/*
*
* LibAnt - A handy C++ library
* Copyright (C) 2021 Antigloss Huang (https://github.com/antigloss) All rights reserved.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#ifndef LIBANT_BUFFER_POOL_H
#define LIBANT_BUFFER_POOL_H

#include <memory>
#include <vector>

namespace ant {

/**
 * BufferPool is a dynamically growing buffer object pool whose initial status is of size 0.
 * It limits only the total size of pooled objects, but not the maximum memory usage.
 * Whenever a buffer object is acquired via this BufferPool, it's returned from the pool,
 * or newly created from memory if the pool is empty.
 * Whenever a buffer object is no longer needed, it's automatically returned to the pool within size limit,
 * or freed otherwise.
 *
 * @tparam BufferType type of the buffer object to be pooled, eg: std::string
 * @tparam BufferSizeType size type of the buffer, eg: std::string::size_type
 * @tparam BufferCapacityFunc member function to get the capacity of a buffer object in bytes, eg: &std::string::capacity
 * @tparam BufferClearFunc member function to clear the contents of a buffer object, but retain its underlying capacity, eg: &std::string::clear
 */
template<typename BufferType, typename BufferSizeType, BufferSizeType (BufferType::*BufferCapacityFunc)() const noexcept,
         void (BufferType::*BufferClearFunc)() noexcept>
class BufferPool : public std::enable_shared_from_this<BufferPool<BufferType, BufferSizeType, BufferCapacityFunc, BufferClearFunc>> {
public:
    using PoolPtr = std::shared_ptr<BufferPool>;
    using BufferPtr = std::shared_ptr<BufferType>;

public:
    /**
     * CreateBufferPool is the only way to create a BufferPool object.
     *
     * @param maxPooledByteSize Limit the total size of pooled objects.
     * @return a newly created BufferPool object
     */
    static PoolPtr CreateBufferPool(uint64_t maxPooledByteSize)
    {
        return PoolPtr(new BufferPool(maxPooledByteSize));
    }

    ~BufferPool()
    {
        for (auto buf : pooledBuffers_) {
            delete buf;
        }
    }

    /**
     * GetBuffer returns a buffer object from the pool, or newly created from memory if the pool is empty.
     * Whenever a buffer object is no longer needed, it's automatically returned to the pool within size limit,
     * or freed otherwise.
     *
     * @return a buffer object from the pool, or newly created from memory if the pool is empty
     */
    BufferPtr GetBuffer()
    {
        BufferType* buf;
        if (pooledBuffers_.size() > 0) {
            buf = pooledBuffers_.back();
            pooledBuffers_.pop_back();
            curPooledSize_ -= (buf->*BufferCapacityFunc)();
            (buf->*BufferClearFunc)();
        } else {
            buf = new BufferType;
        }
        return BufferPtr(buf, [weak = BufferPool::weak_from_this()](BufferType* buf) {
            if (auto self = weak.lock(); self != nullptr) {
                self->freeBuffer(buf);
            } else {
                delete buf;
            }
        });
    }

private:
    BufferPool(uint64_t maxPooledSize)
        : maxPooledSize_(maxPooledSize)
        , curPooledSize_(0)
    {
    }

    void freeBuffer(BufferType* buf)
    {
        auto newSize = curPooledSize_ + (buf->*BufferCapacityFunc)();
        if (newSize <= maxPooledSize_) {
            pooledBuffers_.emplace_back(buf);
            curPooledSize_ = newSize;
        } else {
            delete buf;
        }
    }

private:
    const BufferSizeType maxPooledSize_; // Max pooled size in bytes
    BufferSizeType curPooledSize_;       // Currently pooled size in bytes
    std::vector<BufferType*> pooledBuffers_;
};

} // namespace ant

#endif //LIBANT_BUFFER_POOL_H
