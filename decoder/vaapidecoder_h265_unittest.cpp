#include <gtest/gtest.h>
#include <map>

#include "codecparsers/h265parser.h"
#include "vaapidecoder_h265.h"
#include "vaapidecoder_factory.h"

namespace YamiMediaCodec {

class VaapiDecoderH265Test : public ::testing::Test {
protected:
    bool isFactoryRegistered() const {
        return VaapiDecoderH265::s_registered;
    }
};

#define VAAPIDECODER_H265_TEST(name) \
    TEST_F(VaapiDecoderH265Test, name)

VAAPIDECODER_H265_TEST(FactoryRegistered) {
    EXPECT_TRUE(isFactoryRegistered());
}

VAAPIDECODER_H265_TEST(FactoryCreateFromMIME_H265) {
    VaapiDecoderFactory::Type decoder(NULL);

    ASSERT_TRUE(decoder == NULL);

    decoder = VaapiDecoderFactory::create(YAMI_MIME_H265);

    EXPECT_TRUE(decoder != NULL);

    EXPECT_TRUE(dynamic_cast<VaapiDecoderH265*>(decoder));

    delete decoder;
}

}
