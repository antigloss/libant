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

#endif

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
    return ntohl(v);
}

inline uint32_t BigEndianToHost(uint32_t v)
{
    return ntohl(v);
}

inline int64_t BigEndianToHost(int64_t v)
{
#ifdef __linux__
    return be64toh(v);
#else
    return ntohll(v);
#endif
}

inline uint64_t BigEndianToHost(uint64_t v)
{
#ifdef __linux__
    return be64toh(v);
#else
    return ntohll(v);
#endif
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
    return htonl(v);
}

inline uint32_t HostToBigEndian(uint32_t v)
{
    return htonl(v);
}

inline int64_t HostToBigEndian(int64_t v)
{
#ifdef __linux__
    return htobe64(v);
#else
    return htonll(v);
#endif
}

inline uint64_t HostToBigEndian(uint64_t v)
{
#ifdef __linux__
    return htobe64(v);
#else
    return htonll(v);
#endif
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
        v = bswap_16(v);
    }
#else
#endif
    return v;
}

inline uint16_t LittleEndianToHost(uint16_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        v = bswap_16(v);
    }
#else
#endif
    return v;
}

inline int32_t LittleEndianToHost(int32_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        v = bswap_32(v);
    }
#else
#endif
    return v;
}

inline uint32_t LittleEndianToHost(uint32_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        v = bswap_32(v);
    }
#else
#endif
    return v;
}

inline int64_t LittleEndianToHost(int64_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        v = bswap_64(v);
    }
#else
#endif
    return v;
}

inline uint64_t LittleEndianToHost(uint64_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        v = bswap_64(v);
    }
#else
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
        v = bswap_16(v);
    }
#else
#endif
    return v;
}

inline uint16_t HostToLittleEndian(uint16_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        v = bswap_16(v);
    }
#else
#endif
    return v;
}

inline int32_t HostToLittleEndian(int32_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        v = bswap_32(v);
    }
#else
#endif
    return v;
}

inline uint32_t HostToLittleEndian(uint32_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        v = bswap_32(v);
    }
#else
#endif
    return v;
}

inline int64_t HostToLittleEndian(int64_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        v = bswap_64(v);
    }
#else
#endif
    return v;
}

inline uint64_t HostToLittleEndian(uint64_t v)
{
#ifdef __linux__
    if constexpr (SystemEndian == Endian::BigEndian) {
        v = bswap_64(v);
    }
#else
#endif
    return v;
}



} // namespace ant

#endif //LIBANT_ENCODING_BINARY_ENDIAN_H_
