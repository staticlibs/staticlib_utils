/*
 * Copyright 2015, alex at staticlibs.net
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
 * File:   windows.cpp
 * Author: alex
 * 
 * Created on March 16, 2015, 10:02 PM
 */

#include "staticlib/utils/windows.hpp"

#ifdef STATICLIB_WINDOWS

#include <memory>
#include <exception>
#include <string>
#include <algorithm>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <wtsapi32.h>
#include <ntsecapi.h>

#include "staticlib/support.hpp"

#include "staticlib/utils/string_utils.hpp"

namespace staticlib {
namespace utils {

namespace { // anonymous

/**
 * Deleter implementation for smart pointer classes.
 * Will call 'LocalFree' function on the pointer.
 */
template <typename T>
class local_free_deleter {
public:
    /**
     * Delete operation, will call 'LocalFree' function on the pointer.
     * 
     * @param t pointer
     */
    void operator()(T* t) {
        ::LocalFree(t);
    }
};

/**
 * Deleter implementation for HANDLEs.
 */
class handle_deleter {
public:
    /**
     * Delete operation, calls 'CloseHandle'.
     * 
     * @param handle handle
     */
    void operator()(HANDLE handle) {
        if (nullptr != handle) {
            ::CloseHandle(handle);
        }
    }
};

/**
 * Deleter implementation for LSA_HANDLEs.
 */
class lsa_handle_deleter {
public:
    /**
     * Delete operation, calls 'LsaClose'.
     * 
     * @param handle LSA handle
     */
    void operator()(LSA_HANDLE handle) {
        if (nullptr != handle) {
            ::LsaClose(handle);
        }
    }
};

/**
 * Deleter implementation for WTS buffers.
 */
class wts_buffer_deleter {
public:
    /**
     * Delete operation, calls 'WTSFreeMemory'.
     * 
     * @param buf wide char WTS buffer
     */
    void operator()(wchar_t* buf) {
        if (nullptr != buf) {
            ::WTSFreeMemory(buf);
        }
    }
};

} // namespace

std::wstring widen(const std::string& st) {
    if (st.empty()) return std::wstring();
    auto size_needed = MultiByteToWideChar(CP_UTF8, 0, st.c_str(), static_cast<int> (st.length()), nullptr, 0);
    if (0 == size_needed) throw utils_exception(TRACEMSG("Error on string widen calculation," +
            " string: [" + st + "], error: [" + errcode_to_string(GetLastError()) + "]"));
    std::wstring res{};
    res.resize(size_needed);
    auto buf = std::addressof(res.front());
    int chars_copied = MultiByteToWideChar(CP_UTF8, 0, st.c_str(), static_cast<int> (st.size()), buf, size_needed);
    if (chars_copied != size_needed) throw utils_exception(TRACEMSG("Error on string widen execution," +
            " string: [" + st + "], error: [" + errcode_to_string(GetLastError()) + "]"));
    return res;
}

std::string narrow(std::wstring wstr) {
    return narrow(wstr.c_str(), wstr.length());
}

std::string narrow(const wchar_t* wbuf, size_t length) {
    if (0 == length) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wbuf, static_cast<int> (length), nullptr, 0, nullptr, nullptr);
    if (0 == size_needed) throw utils_exception(TRACEMSG("Error on string narrow calculation," +
            " string length: [" + sl::support::to_string(length) + "], error code: [" + sl::support::to_string(GetLastError()) + "]"));
    std::string res{};
    res.resize(size_needed);
    auto buf = std::addressof(res.front());
    int bytes_copied = WideCharToMultiByte(CP_UTF8, 0, wbuf, static_cast<int> (length), buf, size_needed, nullptr, nullptr);
    if (bytes_copied != size_needed) throw utils_exception(TRACEMSG("Error on string narrow execution," +
            " string length: [" + sl::support::to_string(length) + "], error code: [" + sl::support::to_string(GetLastError()) + "]"));
    return res;
}

std::string errcode_to_string(uint32_t code) STATICLIB_NOEXCEPT {
    if (0 == code) return std::string {};
    wchar_t* buf_p = nullptr;
    size_t size = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<wchar_t*> (&buf_p), 0, nullptr);
    if (0 == size) {
        return "Cannot format code: [" + sl::support::to_string(code) + "]" +
                " into message, error code: [" + sl::support::to_string(GetLastError()) + "]";
    }
    auto buf = std::unique_ptr<wchar_t, local_free_deleter<wchar_t>> (buf_p, local_free_deleter<wchar_t>{});
    if (size <= 2) {
        return "code: [" + sl::support::to_string(code) + "], message: []";
    }
    try {
        std::string msg = narrow(buf.get(), size - 2);
        return "code: [" + sl::support::to_string(code) + "], message: [" + msg + "]";
    } catch (const std::exception& e) {
        return "Cannot format code: [" + sl::support::to_string(code) + "]" +
                " into message, narrow error: [" + e.what() + "]";
    }
}

