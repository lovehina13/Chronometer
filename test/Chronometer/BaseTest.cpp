#include "BaseTest.h"

#include <chrono>
#include <thread>

void BaseTest::SetUp() {}

void BaseTest::TearDown() {}

void BaseTest::sleep(int microseconds) { std::this_thread::sleep_for(std::chrono::microseconds(microseconds)); }
