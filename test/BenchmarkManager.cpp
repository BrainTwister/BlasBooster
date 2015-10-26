#include "BrainTwister/BenchmarkManager.h"
#include "gtest/gtest.h"
#include <thread>

using namespace BrainTwister;

/// A simple Action initialized with a list of times in microseconds.
struct Action
{
	Action(std::initializer_list<size_t> const& list) : time_list(begin(list), end(list)) {}

	void initialize() const {}
    void execute() const {
    	if (iter_time == time_list.end()) throw std::runtime_error("End of time list reached.");
    	std::this_thread::sleep_for(std::chrono::milliseconds(*iter_time++));
    }
    void check() const {}

private:

    std::vector<size_t> time_list;
    mutable std::vector<size_t>::const_iterator iter_time = time_list.begin();
};

TEST(BenchmarkManager, Action1)
{
	BenchmarkManager::Settings settings;
	settings.minExecutionTime = std::chrono::milliseconds(100);

    BenchmarkManager bm(settings);
    Action action{101, 99, 100};
    BenchmarkManager::Result result = bm.benchIt(action);

    EXPECT_EQ(3UL, result.nbReplications);
    EXPECT_EQ(100, std::chrono::duration_cast<std::chrono::milliseconds>(result.averageTime).count());
    EXPECT_EQ(99, std::chrono::duration_cast<std::chrono::milliseconds>(result.shortestTime).count());
    EXPECT_EQ(101, std::chrono::duration_cast<std::chrono::milliseconds>(result.longestTime).count());
}

TEST(BenchmarkManager, Action2)
{
	BenchmarkManager::Settings settings;
	settings.minReplications = 2;
	settings.minExecutionTime = std::chrono::milliseconds(100);

    BenchmarkManager bm(settings);
    Action action{101, 99};
    BenchmarkManager::Result result = bm.benchIt(action);

    EXPECT_EQ(2UL, result.nbReplications);
    EXPECT_EQ(100, std::chrono::duration_cast<std::chrono::milliseconds>(result.averageTime).count());
}

TEST(BenchmarkManager, SpikeDetection)
{
	BenchmarkManager::Settings settings;
	settings.minExecutionTime = std::chrono::milliseconds(100);

    BenchmarkManager bm(settings);
    Action action{101, 150, 100, 99};
    BenchmarkManager::Result result = bm.benchIt(action);

    EXPECT_EQ(3UL, result.nbReplications);
    EXPECT_EQ(1UL, result.num_spikes);
    EXPECT_EQ(100, std::chrono::duration_cast<std::chrono::milliseconds>(result.averageTime).count());
    EXPECT_EQ(99, std::chrono::duration_cast<std::chrono::milliseconds>(result.shortestTime).count());
    EXPECT_EQ(101, std::chrono::duration_cast<std::chrono::milliseconds>(result.longestTime).count());
}

