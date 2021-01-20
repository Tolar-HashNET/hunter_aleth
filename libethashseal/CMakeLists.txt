file(GLOB ALETH_ETHASHSEAL_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB ALETH_ETHASHSEAL_HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(ethashseal ${ALETH_ETHASHSEAL_SRC_FILES} ${ALETH_ETHASHSEAL_HDR_FILES})

target_include_directories(
        ethashseal
        PUBLIC ${ALETH_INCLUDE_DIR}
        PRIVATE "${ALETH_UTILS_DIR}")

target_link_libraries(ethashseal PUBLIC ethereum ethcore CONAN_PKG::ethash)
