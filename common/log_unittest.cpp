#include <gtest/gtest.h>
#include <cstdlib>
#include <sstream>

#include "log.h"

class LogTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        unsetenv("LIBYAMI_LOG_LEVEL");
        unsetenv("LIBYAMI_LOG");
        defaultYamiLogFn = yamiLogFn;
        defaultYamiLogFlag = yamiLogFlag;
    }

    virtual void TearDown() {
        yamiLogFn = defaultYamiLogFn;
        yamiLogFlag = defaultYamiLogFlag;
        isInit = 0;
    }

    FILE* defaultYamiLogFn;
    int defaultYamiLogFlag;
};

#define LOG_TEST(name) \
    TEST_F(LogTest, name)

LOG_TEST(Assert) {
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(ASSERT(false), "(false)");

    EXPECT_DEATH(ASSERT(1 == 0), "(1 == 0)");

    ASSERT(1);
}

LOG_TEST(YamiDebugMessage) {
    yamiLogFlag = YAMI_LOG_DEBUG;

    // FIXME: This causes segmentation fault because yamiLogFn is not set.
    // The YAMI_DEBUG_MESSAGE macro should handle that.
//     YAMI_DEBUG_MESSAGE(DEBUG, "log", "test");
    FAIL();
}

LOG_TEST(YamiTraceInitDefault) {
    yamiTraceInit();

    EXPECT_TRUE(yamiLogFn == stderr);
    EXPECT_EQ(yamiLogFlag, YAMI_LOG_ERROR);
}

LOG_TEST(YamiTraceInitEnvLogLevelDebug) {
    std::stringstream ss;
    ss << YAMI_LOG_DEBUG;

    ASSERT_EQ(setenv("LIBYAMI_LOG_LEVEL", ss.str().c_str(), 1), 0);

    yamiTraceInit();

    EXPECT_TRUE(yamiLogFn == stderr);
    EXPECT_EQ(yamiLogFlag, YAMI_LOG_DEBUG);
}

LOG_TEST(YamiTraceInitEnvLogLevelInfo) {
    std::stringstream ss;
    ss << YAMI_LOG_INFO;

    ASSERT_EQ(setenv("LIBYAMI_LOG_LEVEL", ss.str().c_str(), 1), 0);

    yamiTraceInit();

    EXPECT_TRUE(yamiLogFn == stderr);
    EXPECT_EQ(yamiLogFlag, YAMI_LOG_INFO);
}

LOG_TEST(YamiTraceInitEnvLogLevelWarn) {
    std::stringstream ss;
    ss << YAMI_LOG_WARNING;

    ASSERT_EQ(setenv("LIBYAMI_LOG_LEVEL", ss.str().c_str(), 1), 0);

    yamiTraceInit();

    EXPECT_TRUE(yamiLogFn == stderr);
    EXPECT_EQ(yamiLogFlag, YAMI_LOG_WARNING);
}

LOG_TEST(YamiTraceInitEnvLogLevelErr) {
    std::stringstream ss;
    ss << YAMI_LOG_ERROR;

    ASSERT_EQ(setenv("LIBYAMI_LOG_LEVEL", ss.str().c_str(), 1), 0);

    yamiTraceInit();

    EXPECT_TRUE(yamiLogFn == stderr);
    EXPECT_EQ(yamiLogFlag, YAMI_LOG_ERROR);
}
