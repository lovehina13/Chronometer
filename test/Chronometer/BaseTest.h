#pragma once

#include <gtest/gtest.h>

class BaseTest : public testing::Test {
  protected:
    void SetUp() override;
    void TearDown() override;

    void sleep(int microseconds = 1000);
};
