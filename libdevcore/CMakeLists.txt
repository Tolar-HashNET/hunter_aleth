# devcore
file(GLOB ALETH_DEVCORE_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB ALETH_DEVCORE_HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(devcore ${ALETH_DEVCORE_SRC_FILES} ${ALETH_DEVCORE_HDR_FILES})

target_include_directories(
        devcore
        PUBLIC ${ALETH_INCLUDE_DIR}
        PRIVATE ${ALETH_UTILS_DIR})

target_link_libraries(
        devcore
        PUBLIC CONAN_PKG::leveldb
        CONAN_PKG::spdlog
        CONAN_PKG::rocksdb
        CONAN_PKG::ethash
        aleth-buildinfo
        CONAN_PKG::boost
        Threads::Threads)

target_compile_definitions(devcore PRIVATE ALETH_ROCKSDB)
