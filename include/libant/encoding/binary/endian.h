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

#ifndef LIBANT_ENCODING_BINARY_ENDIAN_H_
#define LIBANT_ENCODING_BINARY_ENDIAN_H_

#include <cstdint>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#ifdef __linux__
#include <byteswap.h>
#endif
#endif

namespace ant {

/**
 * Endian type
 */
enum class Endian {
    LittleEndian = 0,
    BigEndian = 1,
};

#ifdef __linux__

/**
 * Endian of this system
 */
constexpr Endian SystemEndian = (__BYTE_ORDER == __LITTLE_ENDIAN) ? Endian::LittleEndian : Endian::BigEndian;

#else

/**
 * Endian of this system
 */
extern Endian SystemEndian;

/* Macros for swapping */
#define ANT_BYTE_SWAP_16(x) ((uint16_t)((((uint16_t)(x)&0xff00U) >> 8) | (((uint16_t)(x)&0x00ffU) << 8)))

#define ANT_BYTE_SWAP_32(x)                                                                                                     \
    ((uint32_t)((((uint32_t)(x)&0xff000000U) >> 24) | (((uint32_t)(x)&0x00ff0000U) >> 8) | (((uint32_t)(x)&0x0000ff00U) << 8) | \
                (((uint32_t)(x)&0x000000ffU) << 24)))

#define ANT_BYTE_SWAP_64(x)                                                                                                                                   \
    ((uint64_t)((((uint64_t)(x)&0xff00000000000000ULL) >> 56) | (((uint64_t)(x)&0x00ff000000000000ULL) >> 40) |                                               \
                (((uint64_t)(x)&0x0000ff0000000000ULL) >> 24) | (((uint64_t)(x)&0x000000ff00000000ULL) >> 8) | (((uint64_t)(x)&0x00000000ff000000ULL) << 8) | \
                (((uint64_t)(x)&0x0000000000ff0000ULL) << 24) | (((uint64_t)(x)&0x000000000000ff00ULL) << 40) |                                               \
                (((uint64_t)(x)&0x00000000000000ffULL) << 56)))

#endif

/**
 * Convert from big endian to little endian or vice versa
 * @param v
 * @return
 */
constexpr int8_t ByteSwap(int8_t v)
{
    return v;
}

constexpr uint8_t ByteSwap(uint8_t v)
{
    return v;
}

inline int16_t ByteSwap(int16_t v)
{
#ifdef __linux__
    return bswap_16(v);
#else
    return ANT_BYTE_SWAP_16(v);
#endif
}

inline uint16_t ByteSwap(uint16_t v)
{
#ifdef __linux__
    return bswap_16(v);
#else
    return ANT_BYTE_SWAP_16(v);
#endif
}

inline int32_t ByteSwap(int32_t v)
{
#ifdef __linux__
    return bswap_32(v);
#else
    return ANT_BYTE_SWAP_32(v);
#endif
}

inline uint32_t ByteSwap(uint32_t v)
{
#ifdef __linux__
    return bswap_32(v);
#else
    return ANT_BYTE_SWAP_32(v);
#endif
}

inline int64_t ByteSwap(int64_t v)
{
#ifdef __linux__
    return bswap_64(v);
#else
    return ANT_BYTE_SWAP_64(v);
#endif
}

inline uint64_t ByteSwap(uint64_t v)
{
#ifdef __linux__
    return bswap_64(v);
#else
    return ANT_BYTE_SWAP_64(v);
#endif
}

/**
 * Convert from big endian to host endian
 * @param v
 * @return
 */
constexpr int8_t BigEndianToHost(int8_t v)
{
    return v;
}

constexpr uint8_t BigEndianToHost(uint8_t v)
{
    return v;
}

inline int16_t BigEndianToHost(int16_t v)
{
    return ntohs(v);
}

inline uint16_t BigEndianToHost(uint16_t v)
{
    return ntohs(v);
}

inline int32_t BigEndianToHost(int32_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::LittleEndian) {
        return bswap_32(v);
    }
#else
    if (SystemEndian == Endian::LittleEndian) {
        return ANT_BYTE_SWAP_32(v);
    }
#endif
    return v;
}

inline uint32_t BigEndianToHost(uint32_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::LittleEndian) {
        return bswap_32(v);
    }
#else
    if (SystemEndian == Endian::LittleEndian) {
        return ANT_BYTE_SWAP_32(v);
    }
#endif
    return v;
}

inline int64_t BigEndianToHost(int64_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::LittleEndian) {
        return bswap_64(v);
    }
#else
    if (SystemEndian == Endian::LittleEndian) {
        return ANT_BYTE_SWAP_64(v);
    }
#endif
    return v;
}

inline uint64_t BigEndianToHost(uint64_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::LittleEndian) {
        return bswap_64(v);
    }
