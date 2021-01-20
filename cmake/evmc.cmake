# cmake-format: off
# NOTE: We can get rid of this file when we switch to minimum cmake 3.18 MSVC is
# currently shipped with 3.17 Feature required: SOURCE_SUBDIR
# FetchContent_Declare

set(EVMC_SRC_DIR "${TOLAR_EVMC_ROOT_DIR}/lib")
set(EVMC_HDR_DIR "${TOLAR_EVMC_ROOT_DIR}/include")

add_library(evmc INTERFACE)
add_library(evmc::evmc ALIAS evmc)
target_include_directories(
  evmc INTERFACE $<BUILD_INTERFACE:${EVMC_HDR_DIR}>$<INSTALL_INTERFACE:include>)

add_library(evmc_cpp INTERFACE)
add_library(evmc::evmc_cpp ALIAS evmc_cpp)
target_include_directories(
  evmc_cpp
  INTERFACE $<BUILD_INTERFACE:${EVMC_HDR_DIR}>$<INSTALL_INTERFACE:include>)
target_link_libraries(evmc_cpp INTERFACE evmc::evmc)

add_library(
  instructions STATIC
  ${EVMC_HDR_DIR}/evmc/instructions.h
  ${EVMC_SRC_DIR}/instructions/instruction_metrics.c
  ${EVMC_SRC_DIR}/instructions/instruction_names.c)

add_library(evmc::instructions ALIAS instructions)
set_target_properties(instructions PROPERTIES OUTPUT_NAME evmc-instructions
                                              POSITION_INDEPENDENT_CODE TRUE)
target_include_directories(
  instructions
  PUBLIC $<BUILD_INTERFACE:${EVMC_HDR_DIR}>$<INSTALL_INTERFACE:include>)

add_library(loader STATIC ${EVMC_HDR_DIR}/evmc/loader.h
                          ${EVMC_SRC_DIR}/loader/loader.c)

add_library(evmc::loader ALIAS loader)
set_target_properties(loader PROPERTIES OUTPUT_NAME evmc-loader
                                        POSITION_INDEPENDENT_CODE TRUE)
target_link_libraries(
  loader
  INTERFACE ${CMAKE_DL_LIBS}
  PUBLIC evmc::evmc)

# cmake-format: on
