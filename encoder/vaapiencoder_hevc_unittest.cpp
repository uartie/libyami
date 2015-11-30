#include <gtest/gtest.h>
#include "vaapiencoder_hevc.h"
#include "vaapiencoder_factory.h"

namespace YamiMediaCodec {

class VaapiEncoderHEVCTest : public ::testing::Test {
protected:
    bool isFactoryRegistered() const {
        return VaapiEncoderHEVC::s_registered;
    }
};

#define VAAPIENCODER_HEVC_TEST(name) \
    TEST_F(VaapiEncoderHEVCTest, name)

VAAPIENCODER_HEVC_TEST(FactoryRegistered) {
    EXPECT_TRUE(isFactoryRegistered());
}

VAAPIENCODER_HEVC_TEST(FactoryCreateFromMIME_HEVC) {
    VaapiEncoderFactory::Type encoder(NULL);

    ASSERT_TRUE(encoder == NULL);

    encoder = VaapiEncoderFactory::create(YAMI_MIME_HEVC);

    EXPECT_TRUE(encoder != NULL);

    EXPECT_TRUE(dynamic_cast<VaapiEncoderHEVC*>(encoder));

    delete encoder;
}

VAAPIENCODER_HEVC_TEST(FactoryCreateFromMIME_H265) {
    VaapiEncoderFactory::Type encoder(NULL);

    ASSERT_TRUE(encoder == NULL);

    encoder = VaapiEncoderFactory::create(YAMI_MIME_H265);

    EXPECT_TRUE(encoder != NULL);

    EXPECT_TRUE(dynamic_cast<VaapiEncoderHEVC*>(encoder));

    delete encoder;
}

}
