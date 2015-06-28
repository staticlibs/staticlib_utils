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
 * File:   ProducerConsumerQueue_test.cpp
 * Author: alex
 *
 * Created on June 28, 2015, 8:02 PM
 */

// source: https://github.com/facebook/folly/blob/b75ef0a0af48766298ebcc946dd31fe0da5161e3/folly/test/ProducerConsumerQueueTest.cpp

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <atomic>
#include <chrono>
#include <memory>
#include <thread>

#include "staticlib/utils/ProducerConsumerQueue.hpp"

namespace { // anonymous

namespace su = staticlib::utils;

template<class T> struct TestTraits {

    T limit() const {
        return 1 << 16;
    }

    T generate() const {
        return rand() % 26;
    }
};

template<> struct TestTraits<std::string> {

    unsigned int limit() const {
        return 1 << 16;
    }

    std::string generate() const {
        return std::string(12, '#');
    }
};

template<class QueueType, size_t Size, bool Pop = false >
struct PerfTest {
    typedef typename QueueType::value_type T;

    explicit PerfTest() : queue_(Size), done_(false) { }

    void operator()() {
        using namespace std::chrono;
        auto const startTime = system_clock::now();
        std::thread producer([this] { this->producer(); });
        std::thread consumer([this] { this->consumer(); });
        producer.join();
        done_ = true;
        consumer.join();
        auto duration = duration_cast<milliseconds>(system_clock::now() - startTime);
        std::cout << " done: " << duration.count() << "ms" << std::endl;
    }

    void producer() {
        // This is written differently than you might expect so that
        // it does not run afoul of -Wsign-compare, regardless of the
        // signedness of this loop's upper bound.
        for (auto i = traits_.limit(); i > 0; --i) {
            while (!queue_.write(traits_.generate())) {
            }
        }
    }

    void consumer() {
        bool tmp = Pop;
        /*static*/ if (tmp) {
            while (!done_) {
                if (queue_.frontPtr()) {
                    queue_.popFront();
                }
            }
        } else {
            while (!done_) {
                T data;
                queue_.read(data);
            }
        }
    }
    QueueType queue_;
    std::atomic<bool> done_;
    TestTraits<T> traits_;
};

template<class TestType> void doTest(const char* name) {
    std::cout << " testing: " << name << std::endl;
    std::unique_ptr<TestType> const t(new TestType());
    (*t)();
}

template<class T, bool Pop = false >
void perfTestType(const char* type) {
    const size_t size = 0xfffe;
    std::cout << "Type: " << type << std::endl;
    doTest<PerfTest<su::ProducerConsumerQueue<T>, size, Pop> >("ProducerConsumerQueue");
}

template<class QueueType, size_t Size, bool Pop>
struct CorrectnessTest {
    typedef typename QueueType::value_type T;

    std::vector<T> testData_;
    QueueType queue_;
    TestTraits<T> traits_;
    std::atomic<bool> done_;

    explicit CorrectnessTest():
    queue_(Size),
    done_(false) {
        const size_t testSize = static_cast<size_t>(traits_.limit());
        testData_.reserve(testSize);
        for (size_t i = 0; i < testSize; ++i) {
            testData_.push_back(traits_.generate());
        }
    }

    void operator()() {
        std::thread producer([this] { this->producer(); });
        std::thread consumer([this] { this->consumer(); });
        producer.join();
        done_ = true;
        consumer.join();
    }

    void producer() {
        for (auto& data : testData_) {
            while (!queue_.write(data)) {
            }
        }
    }

    void consumer() {
        bool tmp = Pop;
        if (tmp) {
            consumerPop();
        } else {
            consumerRead();
        }
    }

    void consumerPop() {
        for (auto expect : testData_) {
        again:
            T* data = queue_.frontPtr();
            if (!data) {
                if (done_) {
                    // Try one more read; unless there's a bug in the queue class
                    // there should still be more data sitting in the queue even
                    // though the producer thread exited.
                    data = queue_.frontPtr();
                    if (!data) {
                        assert(false); // Finished too early ...
                        return;
                    }
                } else {
                    goto again;
                }
            } else {
                queue_.popFront();
            }
            (void) expect;
            assert(*data == expect);
        }
    }

    void consumerRead() {
        for (auto expect : testData_) {
        again:
            T data;
            if (!queue_.read(data)) {
                if (done_) {
                    // Try one more read; unless there's a bug in the queue class
                    // there should still be more data sitting in the queue even
                    // though the producer thread exited.
                    if (!queue_.read(data)) {
                        assert(false); // Finished too early ...
                        return;
                    }
                } else {
                    goto again;
                }
            }
            (void) expect;
            assert(data == expect);
        }
    }
};

template<class T, bool Pop = false >
void correctnessTestType(const std::string& type) {
    std::cout << "Type: " << type << std::endl;
    doTest<CorrectnessTest<su::ProducerConsumerQueue<T>, 0xfffe, Pop> >("ProducerConsumerQueue");
}

struct DtorChecker {
    static unsigned int numInstances;

    DtorChecker() {
        ++numInstances;
    }

    DtorChecker(const DtorChecker&) {
        ++numInstances;
    }

    ~DtorChecker() {
        --numInstances;
    }
};

unsigned int DtorChecker::numInstances = 0;

void test_QueueCorrectness() {
    // todo: fails on msvc
    //correctnessTestType<std::string, true>("string (front+pop)");
    correctnessTestType<std::string>("string");
    correctnessTestType<int>("int");
    correctnessTestType<unsigned long long>("unsigned long long");
}

void test_PerfTest() {
    // todo: fails on msvc
    // perfTestType<std::string, true>("string (front+pop)");
    perfTestType<std::string>("string");
    perfTestType<int>("int");
    perfTestType<unsigned long long>("unsigned long long");
}

void test_Destructor() {
    // Test that orphaned elements in a ProducerConsumerQueue are
    // destroyed.
    {
        su::ProducerConsumerQueue<DtorChecker> queue(1024);
        for (int i = 0; i < 10; ++i) {
            assert(queue.write(DtorChecker()));
        }
        assert(DtorChecker::numInstances == 10);
        {
            DtorChecker ignore;
            assert(queue.read(ignore));
            assert(queue.read(ignore));
        }
        assert(DtorChecker::numInstances == 8);
    }
    assert(DtorChecker::numInstances == 0);
    // Test the same thing in the case that the queue write pointer has
    // wrapped, but the read one hasn't.
    {
        su::ProducerConsumerQueue<DtorChecker> queue(4);
        for (int i = 0; i < 3; ++i) {
            assert(queue.write(DtorChecker()));
        }
        assert(DtorChecker::numInstances == 3);
        {
            DtorChecker ignore;
            assert(queue.read(ignore));
        }
        assert(DtorChecker::numInstances == 2);
        assert(queue.write(DtorChecker()));
        assert(DtorChecker::numInstances == 3);
    }
    assert(DtorChecker::numInstances == 0);
}

void test_EmptyFull() {
    su::ProducerConsumerQueue<int> queue(3);
    assert(queue.isEmpty());
    assert(!queue.isFull());
    assert(queue.write(1));
    assert(!queue.isEmpty());
    assert(!queue.isFull());
    assert(queue.write(2));
    assert(!queue.isEmpty());
    assert(queue.isFull()); // Tricky: full after 2 writes, not 3.
    assert(!queue.write(3));
    assert(queue.sizeGuess() == 2);
}

}

int main() {
    test_QueueCorrectness();
    test_PerfTest();
    test_Destructor();
    test_EmptyFull();
    
    return 0;
}

