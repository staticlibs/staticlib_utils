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
 * File:   io_utils.hpp
 * Author: alex
 *
 * Created on April 6, 2015, 7:19 PM
 */

#ifndef STATICLIB_IO_UTILS_HPP
#define	STATICLIB_IO_UTILS_HPP

#include <streambuf>
#include <string>
#include <array>

#include "staticlib/utils/tracemsg.hpp"
#include "staticlib/utils/UtilsException.hpp"

namespace staticlib {
namespace utils {

/**
 * Writes buffer contents to the specified Sink ensuring that 
 * the specified number of bytes are written to Sink 
 * (making multiple write calls to Sink if needed).
 * 
 * @param sink iostreams sink
 * @param buf data buffer
 * @param buflen data buffer length
 */
void write_all(std::streambuf& sink, const char* buf, std::streamsize buflen);

/**
 * Writes string contents to the specified Sink ensuring that 
 * the specified number of bytes are written to Sink 
 * (making multiple write calls to Sink if needed).
 * 
 * @param sink iostreams sink
 * @param str data string
 */
void write_all(std::streambuf& sink, const std::string& str);


/**
 * Reads specified number of bytes from the Source into the buffer.
 * May read less then specified bytes only if Source became exhausted.
 * 
 * @param src iostreams source
 * @param buf dest buffer
 * @param buflen number of bytes to read from source
 * @return number of bytes read
 */
size_t read_all(std::streambuf& src, char* buf, std::streamsize buflen);

/**
 * Reads specified number of bytes from the Source into the buffer.
 * Will throw exception if exact specified amount won't be available.
 * 
 * @param src iostreams source
 * @param buf dest buffer
 * @param buflen number of bytes to read from source
 */
void read_exact(std::streambuf& src, char* buf, std::streamsize buflen);

/**
 * Copies data from Source to Sink using specified buffer until 
 * source will be exhausted.
 * 
 * @param src iostreams source
 * @param sink iostreams sink
 * @param buf dest buffer
 * @param buflen number of bytes to read from source
 * @return number of bytes copied
 */
size_t copy_all(std::streambuf& src, std::streambuf& sink, char* buf, std::streamsize buflen);


/**
 * Base class for unbuffered streambuf implementations
 * 
 */
class unbuffered_streambuf_base : public std::streambuf {
public:    
    /**
     * Unsupported method, throws 'UtilsException'
     */
    virtual int underflow() override {
        throw UtilsException(TRACEMSG("'underflow' operation is not supported by unbuffered streambuf"));
    }

    /**
     * Unsupported method, throws 'UtilsException'
     */
    virtual int uflow() override {
        throw UtilsException(TRACEMSG("'uflow' operation is not supported by unbuffered streambuf"));
    }

    /**
     * Unsupported method, throws 'UtilsException'
     */
    virtual int overflow(int) override {
        throw UtilsException(TRACEMSG("'overflow' operation is not supported by unbuffered streambuf"));
    }    
    
protected:
    /**
     * Reads count characters from the input sequence and stores them into a character array pointed to by s
     * Should be overriden by Source streambuf inheritors, default implementation throws 'UtilsException'
     * 
     * @param s destination buffer 
     * @param count number of characters to read
     */
    virtual std::streamsize xsgetn(char*, std::streamsize) override {
        throw UtilsException(TRACEMSG("'xsgetn' operation is not supported by unbuffered streambuf"));
    }

    /**
     * Writes count characters to the output sequence from the character array whose first element is pointed to by s. 
     * Should be overriden by Sink streambuf inheritors, default implementation throws 'UtilsException'
     * 
     * @param s source buffer 
     * @param count number of characters to erite
     */
    virtual std::streamsize xsputn(const char*, std::streamsize) override {
        throw UtilsException(TRACEMSG("'xsputn' operation is not supported by unbuffered streambuf"));
    }

    /**
     * Unsupported method, throws 'UtilsException'
     */
    virtual unbuffered_streambuf_base* setbuf(char*, std::streamsize) override {
        throw UtilsException(TRACEMSG("'setbuf' operation is not supported by unbuffered streambuf"));
    }

    /**
     * Unsupported method, throws 'UtilsException'
     */
    virtual std::streampos seekoff(std::streamsize, std::ios_base::seekdir, std::ios_base::openmode) {
        throw UtilsException(TRACEMSG("'seekoff' operation is not supported by unbuffered streambuf"));
    }

    /**
     * Unsupported method, throws 'UtilsException'
     */
    virtual std::streampos seekpos(std::streampos, std::ios_base::openmode) override {
        throw UtilsException(TRACEMSG("'seekpos' operation is not supported by unbuffered streambuf"));
    }            
    
};

/**
 * Unbuffered implementation of input streambuf, wraps Source reference (in terms of Boost.Iostreams).
 * Should be used directly, must NOT be used wrapped into std::istream.
 */
template <typename Source, std::streamsize source_eof=std::char_traits<char>::eof()>
class unbuffered_source : public unbuffered_streambuf_base {
    Source& source;
    bool exhausted = false;

public:
    /**
     * Constructor
     * 
     * @param source Source reference (in terms of Boost.Iostreams)
     */
    unbuffered_source(Source& source) : source(source) { }

    /**
     * Compatibility method to mimic expected EOF reporting of this streambuf.
     * Return 'std::char_traits<char>::eof()' if the Source was exhausted,
     * throws 'UtilsException' otherwise.
     */
    virtual int uflow() override {
        if (exhausted) {
            return std::char_traits<char>::eof();
        } else {
            throw UtilsException(TRACEMSG("'uflow' operation is not supported by unbuffered streambuf"));
        }
    }
    
protected:
    /**
     * Reads count characters from the input sequence and stores them into a character array pointed to by s
     * On Source EOF returns 0 and sets this streambuf state to 'exhausted'
     * 
     * @param s destination buffer 
     * @param count number of characters to read
     */
    virtual std::streamsize xsgetn(char* s, std::streamsize count) override {
        if (!exhausted) {
            auto res = source.read(s, count);
            if(source_eof != res) {
                return res;
            } else {
                exhausted = true;
                return 0;
            }
        } else {
            return 0;
        }
    }    
};

/**
 * Unbuffered implementation of output streambuf, wraps Sink reference (in terms of Boost.Iostreams).
 * Should be used directly, must NOT be used wrapped into std::ostream.
 */

template <typename Sink>
class unbuffered_sink : public unbuffered_streambuf_base {
    Sink& sink;

public:
    /**
     * Constructor
     * 
     * @param sink Sink reference (in terms of Boost.Iostreams)
     */
    unbuffered_sink(Sink& sink) : sink(sink) { }

protected:
    /**
     * Writes count characters to the output sequence from the character array whose first element is pointed to by s. 
     * 
     * @param s source buffer 
     * @param count number of characters to erite
     */
    virtual std::streamsize xsputn(const char_type* s, std::streamsize count) override {
        return sink.write(s, count);
    }
    
};

} // namespace
}

#endif	/* STATICLIB_IO_UTILS_HPP */

