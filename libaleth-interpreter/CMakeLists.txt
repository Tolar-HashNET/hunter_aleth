file(GLOB ALETH_INTERPRETER_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB ALETH_INTERPRETER_HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(aleth-interpreter ${ALETH_INTERPRETER_SRC_FILES} ${ALETH_INTERPRETER_HDR_FILES})

target_include_directories(aleth-interpreter PUBLIC ${ALETH_INCLUDE_DIR})
target_link_libraries(
        aleth-interpreter PRIVATE devcore aleth-buildinfo CONAN_PKG::ethash evmc::evmc
        evmc::instructions CONAN_PKG::intx CONAN_PKG::boost)