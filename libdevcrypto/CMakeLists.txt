file(GLOB ALETH_DEVCRYPTO_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB ALETH_DEVCRYPTO_HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(devcrypto ${ALETH_DEVCRYPTO_SRC_FILES} ${ALETH_DEVCRYPTO_HDR_FILES})

target_include_directories(
        devcrypto
        PUBLIC ${ALETH_INCLUDE_DIR}
        PRIVATE ${ALETH_UTILS_DIR})

target_link_libraries(
        devcrypto
        PUBLIC devcore CONAN_PKG::secp256k1
        PRIVATE CONAN_PKG::libff CONAN_PKG::cryptopp CONAN_PKG::libscrypt)
