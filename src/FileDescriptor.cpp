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
 * File:   FileDescriptor.cpp
 * Author: alex
 * 
 * Created on October 8, 2015, 12:54 PM
 */

#include "staticlib/utils/FileDescriptor.hpp"

#include <string>

#include "staticlib/config.hpp"

#ifdef STATICLIB_WINDOWS
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
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

namespace staticlib {
namespace utils {

#ifdef STATICLIB_WINDOWS

FileDescriptor::FileDescriptor(std::string file_path, char mode) :
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
    default: throw UtilsException(TRACEMSG("Invalid open mode: [" + mode + "]" + 
            " for file: [" + this->file_path + "]"));
    }
    handle = ::CreateFileW(
            wpath.c_str(),
            dwDesiredAccess,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL, // lpSecurityAttributes
            dwCreationDisposition,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    if (INVALID_HANDLE_VALUE == handle) throw UtilsException(TRACEMSG(
            "Error opening file descriptor: [" + errcode_to_string(::GetLastError()) + "]" +
            ", specified path: [" + this->file_path + "]"));
}


FileDescriptor::FileDescriptor(FileDescriptor&& other) :
handle(other.handle),
file_path(std::move(other.file_path)),
mode(other.mode) {
    other.handle = nullptr;
}

FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) {
    handle = other.handle;
    other.handle = nullptr;
    file_path = std::move(other.file_path);
    mode = other.mode;
    return *this;
}

FileDescriptor::~FileDescriptor() STATICLIB_NOEXCEPT {
    close();
}

//todo: overflow
std::streamsize FileDescriptor::read(staticlib::config::span<char> span) {
    if ('r' == mode) {
        if (nullptr != handle) {
            DWORD res;
            DWORD ulen = span.size() <= std::numeric_limits<uint32_t>::max() ? 
                    static_cast<uint32_t>(span.size()) :
                    std::numeric_limits<uint32_t>::max();
            auto err = ::ReadFile(handle, static_cast<void*>(span.data()), ulen,
                    std::addressof(res), nullptr);
            if (0 != err) {
                return res > 0 ? static_cast<std::streamsize>(res) : std::char_traits<char>::eof();
            }
            throw UtilsException(TRACEMSG("Read error from file: [" + file_path + "]," +
                    " error: [" + errcode_to_string(::GetLastError()) + "]"));
        } else throw UtilsException(TRACEMSG("Attempt to read closed file: [" + file_path + "]"));
    } else throw UtilsException(TRACEMSG("Attempt to read from file opened in 'w' mode: [" + file_path + "]"));
}

//todo: overflow
std::streamsize FileDescriptor::write(staticlib::config::span<const char> span) {
    if ('w' == mode) {
        if (nullptr != handle) {
            DWORD res;
            DWORD ulen = span.size() <= std::numeric_limits<uint32_t>::max() ?
                    static_cast<uint32_t>(span.size()) :
                    std::numeric_limits<uint32_t>::max();
            auto err = ::WriteFile(handle, static_cast<const void*>(span.data()), ulen,
                    std::addressof(res), nullptr);
            if (0 != err) return static_cast<std::streamsize>(res);
            throw UtilsException(TRACEMSG("Write error to file: [" + file_path + "]," +
                    " error: [" + errcode_to_string(::GetLastError()) + "]"));
        } else throw UtilsException(TRACEMSG("Attempt to write into closed file: [" + file_path + "]"));
    } else throw UtilsException(TRACEMSG("Attempt to write into file opened in 'r' mode: [" + file_path + "]"));
}

