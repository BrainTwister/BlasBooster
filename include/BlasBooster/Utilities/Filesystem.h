#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#if 1
    #include <boost/filesystem.hpp>
    namespace filesystem = boost::filesystem;
#else
    #include <experimental/filesystem>
    namespace filesystem = std::filesystem;
#endif

#endif /* FILESYSTEM_H_ */
