# Aleth: Ethereum C++ client, tools and libraries.
# Copyright 2013-2019 Aleth Authors.
# Licensed under the GNU General Public License, Version 3. See the LICENSE file.
cmake_minimum_required(VERSION 3.17)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain.cmake)

project(aleth)
set(PROJECT_VERSION 1.8.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)
include(cmake/conan_deps.cmake)

set(TOLAR_EVMC_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/evmc")
include(cmake/evmc.cmake)

set(ALETH_INCLUDE_DIR ${CMAKE_SOURCE_DIR})
set(ALETH_UTILS_DIR ${CMAKE_SOURCE_DIR}/aleth_utils)

# aleth-buildinfo
add_library(aleth-buildinfo ${CMAKE_CURRENT_SOURCE_DIR}/aleth/buildinfo.c ${CMAKE_CURRENT_SOURCE_DIR}/aleth/buildinfo.h)

# devcore
add_subdirectory(libdevcore)
# devcrypto
add_subdirectory(libdevcrypto)
# ethcore
add_subdirectory(libethcore)
# p2p
add_subdirectory(libp2p)
# evm
add_subdirectory(libevm)
# ethereum
add_subdirectory(libethereum)
# ethashseal
add_subdirectory(libethashseal)
# aleth-interpreter
add_subdirectory(libaleth-interpreter)
