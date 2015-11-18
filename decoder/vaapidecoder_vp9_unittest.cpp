#include <gtest/gtest.h>

#include "vaapidecoder_vp9.h"
#include "vaapidecoder_factory.h"

namespace YamiMediaCodec {

class VaapiDecoderVP9Test : public ::testing::Test {
protected:
    bool isFactoryRegistered() const {
        return VaapiDecoderVP9::s_registered;
    }
};

#define VAAPIDECODER_VP9_TEST(name) \
    TEST_F(VaapiDecoderVP9Test, name)

VAAPIDECODER_VP9_TEST(FactoryRegistered) {
    EXPECT_TRUE(isFactoryRegistered());
}

VAAPIDECODER_VP9_TEST(FactoryCreateFromMIME_VP9) {
    VaapiDecoderFactory::Type decoder(NULL);

    ASSERT_TRUE(decoder == NULL);

    decoder = VaapiDecoderFactory::create(YAMI_MIME_VP9);

    EXPECT_TRUE(decoder != NULL);

    EXPECT_TRUE(dynamic_cast<VaapiDecoderVP9*>(decoder));

    delete decoder;
}

}
