#include <gtest/gtest.h>
#include "vaapidecoder_h264.h"
#include "vaapidecoder_factory.h"

namespace YamiMediaCodec {

class VaapiDecoderH264Test : public ::testing::Test {
protected:
    bool isFactoryRegistered() const {
        return VaapiDecoderH264::s_registered;
    }
};

#define VAAPIDECODER_H264_TEST(name) \
    TEST_F(VaapiDecoderH264Test, name)

VAAPIDECODER_H264_TEST(FactoryRegistered) {
    EXPECT_TRUE(isFactoryRegistered());
}

VAAPIDECODER_H264_TEST(FactoryCreateFromMIME_AVC) {
    VaapiDecoderFactory::Type decoder(NULL);

    ASSERT_TRUE(decoder == NULL);

    decoder = VaapiDecoderFactory::create(YAMI_MIME_AVC);

    EXPECT_TRUE(decoder != NULL);

    EXPECT_TRUE(dynamic_cast<VaapiDecoderH264*>(decoder));

    delete decoder;
}

VAAPIDECODER_H264_TEST(FactoryCreateFromMIME_H264) {
    VaapiDecoderFactory::Type decoder(NULL);

    ASSERT_TRUE(decoder == NULL);

    decoder = VaapiDecoderFactory::create(YAMI_MIME_H264);

    EXPECT_TRUE(decoder != NULL);

    EXPECT_TRUE(dynamic_cast<VaapiDecoderH264*>(decoder));

    delete decoder;
}

}