std::streampos FileDescriptor::seek(std::streamsize offset, char whence) {
    if (nullptr != handle) {
        DWORD dwMoveMethod;
        switch (whence) {
        case 'b': dwMoveMethod = FILE_BEGIN; break;
        case 'c': dwMoveMethod = FILE_CURRENT; break;
        case 'e': dwMoveMethod = FILE_END; break;
        default: throw UtilsException(TRACEMSG("Invalid whence value: [" + whence + "]" + 
                " for seeking file: [" + file_path + "]"));
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
        throw UtilsException(TRACEMSG("Seek error over file: [" + file_path + "]," +
                " error: [" + errcode_to_string(::GetLastError()) + "]"));
    } else throw UtilsException(TRACEMSG("Attempt to seek over closed file: [" + file_path + "]"));
}

void FileDescriptor::close() STATICLIB_NOEXCEPT {
    if (nullptr != handle) {
        ::CloseHandle(handle);
        handle = nullptr;
    }
}

off_t FileDescriptor::size() {
    if (nullptr != handle) {
        DWORD res = ::GetFileSize(handle, nullptr);
        if (INVALID_FILE_SIZE != res || ::GetLastError() == NO_ERROR) {
            return static_cast<off_t>(res);
        } throw UtilsException(TRACEMSG("Error getting size of file: [" + file_path + "]," +
                " error: [" + errcode_to_string(::GetLastError()) + "]"));
    } else throw UtilsException(TRACEMSG("Attempt to get size of closed file: [" + file_path + "]"));
}

#else // STATICLIB_WINDOWS

FileDescriptor::FileDescriptor(std::string file_path, char mode) :
file_path(std::move(file_path)),
mode(mode) { 
    switch (mode) {
    case 'r': 
        fd = ::open(this->file_path.c_str(), O_RDONLY);
        break;
    case 'w': 
        fd = ::open(this->file_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        break;
    default: throw UtilsException(TRACEMSG("Invalid open mode: [" + mode + "]" + 
            " for file: [" + this->file_path + "]"));
    }
    
    if (-1 == fd) throw UtilsException(TRACEMSG("Error opening file: [" + this->file_path + "]," + 
            " with mode: [" + mode + "], error: [" + ::strerror(errno) + "]"));
}

FileDescriptor::~FileDescriptor() STATICLIB_NOEXCEPT {
    close();
}

FileDescriptor::FileDescriptor(FileDescriptor&& other) :
fd(other.fd),
file_path(std::move(other.file_path)),
mode(other.mode) {
    other.fd = -1;
}

FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) {
    fd = other.fd;
    other.fd = -1;
    file_path = std::move(other.file_path);
    mode = other.mode;
    return *this;
}

std::streamsize FileDescriptor::read(staticlib::config::span<char> span) {
    if ('r' == mode) {
        if (-1 != fd) {
            auto res = ::read(fd, span.data(), span.size());
            if (-1 != res) {
                return res > 0 ? res : std::char_traits<char>::eof();
            }
            throw UtilsException(TRACEMSG("Read error from file: [" + file_path +"]," +
                    " error: [" + ::strerror(errno) + "]"));
        } else throw UtilsException(TRACEMSG("Attempt to read closed file: [" + file_path + "]"));
    } else throw UtilsException(TRACEMSG("Attempt to read from file opened in 'w' mode: [" + file_path + "]"));
}

std::streamsize FileDescriptor::write(staticlib::config::span<const char> span) {
    if ('w' == mode) {
        if (-1 != fd) {
            auto res = ::write(fd, span.data(), span.size());
            if (-1 != res) return res;
            throw UtilsException(TRACEMSG("Write error to file: [" + file_path + "]," +
                    " error: [" + ::strerror(errno) + "]"));            
        } else throw UtilsException(TRACEMSG("Attempt to write into closed file: [" + file_path + "]"));
    } else throw UtilsException(TRACEMSG("Attempt to write into file opened in 'r' mode: [" + file_path + "]"));
}

std::streampos FileDescriptor::seek(std::streamsize offset, char whence) {
    if (-1 != fd) {
        int whence_int;
        switch (whence) {
        case 'b': whence_int = SEEK_SET; break;        
        case 'c': whence_int = SEEK_CUR; break;
        case 'e': whence_int = SEEK_END; break;
        default: throw UtilsException(TRACEMSG("Invalid whence value: [" + whence + "]" + 
                " for seeking file: [" + file_path + "]"));
        }
        auto res = lseek(fd, offset, whence_int);
        if (static_cast<off_t> (-1) != res) return res;
        throw UtilsException(TRACEMSG("Seek error over file: [" + file_path + "]," +
                " error: [" + ::strerror(errno) + "]"));        
    } else throw UtilsException(TRACEMSG("Attempt to seek over closed file: [" + file_path + "]"));
}

void FileDescriptor::close() STATICLIB_NOEXCEPT {
    if (-1 != fd) {
        ::close(fd);
        fd = -1;
    }
}

off_t FileDescriptor::size() {
    if (-1 != fd) {
#if defined(STATICLIB_MAC) || defined(STATICLIB_IOS)
        struct stat stat_buf;
        int rc = ::fstat(fd, &stat_buf);
#else
        struct stat64 stat_buf;
        int rc = ::fstat64(fd, &stat_buf);
#endif // STATICLIB_MAC || STATICLIB_IOS
        if (0 == rc) {
            return stat_buf.st_size;
        }
        throw UtilsException(TRACEMSG("Error getting size of file: [" + file_path + "]," +
                " error: [" + ::strerror(errno) + "]"));
    } else throw UtilsException(TRACEMSG("Attempt to get size of closed file: [" + file_path + "]"));
}

#endif // STATICLIB_WINDOWS

std::streamsize FileDescriptor::flush() {
    return 0;
}

const std::string& FileDescriptor::get_file_path() const {
    return file_path;
}

char FileDescriptor::get_mode() {
    return mode;
}

} // namespace
}
