#pragma once

#if 1
    #include <boost/filesystem.hpp>
    namespace filesystem = boost::filesystem;
#else
    #include <experimental/filesystem>
    namespace filesystem = std::experimental::filesystem;
#endif

