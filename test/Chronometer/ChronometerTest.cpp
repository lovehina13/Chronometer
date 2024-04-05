#include "BaseTest.h"

#include "Chronometer/Chronometer.h"

const std::string name("Chronometer");
const bool automatic(false);

TEST_F(BaseTest, Chronometer_Constructor) {
    Chronometer obj1(name, automatic);
    EXPECT_EQ(obj1.name(), name);
    EXPECT_EQ(obj1.automatic(), automatic);
}

TEST_F(BaseTest, Chronometer_CopyConstructor) {
    Chronometer obj1(name, automatic);
    Chronometer obj2(obj1);
    EXPECT_EQ(obj1.name(), obj2.name());
    EXPECT_EQ(obj1.automatic(), obj2.automatic());
}

TEST_F(BaseTest, Chronometer_MoveConstructor) {
    Chronometer obj1(name, automatic);
    Chronometer obj2(std::move(obj1));
    EXPECT_EQ(obj2.name(), name);
    EXPECT_EQ(obj2.automatic(), automatic);
}

TEST_F(BaseTest, Chronometer_CopyAssignmentOperator) {
    Chronometer obj1(name, automatic);
    Chronometer obj2(std::string(), false);
    obj2 = obj1;
    EXPECT_EQ(obj1.name(), obj2.name());
    EXPECT_EQ(obj1.automatic(), obj2.automatic());
}

TEST_F(BaseTest, Chronometer_MoveAssignmentOperator) {
    Chronometer obj1(name, automatic);
    Chronometer obj2(std::string(), false);
    obj2 = std::move(obj1);
    EXPECT_EQ(obj2.name(), name);
    EXPECT_EQ(obj2.automatic(), automatic);
}

TEST_F(BaseTest, Chronometer_GettersAndSetters) {
    Chronometer obj1(name, automatic);
    obj1.tick();
    EXPECT_EQ(obj1.name(), name);
    EXPECT_EQ(obj1.automatic(), automatic);
    EXPECT_EQ(obj1.state(), Chronometer::State::PAUSED);
    EXPECT_EQ(obj1.ticks().size(), 1);
    EXPECT_EQ(obj1.durations().size(), 1);
    EXPECT_EQ(obj1.duration().count(), 0);
    EXPECT_GT(obj1.text().size(), 0);
}

TEST_F(BaseTest, AutomaticChronometer) {
    const std::string name = "AutomaticChronometer";
    const bool automatic = true;

    Chronometer chronometer(name, automatic);
    EXPECT_EQ(chronometer.name(), name);
    EXPECT_EQ(chronometer.automatic(), automatic);
    EXPECT_EQ(chronometer.state(), Chronometer::State::RUNNING);
    EXPECT_EQ(chronometer.ticks().size(), 1);
    EXPECT_EQ(chronometer.durations().size(), 1);
    sleep();

    chronometer.reset();
    EXPECT_EQ(chronometer.ticks().size(), 1);
    EXPECT_EQ(chronometer.durations().size(), 1);
    sleep();

    chronometer.tick();
    EXPECT_EQ(chronometer.ticks().size(), 2);
    EXPECT_EQ(chronometer.durations().size(), 2);
    sleep();

    chronometer.pause();
    EXPECT_EQ(chronometer.state(), Chronometer::State::PAUSED);
    EXPECT_EQ(chronometer.ticks().size(), 3);
    EXPECT_EQ(chronometer.durations().size(), 3);
    sleep();

    chronometer.resume();
    EXPECT_EQ(chronometer.state(), Chronometer::State::RUNNING);
    EXPECT_EQ(chronometer.ticks().size(), 4);
    EXPECT_EQ(chronometer.durations().size(), 4);
    sleep();

    chronometer.tick();
    EXPECT_EQ(chronometer.ticks().size(), 5);
    EXPECT_EQ(chronometer.durations().size(), 5);
    sleep();

    chronometer.terminate();
    EXPECT_EQ(chronometer.ticks().size(), 6);
    EXPECT_EQ(chronometer.durations().size(), 6);
    sleep();

    Chronometer::Ticks ticks = chronometer.ticks();
    Chronometer::Durations durations = chronometer.durations();
    Chronometer::Duration duration = chronometer.duration();
    std::string text = chronometer.text();
    EXPECT_EQ(ticks.size(), 6);
    EXPECT_EQ(durations.size(), 6);
    EXPECT_EQ(durations.at(0).count(), 0);
    EXPECT_GT(durations.at(1).count(), 0);
    EXPECT_GT(durations.at(2).count(), 0);
    EXPECT_EQ(durations.at(3).count(), 0);
    EXPECT_GT(durations.at(4).count(), 0);
    EXPECT_GT(durations.at(5).count(), 0);
    EXPECT_GT(duration.count(), 0);
    EXPECT_GT(text.size(), 0);
}

TEST_F(BaseTest, ManualChronometer) {
    const std::string name = "ManualChronometer";
    const bool automatic = false;

    Chronometer chronometer(name, automatic);
    EXPECT_EQ(chronometer.name(), name);
    EXPECT_EQ(chronometer.automatic(), automatic);
    EXPECT_EQ(chronometer.state(), Chronometer::State::PAUSED);
    EXPECT_EQ(chronometer.ticks().size(), 0);
    EXPECT_EQ(chronometer.durations().size(), 0);
    sleep();

    chronometer.resume();
    EXPECT_EQ(chronometer.state(), Chronometer::State::RUNNING);
    EXPECT_EQ(chronometer.ticks().size(), 1);
    EXPECT_EQ(chronometer.durations().size(), 1);
    sleep();

    chronometer.tick();
    EXPECT_EQ(chronometer.ticks().size(), 2);
    EXPECT_EQ(chronometer.durations().size(), 2);
    sleep();

    chronometer.pause();
    EXPECT_EQ(chronometer.state(), Chronometer::State::PAUSED);
    EXPECT_EQ(chronometer.ticks().size(), 3);
    EXPECT_EQ(chronometer.durations().size(), 3);
    sleep();

    chronometer.resume();
    EXPECT_EQ(chronometer.state(), Chronometer::State::RUNNING);
    EXPECT_EQ(chronometer.ticks().size(), 4);
    EXPECT_EQ(chronometer.durations().size(), 4);
    sleep();

    chronometer.tick();
    EXPECT_EQ(chronometer.ticks().size(), 5);
    EXPECT_EQ(chronometer.durations().size(), 5);
    sleep();

    chronometer.pause();
    EXPECT_EQ(chronometer.state(), Chronometer::State::PAUSED);
    EXPECT_EQ(chronometer.ticks().size(), 6);
    EXPECT_EQ(chronometer.durations().size(), 6);
    sleep();

    Chronometer::Ticks ticks = chronometer.ticks();
    Chronometer::Durations durations = chronometer.durations();
    Chronometer::Duration duration = chronometer.duration();
    std::string text = chronometer.text();
    EXPECT_EQ(ticks.size(), 6);
    EXPECT_EQ(durations.size(), 6);
    EXPECT_EQ(durations.at(0).count(), 0);
    EXPECT_GT(durations.at(1).count(), 0);
    EXPECT_GT(durations.at(2).count(), 0);
    EXPECT_EQ(durations.at(3).count(), 0);
    EXPECT_GT(durations.at(4).count(), 0);
    EXPECT_GT(durations.at(5).count(), 0);
    EXPECT_GT(duration.count(), 0);
    EXPECT_GT(text.size(), 0);

    chronometer.log();
}
