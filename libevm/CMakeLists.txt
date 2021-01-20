file(GLOB ALETH_EVM_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB ALETH_EVM_HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(evm ${ALETH_EVM_SRC_FILES} ${ALETH_EVM_HDR_FILES})

target_include_directories(evm PUBLIC ${ALETH_INCLUDE_DIR})
target_link_libraries(
        evm
        PUBLIC ethcore
        devcore
        evmc::evmc
        aleth-interpreter
        aleth-buildinfo
        CONAN_PKG::jsoncpp
        CONAN_PKG::boost
        evmc::loader)