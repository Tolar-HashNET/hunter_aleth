include(cmake/conan.cmake)

set(CONAN_CMAKE_SILENT_OUTPUT True)

conan_add_remote(NAME tolar-conan URL https://artifactory.dev.tolar.io/artifactory/api/conan/conan INDEX 0)

conan_cmake_run(
        REQUIRES
        spdlog/1.8.1
        boost/1.74.0
        snappy/1.1.8
        cryptopp/8.2.0
        leveldb/1.22
        rocksdb/6.10.2
        secp256k1/0.1@tolar/stable
        libff/0.1@tolar/stable
        libscrypt/0.1@tolar/stable
        ethash/0.1@tolar/stable
        intx/0.1@tolar/stable
        jsoncpp/1.9.4
        OPTIONS
        boost:shared=False
        snappy:shared=False
        cryptopp:shared=False
        leveldb:shared=False
        rocksdb:shared=False
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing
        SETTINGS compiler.cppstd=17)

