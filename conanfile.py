from conans import ConanFile, CMake, tools
import os
import shutil


class TolarAlethConan(ConanFile):
    name = "tolar_aleth"
    license = "GNU General Public License v3.0"
    url = "https://github.com/Tolar-HashNET/hunter_aleth"
    description = "The collection of C++ libraries and tools for Ethereum."
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = ["cmake"]
    requires = [
        "spdlog/1.9.2",
        "boost/1.79.0",
        "snappy/1.1.9",
        "cryptopp/8.2.0",
        "leveldb/1.22",
        "rocksdb/6.20.3",
        "secp256k1/0.1@tolar/stable",
        "libff/0.1@tolar/stable",
        "libscrypt/0.1@tolar/stable",
        "ethash/0.1@tolar/stable",
        "intx/0.1@tolar/stable",
        "jsoncpp/1.9.4"
    ]
    _export_dirs = [
        "aleth",
        "cmake",
        "evmc",
        "libaleth-interpreter",
        "libdevcore",
        "libdevcrypto",
        "libethashseal",
        "libethcore",
        "libethereum",
        "libevm",
        "libp2p",
        "aleth_utils"
    ]
    _destination_lib_dir = "lib"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def export_sources(self):
        source_dir = os.getcwd()

        for export_dir in self._export_dirs:
            shutil.copytree(os.path.join(source_dir, export_dir), os.path.join(self.export_sources_folder, export_dir))

        self.copy("CMakeLists.txt")
        self.copy("LICENSE")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy(pattern="LICENSE", dst="licenses")
        self.copy("*.h", dst="include")
        self.copy("*.hpp", dst="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

        evmc_dir = os.path.join(self.package_folder, "include/evmc")
        evmc_tmp_dir = os.path.join(self.package_folder, "include/tmp_evmc")
        tmp_include_dir = os.path.join(evmc_tmp_dir, "include/evmc")

        shutil.move(evmc_dir, evmc_tmp_dir)
        os.mkdir(evmc_dir)
        self.copy("*.h", dst=evmc_dir, src=tmp_include_dir)
        self.copy("*.hpp", dst=evmc_dir, src=tmp_include_dir)
        shutil.rmtree(evmc_tmp_dir)

    def package_info(self):
        self.cpp_info.components["evmc-instructions"].libs = ["evmc-instructions"]
        self.cpp_info.components["evmc-loader"].libs = ["evmc-loader"]
        self.cpp_info.components["aleth-buildinfo"].libs = ["aleth-buildinfo"]

        self.cpp_info.components["devcore"].libs = ["devcore"]
        self.cpp_info.components["devcore"].requires = ["spdlog::spdlog", "leveldb::leveldb", "rocksdb::rocksdb",
                                                        "ethash::ethash",
                                                        "aleth-buildinfo", "boost::boost"]

        self.cpp_info.components["devcrypto"].libs = ["devcrypto"]
        self.cpp_info.components["devcrypto"].requires = ["devcore", "libscrypt::libscrypt", "secp256k1::secp256k1",
                                                          "libff::libff", "cryptopp::cryptopp"]

        self.cpp_info.components["ethcore"].libs = ["ethcore"]
        self.cpp_info.components["ethcore"].requires = ["devcrypto", "devcore"]

        self.cpp_info.components["p2p"].libs = ["p2p"]
        self.cpp_info.components["p2p"].requires = ["devcrypto", "devcore"]

        self.cpp_info.components["evm"].libs = ["evm"]
        self.cpp_info.components["evm"].requires = ["ethcore", "devcore", "aleth-interpreter", "aleth-buildinfo",
                                                    "jsoncpp::jsoncpp", "boost::boost", "evmc-loader"]

        self.cpp_info.components["ethereum"].libs = ["ethereum"]
        self.cpp_info.components["ethereum"].requires = ["evm", "ethcore", "p2p", "devcrypto", "devcore",
                                                         "jsoncpp::jsoncpp", "snappy::snappy", "boost::boost"]

        self.cpp_info.components["ethashseal"].libs = ["ethashseal"]
        self.cpp_info.components["ethashseal"].requires = ["ethereum", "ethcore", "ethash::ethash"]

        self.cpp_info.components["aleth-interpreter"].libs = ["aleth-interpreter"]
        self.cpp_info.components["aleth-interpreter"].requires = ["devcore", "aleth-buildinfo", "ethash::ethash",
                                                                  "evmc-instructions", "intx::intx", "boost::boost"]

        if self.settings.os == "Linux":
            self.cpp_info.components["evmc-loader"].system_libs = ["dl", "pthread"]
        if tools.is_apple_os(self.settings.os):
            self.cpp_info.components["evmc-loader"].system_libs = ["pthread"]
