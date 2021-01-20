file(GLOB ALETH_ETHCORE_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB ALETH_ETHCORE_HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(ethcore ${ALETH_ETHCORE_SRC_FILES} ${ALETH_ETHCORE_HDR_FILES})

target_include_directories(
        ethcore
        PUBLIC ${ALETH_INCLUDE_DIR}
        PRIVATE "${ALETH_UTILS_DIR}")
target_link_libraries(ethcore PUBLIC devcore devcrypto)
