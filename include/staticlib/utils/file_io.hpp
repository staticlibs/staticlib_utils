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
 * File:   file_io.hpp
 * Author: alex
 *
 * Created on October 8, 2015, 12:51 PM
 */

#ifndef STATICLIB_FILE_IO_HPP
#define	STATICLIB_FILE_IO_HPP

#include <string>
#include <memory>

#include "staticlib/utils/config.hpp"

namespace staticlib {
namespace utils {

class FileDescriptor {
#ifdef STATICLIB_WINDOWS
    void* handle;
#else // STATICLIB_WINDOWS 
    int fd;
#endif // STATICLIB_WINDOWS
    std::string file_path;
    char mode;
public:
    FileDescriptor(std::string file_path, char mode);
    
    ~FileDescriptor() STATICLIB_NOEXCEPT;
    
    FileDescriptor(const FileDescriptor&) = delete;
    
    FileDescriptor& operator=(const FileDescriptor&) = delete;

    FileDescriptor(FileDescriptor&& other);

    FileDescriptor& operator=(FileDescriptor&& other);

    std::streamsize read(char* buf, std::streamsize count);
    
    std::streamsize write(const char* buf, std::streamsize count);
    
    std::streampos seek(std::streamsize offset, char whence = 'b');
    
    std::streamsize flush();
    
    off_t size();
    
    void close() STATICLIB_NOEXCEPT;
};

} // namespace
}

#endif	/* STATICLIB_FILE_IO_HPP */

