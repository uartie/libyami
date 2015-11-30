#include <gtest/gtest.h>
#include "vaapiencoder_jpeg.h"
#include "vaapiencoder_factory.h"

namespace YamiMediaCodec {

class VaapiEncoderJpegTest : public ::testing::Test {
protected:
    bool isFactoryRegistered() const {
        return VaapiEncoderJpeg::s_registered;
    }
};

#define VAAPIENCODER_JPEG_TEST(name) \
    TEST_F(VaapiEncoderJpegTest, name)

VAAPIENCODER_JPEG_TEST(FactoryRegistered) {
    EXPECT_TRUE(isFactoryRegistered());
}

VAAPIENCODER_JPEG_TEST(FactoryCreateFromMIME_JPEG) {
    VaapiEncoderFactory::Type encoder(NULL);

    ASSERT_TRUE(encoder == NULL);

    encoder = VaapiEncoderFactory::create(YAMI_MIME_JPEG);

    EXPECT_TRUE(encoder != NULL);

    EXPECT_TRUE(dynamic_cast<VaapiEncoderJpeg*>(encoder));

    delete encoder;
}

}
