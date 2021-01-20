file(GLOB ALETH_ETHEREUM_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB ALETH_ETHEREUM_HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(ethereum ${ALETH_ETHEREUM_SRC_FILES} ${ALETH_ETHEREUM_HDR_FILES})

target_include_directories(
        ethereum
        PUBLIC ${ALETH_INCLUDE_DIR}
        PRIVATE "${ALETH_UTILS_DIR}")

target_link_libraries(
        ethereum
        PUBLIC evm ethcore p2p devcrypto devcore
        PRIVATE CONAN_PKG::jsoncpp CONAN_PKG::snappy CONAN_PKG::boost)

