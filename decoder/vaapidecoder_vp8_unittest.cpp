#include <gtest/gtest.h>

#include "vaapidecoder_vp8.h"
#include "vaapidecoder_factory.h"

namespace YamiMediaCodec {

class VaapiDecoderVP8Test : public ::testing::Test {
protected:
    bool isFactoryRegistered() const {
        return VaapiDecoderVP8::s_registered;
    }
};

#define VAAPIDECODER_VP8_TEST(name) \
    TEST_F(VaapiDecoderVP8Test, name)

VAAPIDECODER_VP8_TEST(FactoryRegistered) {
    EXPECT_TRUE(isFactoryRegistered());
}

VAAPIDECODER_VP8_TEST(FactoryCreateFromMIME_VP8) {
    VaapiDecoderFactory::Type decoder(NULL);

    ASSERT_TRUE(decoder == NULL);

    decoder = VaapiDecoderFactory::create(YAMI_MIME_VP8);

    EXPECT_TRUE(decoder != NULL);

    EXPECT_TRUE(dynamic_cast<VaapiDecoderVP8*>(decoder));

    delete decoder;
}

}
