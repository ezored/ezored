#include "ezored/helper/SecurityHelper.hpp"

#include "openssl/evp.h"
#include "openssl/pem.h"
#include "openssl/rand.h"
#include "openssl/rsa.h"

#include <cstdio>
#include <string>
#include <vector>

namespace ezored
{
namespace helper
{

std::string SecurityHelper::generateUuidV4()
{
    union
    {
        struct
        {
            uint32_t time_low;
            uint16_t time_mid;
            uint16_t time_hi_and_version;
            uint8_t clk_seq_hi_res;
            uint8_t clk_seq_low;
            uint8_t node[6];
        };

        uint8_t __rnd[16];
    } uuid;

    RAND_bytes(uuid.__rnd, sizeof(uuid));

    // Refer Section 4.2 of RFC-4122
    // https://tools.ietf.org/html/rfc4122#section-4.2
    uuid.clk_seq_hi_res = static_cast<uint8_t>((uuid.clk_seq_hi_res & 0x3F) | 0x80);
    uuid.time_hi_and_version = static_cast<uint16_t>((uuid.time_hi_and_version & 0x0FFF) | 0x4000);

    auto buffer = std::vector<char>(38);

    snprintf(buffer.data(), 38, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
             uuid.time_low, uuid.time_mid, uuid.time_hi_and_version,
             uuid.clk_seq_hi_res, uuid.clk_seq_low,
             uuid.node[0], uuid.node[1], uuid.node[2],
             uuid.node[3], uuid.node[4], uuid.node[5]);

    return std::string(buffer.data());
}

} // namespace helper
} // namespace ezored
