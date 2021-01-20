set(
    sources
    AccountManager.cpp AccountManager.h
    main.cpp
    MinerAux.cpp MinerAux.h
)

add_executable(aleth ${sources})
target_link_libraries(
    aleth
    PRIVATE ethereum ethashseal evm web3jsonrpc webthree devcore CONAN_PKG::boost
)

target_include_directories(aleth PRIVATE ../utils)
