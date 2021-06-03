#include "fixtures/InitializationFixture.hpp"
#include "gtest/gtest.h"

// initialization test
TEST_F(InitializationFixture, Initialization)
{
    EXPECT_EQ(coreIsInitialized, true);
}

// version test
TEST_F(InitializationFixture, Version)
{
    auto version = ApplicationCore::shared()->getVersion();
    EXPECT_EQ(version, "1.0.0");
}