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
 * File:   file_io.cpp
 * Author: alex
 * 
 * Created on October 8, 2015, 12:54 PM
 */

#include <string>

#include "staticlib/utils/config.hpp"
#ifdef STATICLIB_WINDOWS
#include <windows.h>
#include "staticlib/utils/windows.hpp"
#else // STATICLIB_WINDOWS
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#endif // STATICLIB_WINDOWS

#include "staticlib/utils/UtilsException.hpp"
#include "staticlib/utils/tracemsg.hpp"
#include "staticlib/utils/file_io.hpp"

namespace staticlib {
namespace utils {

#ifdef STATICLIB_WINDOWS

FileDescriptor::FileDescriptor(std::string file_path, char mode) :
handle(nullptr),
file_path(std::move(file_path)),
mode(mode) {        
    std::wstring wpath = widen(this->file_path);
    DWORD dwDesiredAccess;
    DWORD dwCreationDisposition;
    switch (mode) {
    case 'r':
        dwDesiredAccess = GENERIC_READ;
        dwCreationDisposition = OPEN_EXISTING;
        break;
    case 'w': 
        dwDesiredAccess = GENERIC_WRITE; 
        dwCreationDisposition = CREATE_ALWAYS;
        break;
    default: throw UtilsException(TRACEMSG(std::string{} +
        "Invalid open mode: [" + mode + "] for file: [" + this->file_path + "]"));
    }
    handle = ::CreateFileW(
            wpath.c_str(),
            dwDesiredAccess,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL, // lpSecurityAttributes
            dwCreationDisposition,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    if (INVALID_HANDLE_VALUE == handle) throw UtilsException(TRACEMSG(std::string{} +
            "Error opening file descriptor: [" + errcode_to_string(::GetLastError()) + "]" +
            ", specified path: [" + this->file_path + "]"));
}

FileDescriptor::~FileDescriptor() STATICLIB_NOEXCEPT {
    close();
}

std::streamsize FileDescriptor::read(char* buf, std::streamsize count) {
    if ('r' == mode) {
        if (nullptr != handle) {
            DWORD res;
            auto err = ::ReadFile(handle, buf, static_cast<DWORD>(count), std::addressof(res), nullptr);
            if (0 != err) return res;
            if (ERROR_HANDLE_EOF == ::GetLastError()) return std::char_traits<char>::eof();
            throw UtilsException(TRACEMSG(std::string{} +
                    "Read error from file: [" + file_path + "]," +
                    " error: [" + errcode_to_string(::GetLastError()) + "]"));
        } else throw UtilsException(TRACEMSG(std::string{} +
                "Attempt to read closed file: [" + file_path + "]"));
    } else throw UtilsException(TRACEMSG(std::string{} +
            "Attempt to read from file opened in 'w' mode: [" + file_path + "]"));
}

std::streamsize FileDescriptor::write(const char* buf, std::streamsize count) {
    if ('w' == mode) {
        if (nullptr != handle) {
            DWORD res;
            auto err = ::WriteFile(handle, buf, static_cast<DWORD>(count), std::addressof(res), nullptr);
            if (0 != err) return res;
            throw UtilsException(TRACEMSG(std::string{} +
                    "Write error to file: [" + file_path + "]," +
                    " error: [" + errcode_to_string(::GetLastError()) + "]"));
        } else throw UtilsException(TRACEMSG(std::string{} +
                "Attempt to write into closed file: [" + file_path + "]"));
    } else throw UtilsException(TRACEMSG(std::string{} +
    "Attempt to write into file opened in 'r' mode: [" + file_path + "]"));
}

std::streampos FileDescriptor::seek(std::streamsize offset, char whence) {
    if (nullptr != handle) {
        DWORD dwMoveMethod;
        switch (whence) {
        case 'b': dwMoveMethod = FILE_BEGIN; break;
        case 'c': dwMoveMethod = FILE_CURRENT; break;
        case 'e': dwMoveMethod = FILE_END; break;
        default: throw UtilsException(TRACEMSG(std::string{} +
                    "Invalid whence value: [" + whence + "] for seeking file: [" + file_path + "]"));
        }
        LONG lDistanceToMove = static_cast<LONG> (offset & 0xffffffff);
        LONG lDistanceToMoveHigh = static_cast<LONG> (offset >> 32);
        DWORD dwResultLow = ::SetFilePointer(
                handle,
                lDistanceToMove,
                std::addressof(lDistanceToMoveHigh),
                dwMoveMethod);
        if (INVALID_SET_FILE_POINTER != dwResultLow || ::GetLastError() == NO_ERROR) {
            return (static_cast<long long int>(lDistanceToMoveHigh) << 32) + dwResultLow;
        }
        throw UtilsException(TRACEMSG(std::string{} +
                "Seek error over file: [" + file_path + "]," +
                " error: [" + errcode_to_string(::GetLastError()) + "]"));
    } else throw UtilsException(TRACEMSG(std::string{} +
            "Attempt to seek over closed file: [" + file_path + "]"));
}

void FileDescriptor::close() STATICLIB_NOEXCEPT {
    if (nullptr != handle) {
        ::CloseHandle(handle);
        handle = nullptr;
    }
}

off_t FileDescriptor::size() {
    if (nullptr != handle) {
        LARGE_INTEGER res = -1;
        auto err = ::GetFileSizeEx(handle, std::addressof(res));
        if (0 != err) {
            return static_cast<off_t>(res);
        } throw UtilsException(TRACEMSG(std::string{} +
                "Error getting size of file: [" + file_path + "]," +
                " error: [" + errcode_to_string(::GetLastError()) + "]"));
    } else throw UtilsException(TRACEMSG(std::string{} +
            "Attempt to get size of closed file: [" + file_path + "]"));
}

#else // STATICLIB_WINDOWS

FileDescriptor::FileDescriptor(std::string file_path, char mode) :
fd(-1), 
file_path(std::move(file_path)),
mode(mode) { 
    switch (mode) {
    case 'r': 
        fd = ::open(this->file_path.c_str(), O_RDONLY);
        break;
    case 'w': 
        fd = ::open(this->file_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        break;
    default: throw UtilsException(TRACEMSG(std::string{} +
            "Invalid open mode: [" + mode + "] for file: [" + this->file_path + "]"));
    }
    
    if (-1 == fd) throw UtilsException(TRACEMSG(std::string{} +
            "Error opening file: [" + this->file_path + "], with mode: [" + mode + "]," +
            " error: [" + ::strerror(errno) + "]"));
}

FileDescriptor::~FileDescriptor() STATICLIB_NOEXCEPT {
    close();
}

FileDescriptor::FileDescriptor(FileDescriptor&& other) :
fd(other.fd),
mode(other.mode) {
    other.fd = -1;
}

FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) {
    fd = other.fd;
    other.fd = -1;
    mode = other.mode;
    return *this;
}

std::streamsize FileDescriptor::read(char* buf, std::streamsize count) {
    if ('r' == mode) {
        if (-1 != fd) {
            auto res = ::read(fd, buf, count);
            if (-1 != res) {
                return res > 0 ? res : std::char_traits<char>::eof();
            }
            throw UtilsException(TRACEMSG(std::string{} +
                    "Read error from file: [" + file_path +"]," +
                    " error: [" + ::strerror(errno) + "]"));
        } else throw UtilsException(TRACEMSG(std::string{} +
                "Attempt to read closed file: [" + file_path + "]"));
    } else throw UtilsException(TRACEMSG(std::string{} +
                "Attempt to read from file opened in 'w' mode: [" + file_path + "]"));
}

std::streamsize FileDescriptor::write(const char* buf, std::streamsize count) {
    if ('w' == mode) {
        if (-1 != fd) {
            auto res = ::write(fd, buf, count);
            if (-1 != res) return res;
            throw UtilsException(TRACEMSG(std::string{} +
                    "Write error to file: [" + file_path + "]," +
                    " error: [" + ::strerror(errno) + "]"));            
        } else throw UtilsException(TRACEMSG(std::string{} +
                "Attempt to write into closed file: [" + file_path + "]"));
    } else throw UtilsException(TRACEMSG(std::string{} +
            "Attempt to write into file opened in 'r' mode: [" + file_path + "]"));
}

std::streampos FileDescriptor::seek(std::streamsize offset, char whence) {
    if (-1 != fd) {
        int whence_int;
        switch (whence) {
        case 'b': whence_int = SEEK_SET; break;        
        case 'c': whence_int = SEEK_CUR; break;
        case 'e': whence_int = SEEK_END; break;
        default: throw UtilsException(TRACEMSG(std::string{} +
            "Invalid whence value: [" + whence + "] for seeking file: [" + file_path + "]"));
        }
        auto res = lseek(fd, offset, whence_int);
        if (static_cast<off_t> (-1) != res) return res;
        throw UtilsException(TRACEMSG(std::string{} +
                "Seek error over file: [" + file_path + "]," +
                " error: [" + ::strerror(errno) + "]"));        
    } else throw UtilsException(TRACEMSG(std::string{} +
            "Attempt to seek over closed file: [" + file_path + "]"));
}

void FileDescriptor::close() STATICLIB_NOEXCEPT {
    if (-1 != fd) {
        ::close(fd);
        fd = -1;
    }
}

off_t FileDescriptor::size() {
    if (-1 != fd) {
        struct stat64 stat_buf;
        int rc = ::fstat64(fd, &stat_buf);
        if (0 == rc) {
            return stat_buf.st_size;
        }
        throw UtilsException(TRACEMSG(std::string{} +
                "Error getting size of file: [" + file_path + "]," +
                " error: [" + ::strerror(errno) + "]"));
    } else throw UtilsException(TRACEMSG(std::string{} +
            "Attempt to get size of closed file: [" + file_path + "]"));
}

#endif // STATICLIB_WINDOWS

std::streamsize FileDescriptor::flush() {
    return 0;
}

} // namespace
}
