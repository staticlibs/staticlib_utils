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

/**
 * Implementation of a file descriptor/handle wrapper with a 
 * unified interface for *nix and windows
 */
class FileDescriptor {
#ifdef STATICLIB_WINDOWS
    void* handle;
#else // STATICLIB_WINDOWS
    /**
     * Native file descriptor (handle on windows)
     */
    int fd;
#endif // STATICLIB_WINDOWS
    /**
     * Path to file
     */
    std::string file_path;
    /**
     * Mode in which this descriptor was opened
     */
    char mode;
public:
    /**
     * Constructor
     * 
     * @param file_path path to file
     * @param mode how to open the file, supported modes are 'r' and 'w'
     */
    FileDescriptor(std::string file_path, char mode);
    
    /**
     * Destructor, will close the descriptor
     */
    ~FileDescriptor() STATICLIB_NOEXCEPT;
    
    /**
     * Deleted copy constructor
     * 
     * @param other instance
     */
    FileDescriptor(const FileDescriptor&) = delete;
    
    /**
     * Deleted copy assignment operator
     * 
     * @param other instance
     * @return this instance
     */
    FileDescriptor& operator=(const FileDescriptor&) = delete;

    /**
     * Move constructor
     * 
     * @param other other instance
     */
    FileDescriptor(FileDescriptor&& other);

    /**
     * Move assignment operator
     * 
     * @param other other instance
     * @return this instance
     */
    FileDescriptor& operator=(FileDescriptor&& other);

    /**
     * Reads specified number of bytes from this file descriptor
     * into specified buffer.
     * 
     * @param buf destination buffer
     * @param count number of bytes to read
     * @return number of bytes read, "std::char_traits<char>::eof()" on EOF
     */
    std::streamsize read(char* buf, std::streamsize count);
    
    /**
     * Writes specified number of bytes to this file descriptor
     * 
     * @param buf source buffer
     * @param count number of bytes to write
     * @return number of bytes successfully written
     */
    std::streamsize write(const char* buf, std::streamsize count);
    
    /**
     * Seeks over this file descriptor
     * 
     * @param offset offset to seek with
     * @param whence seek direction, supported are 'b' (begin, default),
     *        'e' (end),  and 'c' (current position)
     * @return resulting offset location as measured in bytes from the beginning of the file
     */
    std::streampos seek(std::streamsize offset, char whence = 'b');
    
    /**
     * No-op
     * 
     * @return zero
     */
    std::streamsize flush();
    
    /**
     * Returns the size of the file pointed by this descriptor
     * 
     * @return size of the file in bytes
     */
    off_t size();
    
    /**
     * Closed the underlying file descriptor, will be called automatically 
     * on destruction
     */
    void close() STATICLIB_NOEXCEPT;
};

} // namespace
}

#endif	/* STATICLIB_FILE_IO_HPP */

