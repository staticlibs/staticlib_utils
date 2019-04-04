/*
 * Copyright 2019, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   user_utils.cpp
 * Author: alex
 *
 * Created on April 4, 2019, 7:00 PM
 */

#include "staticlib/utils/user_utils.hpp"

#include "staticlib/config.hpp"

#include <vector>

#ifdef STATICLIB_WINDOWS

#include "staticlib/support/windows.hpp"
#include "staticlib/utils/windows.hpp"
#include <shlobj.h>

#elif (defined(STATICLIB_LINUX) || defined(STATICLIB_MAC))

#include <cerrno>
#include <cstring>
#include <memory>
#include <utility>
#include <pwd.h>
#include <unistd.h>
#include <sys/stat.h>

#endif // STATICLIB_WINDOWS

#include "staticlib/support.hpp"
#include "staticlib/utils/utils_exception.hpp"

namespace staticlib {
namespace utils {

namespace { // anonymous

#ifdef STATICLIB_WINDOWS
std::string get_csidl_dir(int csidl) {
    auto buf = std::vector<wchar_t>();
    auto err = ::SHGetFolderPathW(
            nullptr,
            csidl | CSIDL_FLAG_CREATE,
            nullptr, 
            0, 
            buf.data());
    if (S_OK != err) throw utils_exception(TRACEMSG(
            "Error getting directory," +
            " csidl: [" + sl::support::to_string(csidl) + "]" +
            " message: [" + errcode_to_string(HRESULT_CODE(err)) + "]"));
    auto path = narrow(buf.data(), ::wcslen(buf.data()));
    std::replace(path.begin(), path.end(), '\\', '/');
    path.push_back('/');
    return path;
}
#endif // STATICLIB_WINDOWS

#if (defined(STATICLIB_LINUX) || defined(STATICLIB_MAC))
std::pair<std::unique_ptr<struct passwd>, std::vector<char>> get_passwd() {
    auto uid = ::geteuid();
    auto pwd = sl::support::make_unique<struct passwd>();
    std::memset(pwd.get(), '\0', sizeof(pwd));
    auto buf = std::vector<char>();
    buf.resize(1<<5);
    size_t buf_max = 1<<10;
    while (buf.size() <= buf_max) {
        struct passwd* out_ptr = nullptr;
        auto err = ::getpwuid_r(uid, pwd.get(), buf.data(), buf.size(), std::addressof(out_ptr));
        if (nullptr == out_ptr && ERANGE == err) {
            buf.resize(buf.size() * 2);
        } else if (0 == err && nullptr != out_ptr) {
            return std::make_pair(std::move(pwd), std::move(buf));
        } else {
            throw utils_exception(TRACEMSG(
                    "Error getting user name," +
                    " code: [" + sl::support::to_string(err) + "]"));
        }
    }
    throw utils_exception(TRACEMSG(
            "Error getting user name, buffer exceeded," +
            " size: [" + sl::support::to_string(buf_max) + "]"));
}
#endif // STATICLIB_LINUX || STATICLIB_MAC

} // namespace

std::string user_name() {
#ifdef STATICLIB_WINDOWS

    // maybe it is better to consider WTSQuerySessionInformationW
    DWORD len = 0;
    auto err_len = ::GetUserNameW(nullptr, std::addressof(len));
    if (0 !=  err_len) throw utils_exception(TRACEMSG(
            "Error getting required length for 'GetUserNameW' call," +
            " code: [" + sl::support::to_string(err_len) + "]"));
    auto err_len_code = ::GetLastError();
    if (ERROR_INSUFFICIENT_BUFFER != err_len_code) throw utils_exception(TRACEMSG(
            "Error getting required length for 'GetUserNameW' call," +
            " message: [" + errcode_to_string(err_len_code) + "]"));

    auto buf = std::vector<wchar_t>();
    buf.resize(len);

    auto err = ::GetUserNameW(buf.data(), std::addressof(len));
    if (0 == err) throw utils_exception(TRACEMSG(
            "Error getting user name," +
            " message: [" + errcode_to_string(::GetLastError()) + "]"));
    auto res = narrow(buf.data(), len);
    return res;

#elif (defined(STATICLIB_LINUX) || defined(STATICLIB_MAC))

    auto pa = get_passwd();
    return std::string(pa.first->pw_name);

#elif defined(STATICLIB_ANDROID)

    throw utils_exception(TRACEMSG("Getting user name is not supported on Android"));

#else // UNKNOWN

#error "Cannot determine the OS"

#endif // STATICLIB_WINDOWS
}

std::string user_home_dir() {
#ifdef STATICLIB_WINDOWS

    return get_csidl_dir(CSIDL_PROFILE);

#elif (defined(STATICLIB_LINUX) || defined(STATICLIB_MAC))

    auto pa = get_passwd();
    auto res = std::string(pa.first->pw_dir);
    res.push_back('/');
    return res;

#elif defined(STATICLIB_ANDROID)

    throw utils_exception(TRACEMSG("Getting home directory is not supported on Android"));

#else // UNKNOWN

#error "Cannot determine the OS"

#endif // STATICLIB_WINDOWS
}

std::string user_localappdata_dir() {
#ifdef STATICLIB_WINDOWS

    return get_csidl_dir(CSIDL_LOCAL_APPDATA);

#elif (defined(STATICLIB_LINUX) || defined(STATICLIB_MAC))

    // if needed, client should check XDG_DATA_HOME before calling this
    auto home = user_home_dir();
    auto local = home + ".local/";
    auto res = local + "share/";
    // best effort on dir create
    auto mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
    ::mkdir(local.c_str(), mode);
    ::mkdir(res.c_str(), mode);
    return res;

#elif defined(STATICLIB_ANDROID)

    throw utils_exception(TRACEMSG("Getting local app data directory is not supported on Android"));

#else // UNKNOWN

#error "Cannot determine the OS"

#endif // STATICLIB_WINDOWS
}

} // namespace
}
