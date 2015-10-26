BenchmarkManager
================

Copyright 2015 BrainTwister - All rights reserved.

BenchmarkManager is free software made available under the MIT License. For details see the LICENSE file.

Requirements
------------

- cmake (Version >= 3.0, http://www.cmake.org)
- gtest (Optional, but recommended, https://code.google.com/p/googletest)

Description
-----------

Benchmarking is a recurring task of software development with always the same requirements:

- The time measurement shall be executed serval times to get a reliable result.
- Outliers shall be detected.

The BenchmarkManager provides 

``` C++

struct Action
{
    void initialize() const
    { /* */ }
    void execute() const
    { /* */ }
    void check() const
    { /* */ }
};

```

and call the BenchmarkManager:

``` C++

BenchmarkManager::Settings settings;
settings.minExecutionTime = std::chrono::milliseconds(1);

BenchmarkManager bm(settings);
Action action{1001, 999, 1000};
BenchmarkManager::Result result = bm.benchIt(action);

```
