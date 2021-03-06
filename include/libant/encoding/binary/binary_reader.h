#ifndef LIBANT_ENCODING_BINARY_BINARY_READER_H_
#define LIBANT_ENCODING_BINARY_BINARY_READER_H_

#include <string>
#include <string_view>

#include "endian.h"

namespace ant {

/**
 * Decode data from a binary stream.
 *
 * @tparam endian endian of the binary stream to be decoded
 */
template<Endian endian>
class BinaryReader {
public:
    /**
     * Construct a BinaryReader object from `stream`.
     *
     * @param stream
     */
    BinaryReader(std::string_view& stream)
        : buf_(stream)
        , pos_(0)
    {
    }

    /**
     * Construct a BinaryReader object from `data` of length `dataLen`.
     *
     * @param stream
     */
    BinaryReader(const void* data, size_t dataLen)
        : buf_(reinterpret_cast<const char*>(data), dataLen)
        , pos_(0)
    {
    }

    /**
     * Reads an integer from the binary stream into `val`.
     *
     * @tparam T supported integer types are int8, uint8, int16, uint16, int32, uint32, int64, and uint64
     * @param val
     *
     * @return true on success, false on failure.
     */
    template<typename T>
    bool ReadInteger(T& val)
    {
        auto finalPos = pos_ + sizeof(T);
        if (finalPos <= buf_.size()) {
            if constexpr (endian == Endian::LittleEndian) {
                val = LittleEndianToHost(*reinterpret_cast<const T*>(&buf_[pos_]));
            } else {
                val = BigEndianToHost(*reinterpret_cast<const T*>(&buf_[pos_]));
            }
            pos_ = finalPos;
            return true;
        }
        return false;
    }

    /**
     * Reads the remaining bytes of the binary stream into `val`.
     *
     * @param val
     */
    void ReadString(std::string& val)
    {
        val.clear();
        val.append(&buf_[pos_], buf_.size() - pos_);
        pos_ = buf_.size();
    }

    /**
     * Reads length of the string of type `StringLenType` first, then reads the string payload according to the length into `val`.
     *
     * @tparam StringLenType type of the length of the string encoded before the string payload
     * @param val
     *
     * @return true on success, false on failure.
     */
    template<typename StringLenType>
    bool ReadString(std::string& val)
    {
        StringLenType len;
        if (ReadInteger(len) && len >= 0) {
            auto finalPos = pos_ + len;
            if (finalPos <= buf_.size()) {
                val.clear();
                val.append(&buf_[pos_], len);
                pos_ = finalPos;
                return true;
            }
        }
        return false;
    }

    const void* RemainingData() const
    {
        if (buf_.size() > pos_) {
            return buf_.data() + pos_;
        }
        return nullptr;
    }

    size_t RemainingLength() const
    {
        return buf_.size() - pos_;
    }

private:
    std::string_view buf_;
    std::string_view::size_type pos_;
};

} // namespace ant

#endif //LIBANT_ENCODING_BINARY_BINARY_READER_H_
