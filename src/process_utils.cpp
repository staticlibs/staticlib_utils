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
 * File:   process_utils.cpp
 * Author: alex
 * 
 * Created on September 21, 2015, 8:47 AM
 */

#include <array>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>

#include "staticlib/utils/config.hpp"
#ifdef STATICLIB_WINDOWS
#include "staticlib/utils/windows.hpp"
#endif // STATICLIB_WINDOWS
#if defined(STATICLIB_LINUX) || defined(STATICLIB_MAC)
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#endif // STATICLIB_LINUX || STATICLIB_MAC
#include "staticlib/utils/UtilsException.hpp"
#include "staticlib/utils/tracemsg.hpp"
#include "staticlib/utils/string_utils.hpp"
#include "staticlib/utils/process_utils.hpp"

namespace staticlib {
namespace utils {

namespace { // anonymous

#if defined(STATICLIB_LINUX) || defined(STATICLIB_MAC)
int parse_int_nothrow(char* fd_name) {
    size_t i = 0;
    while('\0' != fd_name[i]) {
        if(fd_name[i] < '0' || fd_name[i] > '9') return -1;
        i+=1;
    }
    errno = 0;
    int res = ::strtol(fd_name, NULL, 10);
    if (errno > 0) {
        errno = 0;
        return -1;
    }
    return res;
}

void close_descriptors_nothrow() {    
    for (;;) {        
        // open descriptors dir
        DIR* dp = ::opendir("/proc/self/fd");
        if (NULL == dp) {
            std::cout << TRACEMSG(std::string{} + 
                    "Process opendir(\"/proc/self/fd\") failed: [" + ::strerror(errno) + "]") 
                    << std::endl;
            _exit(errno);
        }
        // collect descriptors
        std::array<int, 1024> fd_list{{}};
        errno = 0;
        size_t idx = 0;
        struct dirent64* dirp;
        while ((dirp = readdir64(dp)) != NULL) {
            int fd = parse_int_nothrow(dirp->d_name);            
            if (-1 != fd && STDOUT_FILENO != fd && STDERR_FILENO != fd) {
               fd_list[idx++] = fd;
               if (idx >= fd_list.size()) break;
            }
            errno = 0;
        }                
        // readdir64 failed
        if (errno > 0) {
            std::cout << TRACEMSG(std::string{} + 
                    "Process readdir64 failed: [" + ::strerror(errno) + "]") << std::endl;
            _exit(errno);
        }
        for (size_t i = 0; i < idx; i++) {
            close(fd_list[i]);
        }
        closedir(dp);
        // if fd_list was 
        if (idx < fd_list.size()) break;
    }
}

void copy_descriptor_nothrow(int from, int to) {
    long int res;
    do {
        res = ::dup2(from, to);
    } while ((-1 == res) && (errno == EINTR));
    // cannot throw here and it is yet no destination to write error to
    if (-1 == res) _exit(errno);
}

void setsid_nothrow() {
    pid_t sid = setsid();
    if (sid < 0) {
        std::cout << TRACEMSG(std::string{} + 
                "Process setsid error: [" + ::strerror(errno) + "]") << std::endl;
        _exit(sid);
    }
}

void reset_signals_nothrow() {
    // set signals to default
    struct sigaction sig_action;
    sig_action.sa_handler = SIG_DFL;
    sig_action.sa_flags = 0;
    ::sigemptyset(std::addressof(sig_action.sa_mask));
    for (int i = 0; i < NSIG; i++) {
        ::sigaction(i, std::addressof(sig_action), nullptr);
    }
    // resume all signals
    sigset_t allmask;
    ::sigfillset(std::addressof(allmask));
    int err = ::pthread_sigmask(SIG_SETMASK, std::addressof(allmask), nullptr);
    if (0 != err) {
        std::cout << TRACEMSG(std::string{} +
                "Error resuming signals in child: [" + ::strerror(err) + "]") << std::endl;
        _exit(err);
    }
}

void sigchild_handler(int) {
    pid_t pid;
    do {
        pid = ::waitpid(static_cast<pid_t> (-1), 0, WNOHANG);
    } while (pid > 0);
}

void register_signal(int signum, int flags, void (*handler)(int)) {
    struct sigaction sa;
    sa.sa_handler = handler;
    ::sigemptyset(std::addressof(sa.sa_mask));
    sa.sa_flags = flags;
    int res = ::sigaction(signum, std::addressof(sa), 0);
    if (-1 == res) throw UtilsException(TRACEMSG(std::string{} + 
            "Error registering signal: [" + to_string(signum) + "],"
            " with flags: [" + to_string(flags) + "], error: [" + ::strerror(errno) + "]"));
}

sigset_t block_signals() {
    sigset_t oldmask, newmask;
    ::sigfillset(std::addressof(newmask));
    int err = ::pthread_sigmask(SIG_SETMASK, std::addressof(newmask), std::addressof(oldmask));
    if (0 != err) throw UtilsException(TRACEMSG(std::string{} +
            "Error blocking signals in parent: [" + ::strerror(err) + "]"));
    return oldmask;
}

void resume_signals(sigset_t& oldmask) {
    int err = ::pthread_sigmask(SIG_SETMASK, std::addressof(oldmask), nullptr);
    if (0 != err) throw UtilsException(TRACEMSG(std::string{} +
            "Error resuming signals in parent: [" + ::strerror(err) + "]"));
}

int open_fd(const std::string& path) {
    int fd;
    errno = 0;
    do {
        fd = ::open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    } while ((-1 == fd) && (EINTR == errno));
    if (-1 == fd) throw UtilsException(TRACEMSG(std::string{} + 
            "Error opening out file descriptor: [" + ::strerror(errno) + "]" +
            ", specified out path: [" + path + "]"));
    return fd;
}

std::vector<char*> prepare_args(const std::string& executable, const std::vector<std::string>& args) {
    std::vector<char*> res;
    res.reserve(args.size() + 2);
    // generally UB, but okay here
    res.push_back(const_cast<char*> (std::addressof(executable.front())));
    std::transform(args.begin(), args.end(), std::back_inserter(res), [](const std::string & st) {
        return const_cast<char*> (std::addressof(st.front()));
    });
    res.push_back(nullptr);
    return res;
}

int exec_async_unix(const std::string& executable, const std::vector<std::string>& args, const std::string& out) {
    // some preparations
    volatile sigset_t oldmask = block_signals();
    volatile const char* exec_path = executable.c_str();
    volatile std::vector<char*> args_ptrs = prepare_args(executable, args);    
    volatile int out_fd = open_fd(out);    
    // do fork
    volatile pid_t pid = ::vfork();
    if (-1 == pid) { // no child created
        throw UtilsException{TRACEMSG(std::string{} + "Process vfork error: [" + ::strerror(errno) + "]")};
    } else if (pid > 0) { // return pid to parent
        sigset_t& oldmask_ref = const_cast<sigset_t&>(oldmask);
        resume_signals(oldmask_ref);
        return pid;
    } else { // we are in child process      
        copy_descriptor_nothrow(out_fd, STDOUT_FILENO);
        copy_descriptor_nothrow(out_fd, STDERR_FILENO);
        close_descriptors_nothrow();
        setsid_nothrow();
        reset_signals_nothrow();
        // prepare and do exec        
        const char* exec_path_child = const_cast<const char*>(exec_path);
        std::vector<char*>& arg_ptrs_child = const_cast<std::vector<char*>&>(args_ptrs);
        errno = 0;
        int res = ::execv(exec_path_child, arg_ptrs_child.data());
        std::cout << TRACEMSG(std::string{} + " Process execv error: [" + ::strerror(errno) + "]," +
                " executable: [" + executable + "], args size: [" + to_string(args.size()) + "]") << std::endl;
        if (-1 == res) _exit(errno);        
        return 0;
    }
}
#endif

} // namespace

int shell_exec_and_wait(const std::string& cmd) {
#ifdef STATICLIB_WINDOWS
    std::string quoted = "\"" + cmd + "\"";
    std::wstring ws = widen(quoted);
    return _wsystem(ws.c_str());
#else
    return std::system(cmd.c_str());
#endif // STATICLIB_WINDOWS
}

int exec_and_wait(const std::string& executable, const std::vector<std::string>& args, const std::string& out) {
#if defined(STATICLIB_LINUX) || defined(STATICLIB_MAC)
    pid_t pid = exec_async_unix(executable, args, out);
    int status;
    while (::waitpid(pid, std::addressof(status), 0) < 0) {
        switch (errno) {
        case ECHILD: return 0;
        case EINTR: break;
        default: return -1;
        }
    }
    return WEXITSTATUS(status);
#else 
    return -1;
#endif // STATICLIB_LINUX    
}

int exec_async(const std::string& executable, const std::vector<std::string>& args, const std::string& out) {
#if defined(STATICLIB_LINUX) || defined(STATICLIB_MAC)
    pid_t pid =  exec_async_unix(executable, args, out);
    register_signal(SIGCHLD, SA_RESTART | SA_NOCLDSTOP, sigchild_handler);
    return pid;
#else 
    return -1;
#endif // STATICLIB_LINUX
}

} // namespace
}

