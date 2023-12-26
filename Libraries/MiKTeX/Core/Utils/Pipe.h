/**
 * @file Pipe.h
 * @author Christian Schenk
 * @brief Pipe class
 *
 * @copyright Copyright © 1996-2023 Christian Schenk
 *
 * This file is part of the MiKTeX Core Library.
 *
 * The MiKTeX Core Library is licensed under GNU General Public License version
 * 2 or any later version.
 */

#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>

CORE_INTERNAL_BEGIN_NAMESPACE;

#if defined(_MSC_VER)
#pragma push_macro("min")
#undef min
#endif

class Pipe
{

public:

    Pipe()
    {
        capacity = 1024 * 32;
        buffer = new unsigned char[capacity];
    }

    ~Pipe()
    {
        delete[] buffer;
    }

    void Close() noexcept
    {
        done = true;
        readCondition.notify_one();
        writeCondition.notify_one();
    }

    void Write(const void* data, size_t count)
    {
        std::unique_lock<std::mutex> lock(mut);
        size_t written = 0;
        while (written < count)
        {
            writeCondition.wait(lock, [this]
                                { return done || CanWrite(); });
            if (done)
            {
                throw MiKTeX::Core::BrokenPipeException();
            }
            size_t n = std::min(count - written, capacity - size);
            size_t num1 = std::min(n, capacity - tail);
            size_t num2 = n - num1;
            memcpy(buffer + tail, (unsigned char *)data + written, num1);
            memcpy(buffer, (unsigned char *)data + written + num1, num2);
            tail = (tail + n) % capacity;
            size += n;
            readCondition.notify_one();
            written += n;
        }
    }

    size_t Read(void* data, size_t count)
    {
        std::unique_lock<std::mutex> lock(mut);
        size_t read = 0;
        bool noMore = false;
        while (read < count && !noMore)
        {
            readCondition.wait(lock, [this]
                               { return done || CanRead(); });
            size_t n = std::min(count - read, size);
            size_t num1 = std::min(n, capacity - head);
            size_t num2 = n - num1;
            memcpy((unsigned char *)data + read, buffer + head, num1);
            memcpy((unsigned char *)data + read + num1, buffer, num2);
            head = (head + n) % capacity;
            size -= n;
            writeCondition.notify_one();
            read += n;
            noMore = done;
        }
        return read;
    }

private:

#if 0
    void Resize(size_t newCapacity)
    {
        if (done || newCapacity <= capacity)
        {
            return;
        }
        unsigned char *newBuffer = new unsigned char[newCapacity];
        size_t size = GetSize();
        size_t num1 = min(size, capacity - head);
        size_t num2 = size - num1;
        memcpy(newBuffer, buffer + head, num1);
        memcpy(newBuffer + num1, buffer, num2);
        delete[] buffer;
        buffer = newBuffer;
        head = 0;
        tail = size;
    }
#endif

    bool CanWrite() const
    {
        return size < capacity;
    }

    bool CanRead() const
    {
        return size > 0;
    }

    unsigned char* buffer = nullptr;
    size_t capacity = 0;
    std::atomic_bool done{false};
    size_t head = 0;
    std::mutex mut;
    std::condition_variable readCondition;
    size_t size = 0;
    size_t tail = 0;
    std::condition_variable writeCondition;
};

#if defined(_MSC_VER)
#pragma pop_macro("min")
#endif

CORE_INTERNAL_END_NAMESPACE;