#else
    if (SystemEndian == Endian::LittleEndian) {
        return ANT_BYTE_SWAP_64(v);
    }
#endif
    return v;
}

constexpr int8_t HostToBigEndian(int8_t v)
{
    return v;
}

constexpr uint8_t HostToBigEndian(uint8_t v)
{
    return v;
}

inline int16_t HostToBigEndian(int16_t v)
{
    return htons(v);
}

inline uint16_t HostToBigEndian(uint16_t v)
{
    return htons(v);
}

inline int32_t HostToBigEndian(int32_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::LittleEndian) {
        return bswap_32(v);
    }
#else
    if (SystemEndian == Endian::LittleEndian) {
        return ANT_BYTE_SWAP_32(v);
    }
#endif
    return v;
}

inline uint32_t HostToBigEndian(uint32_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::LittleEndian) {
        return bswap_32(v);
    }
#else
    if (SystemEndian == Endian::LittleEndian) {
        return ANT_BYTE_SWAP_32(v);
    }
#endif
    return v;
}

inline int64_t HostToBigEndian(int64_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::LittleEndian) {
        return bswap_64(v);
    }
#else
    if (SystemEndian == Endian::LittleEndian) {
        return ANT_BYTE_SWAP_64(v);
    }
#endif
    return v;
}

inline uint64_t HostToBigEndian(uint64_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::LittleEndian) {
        return bswap_64(v);
    }
#else
    if (SystemEndian == Endian::LittleEndian) {
        return ANT_BYTE_SWAP_64(v);
    }
#endif
    return v;
}

constexpr int8_t LittleEndianToHost(int8_t v)
{
    return v;
}

constexpr uint8_t LittleEndianToHost(uint8_t v)
{
    return v;
}

inline int16_t LittleEndianToHost(int16_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        return bswap_16(v);
    }
#else
    if (SystemEndian == Endian::BigEndian) {
        return ANT_BYTE_SWAP_16(v);
    }
#endif
    return v;
}

inline uint16_t LittleEndianToHost(uint16_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        return bswap_16(v);
    }
#else
    if (SystemEndian == Endian::BigEndian) {
        return ANT_BYTE_SWAP_16(v);
    }
#endif
    return v;
}

inline int32_t LittleEndianToHost(int32_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        return bswap_32(v);
    }
#else
    if (SystemEndian == Endian::BigEndian) {
        return ANT_BYTE_SWAP_32(v);
    }
#endif
    return v;
}

inline uint32_t LittleEndianToHost(uint32_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        return bswap_32(v);
    }
#else
    if (SystemEndian == Endian::BigEndian) {
        return ANT_BYTE_SWAP_32(v);
    }
#endif
    return v;
}

inline int64_t LittleEndianToHost(int64_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        return bswap_64(v);
    }
#else
    if (SystemEndian == Endian::BigEndian) {
        return ANT_BYTE_SWAP_64(v);
    }
#endif
    return v;
}

inline uint64_t LittleEndianToHost(uint64_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        return bswap_64(v);
    }
#else
    if (SystemEndian == Endian::BigEndian) {
        return ANT_BYTE_SWAP_64(v);
    }
#endif
    return v;
}

constexpr int8_t HostToLittleEndian(int8_t v)
{
    return v;
}

constexpr uint8_t HostToLittleEndian(uint8_t v)
{
    return v;
}

inline int16_t HostToLittleEndian(int16_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        return bswap_16(v);
    }
#else
    if (SystemEndian == Endian::BigEndian) {
        return ANT_BYTE_SWAP_16(v);
    }
#endif
    return v;
}

inline uint16_t HostToLittleEndian(uint16_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        return bswap_16(v);
    }
#else
    if (SystemEndian == Endian::BigEndian) {
        return ANT_BYTE_SWAP_16(v);
    }
#endif
    return v;
}

inline int32_t HostToLittleEndian(int32_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        return bswap_32(v);
    }
#else
    if (SystemEndian == Endian::BigEndian) {
        return ANT_BYTE_SWAP_32(v);
    }
#endif
    return v;
}

inline uint32_t HostToLittleEndian(uint32_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        return bswap_32(v);
    }
#else
    if (SystemEndian == Endian::BigEndian) {
        return ANT_BYTE_SWAP_32(v);
    }
#endif
    return v;
}

inline int64_t HostToLittleEndian(int64_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        return bswap_64(v);
    }
#else
    if (SystemEndian == Endian::BigEndian) {
        return ANT_BYTE_SWAP_64(v);
    }
#endif
    return v;
}

inline uint64_t HostToLittleEndian(uint64_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        return bswap_64(v);
    }
#else
    if (SystemEndian == Endian::BigEndian) {
        return ANT_BYTE_SWAP_64(v);
    }
#endif
    return v;
}

} // namespace ant

#endif //LIBANT_ENCODING_BINARY_ENDIAN_H_
