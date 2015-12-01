#include <gtest/gtest.h>
#include <tr1/array>
#include "nalreader.h"

namespace YamiMediaCodec{

#define NALREADER_TEST(name) \
    TEST(NalReaderTest, name)

const std::tr1::array<uint8_t, 39> g_data = {
    0x02, // junk

    0x00, 0x00, 0x01, // start code prefix
    0xff, 0xfe, 0xfd,
    0xfc, 0xfb, 0xfa,

    0x00, 0x00, 0x01, // start code prefix
    0xaa,

    0x00, 0x00, 0x01, // start code prefix
    0xfd, 0xaf, 0x24,

    0x00, 0x00, 0x01, // start code prefix
    0x01, 0x00, 0x00,
    0x1a, 0x01, 0x01,
    0x00, 0x01, 0xbd,

    0x00, 0x00, 0x01, // start code prefix
    0x56, 0x01, 0x84,
    0x12
};

const std::tr1::array<int32_t, 5> g_nsizes = {9, 4, 6, 12, 7};

NALREADER_TEST(ReadAsUnits) {
    const uint8_t* nal;
    int32_t offset(1), size;

    NalReader reader(&g_data[0], g_data.size(), false);

    for (unsigned n(0); n < g_nsizes.size(); ++n) {
        EXPECT_TRUE(reader.read(nal, size));
        EXPECT_EQ(size, g_nsizes[n]);
        for (unsigned i(0); i < size; ++i)
            EXPECT_EQ(nal[i], g_data[i+offset]);
        offset += size;
    }

    EXPECT_FALSE(reader.read(nal, size));
}

NALREADER_TEST(ReadAsWhole) {
    const uint8_t* nal;
    int32_t size;

    NalReader reader(&g_data[0], g_data.size(), true);

    EXPECT_TRUE(reader.read(nal, size));
    EXPECT_EQ(size, g_data.size());

    for (unsigned i(0); i < size; ++i)
        EXPECT_EQ(nal[i], g_data[i]);

    EXPECT_FALSE(reader.read(nal, size));
}

NALREADER_TEST(ReadEmptyBuf) {
    const uint8_t data[] = {};
    const uint8_t* nal;
    int32_t size;

    NalReader reader(data, 0, false);
    EXPECT_FALSE(reader.read(nal, size));

    reader = NalReader(data, 0, true);
    EXPECT_FALSE(reader.read(nal, size));
}

NALREADER_TEST(ReadNoPrefix) {
    const std::tr1::array<uint8_t, 9> data = {
        0x00, 0x01, 0x00,
        0x10, 0x01, 0xfe,
        0x01, 0x00, 0x00
    };
    const uint8_t* nal;
    int32_t size;

    NalReader reader(&data[0], data.size(), false);
    EXPECT_FALSE(reader.read(nal, size));
}

}
