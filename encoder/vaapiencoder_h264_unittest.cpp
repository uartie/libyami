#include <gtest/gtest.h>
#include "vaapiencoder_h264.h"
#include "vaapiencoder_factory.h"

namespace YamiMediaCodec {

class VaapiEncoderH264Test : public ::testing::Test {
protected:
    bool isFactoryRegistered() const {
        return VaapiEncoderH264::s_registered;
    }
};

#define VAAPIENCODER_H264_TEST(name) \
    TEST_F(VaapiEncoderH264Test, name)

VAAPIENCODER_H264_TEST(FactoryRegistered) {
    EXPECT_TRUE(isFactoryRegistered());
}

VAAPIENCODER_H264_TEST(FactoryCreateFromMIME_AVC) {
    VaapiEncoderFactory::Type encoder(NULL);

    ASSERT_TRUE(encoder == NULL);

    encoder = VaapiEncoderFactory::create(YAMI_MIME_AVC);

    EXPECT_TRUE(encoder != NULL);

    EXPECT_TRUE(dynamic_cast<VaapiEncoderH264*>(encoder));

    delete encoder;
}

VAAPIENCODER_H264_TEST(FactoryCreateFromMIME_H264) {
    VaapiEncoderFactory::Type encoder(NULL);

    ASSERT_TRUE(encoder == NULL);

    encoder = VaapiEncoderFactory::create(YAMI_MIME_H264);

    EXPECT_TRUE(encoder != NULL);

    EXPECT_TRUE(dynamic_cast<VaapiEncoderH264*>(encoder));

    delete encoder;
}

}
