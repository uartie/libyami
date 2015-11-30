#include <gtest/gtest.h>

#include "vaapidecoder_jpeg.h"
#include "vaapidecoder_factory.h"

namespace YamiMediaCodec {

class VaapiDecoderJpegTest : public ::testing::Test {
protected:
    bool isFactoryRegistered() const {
        return VaapiDecoderJpeg::s_registered;
    }
};

#define VAAPIDECODER_JPEG_TEST(name) \
    TEST_F(VaapiDecoderJpegTest, name)

VAAPIDECODER_JPEG_TEST(FactoryRegistered) {
    EXPECT_TRUE(isFactoryRegistered());
}

VAAPIDECODER_JPEG_TEST(FactoryCreateFromMIME_JPEG) {
    VaapiDecoderFactory::Type decoder(NULL);

    ASSERT_TRUE(decoder == NULL);

    decoder = VaapiDecoderFactory::create(YAMI_MIME_JPEG);

    EXPECT_TRUE(decoder != NULL);

    EXPECT_TRUE(dynamic_cast<VaapiDecoderJpeg*>(decoder));

    delete decoder;
}

}
