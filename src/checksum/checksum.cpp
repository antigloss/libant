#include <cassert>
#include <libant/checksum/checksum.h>

namespace ant {

uint32_t AddChecksum16(uint32_t currentChecksum, const void* data, size_t dataLen)
{
    // add data altogether
    auto data16 = reinterpret_cast<const uint16_t*>(data);
    while (dataLen > 1) {
        currentChecksum += *(data16++);
        dataLen -= 2;
    }
    if (dataLen) {
        currentChecksum += *reinterpret_cast<const uint8_t*>(data16);
    }
    return currentChecksum;
}

} // namespace ant
