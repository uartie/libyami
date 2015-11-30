#include <gtest/gtest.h>
#include "vaapiencoder_vp8.h"
#include "vaapiencoder_factory.h"

namespace YamiMediaCodec {

class VaapiEncoderVP8Test : public ::testing::Test {
protected:
    bool isFactoryRegistered() const {
        return VaapiEncoderVP8::s_registered;
    }
};

#define VAAPIENCODER_VP8_TEST(name) \
    TEST_F(VaapiEncoderVP8Test, name)

VAAPIENCODER_VP8_TEST(FactoryRegistered) {
    EXPECT_TRUE(isFactoryRegistered());
}

VAAPIENCODER_VP8_TEST(FactoryCreateFromMIME_VP8) {
    VaapiEncoderFactory::Type encoder(NULL);

    ASSERT_TRUE(encoder == NULL);

    encoder = VaapiEncoderFactory::create(YAMI_MIME_VP8);

    EXPECT_TRUE(encoder != NULL);

    EXPECT_TRUE(dynamic_cast<VaapiEncoderVP8*>(encoder));

    delete encoder;
}

}