bool current_process_elevated() {
    HANDLE hatoken = nullptr;
    auto err_open = ::OpenProcessToken(::GetCurrentProcess(), TOKEN_QUERY, std::addressof(hatoken));    
    if (0 == err_open) throw utils_exception(TRACEMSG("'OpenProcessToken'" +
            " error: [" + errcode_to_string(::GetLastError()) + "]"));
    auto token = std::unique_ptr<void, handle_deleter>(hatoken, handle_deleter());
    TOKEN_ELEVATION elev;
    DWORD len = sizeof(TOKEN_ELEVATION);
    auto err_info = ::GetTokenInformation(token.get(), TokenElevation, std::addressof(elev),
            sizeof(elev), std::addressof(len));
    if (0 == err_info) throw utils_exception(TRACEMSG("'GetTokenInformation'" +
            " error: [" + errcode_to_string(::GetLastError()) + "]"));
    return 0 != elev.TokenIsElevated;
}

std::string current_process_username() {
    DWORD session_id = 0;
    auto err_sid = ::ProcessIdToSessionId(::GetCurrentProcessId(), std::addressof(session_id));
    if (0 == err_sid) throw utils_exception(TRACEMSG("'ProcessIdToSessionId'" +
            " error: [" + errcode_to_string(::GetLastError()) + "]"));
    DWORD len = 0;
    wchar_t* out_ptr = nullptr;
    auto err_wts = ::WTSQuerySessionInformationW(WTS_CURRENT_SERVER_HANDLE, session_id, WTSUserName,
            std::addressof(out_ptr), std::addressof(len));
    if (0 == err_wts) throw utils_exception(TRACEMSG("'WTSQuerySessionInformationW'" +
            " error: [" + errcode_to_string(::GetLastError()) + "]"));
    auto out = std::unique_ptr<wchar_t, wts_buffer_deleter>(out_ptr, wts_buffer_deleter());
    return narrow(out.get(), len/sizeof(wchar_t) - 1);
}

void ensure_has_logon_as_service(const std::string& username) {
    std::wstring uname = widen(username);
    
    // lookup check
    DWORD sidlen = 0;
    DWORD domlen = 0;
    SID_NAME_USE siduse;
    auto err_look_check = ::LookupAccountNameW(nullptr, uname.data(), nullptr, std::addressof(sidlen),
            nullptr, std::addressof(domlen), std::addressof(siduse));
    if (0 == err_look_check && ERROR_INSUFFICIENT_BUFFER != GetLastError()) {
        throw utils_exception(TRACEMSG("'LookupAccountNameW' check," +
            " error: [" + errcode_to_string(::GetLastError()) + "]"));
    }
   
    // lookup
    std::vector<char> sidbuf;
    sidbuf.resize(sidlen);
    PSID sid = reinterpret_cast<PSID>(sidbuf.data());
    std::wstring domname;
    domname.resize(domlen);
    auto err_look = ::LookupAccountNameW(nullptr, uname.data(), sid, std::addressof(sidlen),
            std::addressof(domname.front()), std::addressof(domlen), std::addressof(siduse));
    if (0 == err_look) throw utils_exception(TRACEMSG("'LookupAccountNameW'," +
            " error: [" + errcode_to_string(::GetLastError()) + "]"));
   
    // open policy
    LSA_UNICODE_STRING domname_u;    
    domname_u.Buffer = std::addressof(domname.front());
    domname_u.Length = static_cast<USHORT>(domname.length() * sizeof(wchar_t));
    domname_u.MaximumLength = static_cast<USHORT>((domname.length() + 1) * sizeof(wchar_t));
    LSA_OBJECT_ATTRIBUTES attrs;
    std::memset(std::addressof(attrs), '\0', sizeof(attrs));
    LSA_HANDLE lh_ptr;
    auto err_open = LsaOpenPolicy(std::addressof(domname_u), std::addressof(attrs), 
            POLICY_ALL_ACCESS, std::addressof(lh_ptr));
    if (0 != err_open) throw utils_exception(TRACEMSG("'LsaOpenPolicy'" +
            " error: [" + errcode_to_string(::LsaNtStatusToWinError(err_open)) + "]"));
    auto lh = std::unique_ptr<void, lsa_handle_deleter>(lh_ptr, lsa_handle_deleter());

    // add right
    std::wstring right = widen("SeServiceLogonRight");
    LSA_UNICODE_STRING right_u;
    right_u.Buffer = std::addressof(right.front());
    right_u.Length = static_cast<USHORT>(right.length() * sizeof(wchar_t));
    right_u.MaximumLength = static_cast<USHORT>((right.length() + 1) * sizeof(wchar_t));
    auto err_add = ::LsaAddAccountRights(lh.get(), sid, std::addressof(right_u), 1);
    if (0 != err_add) throw utils_exception(TRACEMSG("'LsaAddAccountRights'" +
            " error: [" + errcode_to_string(::LsaNtStatusToWinError(err_add)) + "]"));
}

// named_mutex impl

named_mutex::named_mutex(const std::string& name) :
mutex(::CreateMutexW(nullptr, FALSE, widen(name).c_str())),
error(::GetLastError()) { }

named_mutex::named_mutex(named_mutex&& other) :
mutex(other.mutex),
error(other.error) {
    other.mutex = nullptr;
}

named_mutex& named_mutex::operator=(named_mutex&& other) {
    mutex = other.mutex;
    other.mutex = nullptr;
    error = other.error;
    return *this;
}

named_mutex::~named_mutex() STATICLIB_NOEXCEPT {
    if (nullptr != mutex) {
        ::CloseHandle(mutex);
    }
}

bool named_mutex::already_taken() const {
    return (ERROR_ALREADY_EXISTS == error);
}


} // namespace
}

#endif // STATICLIB_WINDOWS
