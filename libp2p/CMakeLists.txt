file(GLOB ALETH_P2P_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB ALETH_P2P_HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(p2p ${ALETH_P2P_SRC_FILES} ${ALETH_P2P_HDR_FILES})
target_include_directories(p2p PUBLIC ${ALETH_INCLUDE_DIR})
target_link_libraries(p2p PUBLIC devcrypto devcore PRIVATE CONAN_PKG::cryptopp)