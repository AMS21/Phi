#!/bin/bash

# Stop on first error
set -e

upgraded_pip=0
added_llvm_apt=0
root_dir=$(pwd)

cmake_build_flags="-O3 -DNDEBUG -w -march=native -mtune=native"

# Make sure pip is using the latest version
upgrade_pip() {
    if [[ "$upgraded_pip" == 0 ]]; then
        echo "-- Upgrading pip..."

        sudo -H pip3 install --upgrade pip
        upgraded_pip=1

        echo "-- Upgrading pip done"
    fi
}

add_llvm_apt() {
    if [[ "$added_llvm_apt" == 0 ]]; then
        echo "-- Adding LLVM-$1 apt..."
        # Get gpg key
        wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -

        os_release=$(lsb_release -c -s)
        apt_repo="https://apt.llvm.org/$os_release/ llvm-toolchain-$os_release-$1 main"
        echo "Adding the apt repo: $apt_repo"

        # Add the required repo
        sudo add-apt-repository "deb $apt_repo"

        # Update repo list
        echo "-- Updating apt..."
        sudo apt-get update -m
        echo "-- Updating apt done"

        echo "-- Adding LLVM-$1 apt done"
    fi
}

install_gcovr() {
    upgrade_pip

    echo "-- Installing gcovr..."
    sudo -H pip3 install gcovr
    echo "-- Installing gcovr done"

    # Verify
    echo "-- Verifying gcovr..."
    gcovr --version
    echo "-- Verifying gcovr done"
}

install_cmake_format() {
    upgrade_pip

    echo "-- Installing cmake-format..."
    # See https://cmake-format.readthedocs.io/en/latest/installation.html#installation
    sudo -H pip3 install cmakelang pyyaml
    echo "-- Installing cmake-format done"

    # Verify
    echo "-- Verifying cmake-format..."
    cmake-format --version
    echo "-- Verifying cmake-format done"
}

# Expects first parameter to be the requested version
install_clang() {
    add_llvm_apt "$1"

    # Install clang
    echo "-- Installing clang-$1..."
    sudo apt-get install "clang-$1" "clang++-$1" g++-multilib -y
    echo "-- Installing clang-$1 done"

    # Verify versions
    echo "-- Verify clang-$1..."
    "clang-$1" --version
    echo "-- Verify clang-$1 done"

    echo "-- Verify clang++-$1..."
    "clang++-$1" --version
    echo "-- Verify clang++-$1 done"

    # Export values
    # shellcheck disable=SC2129
    echo "CLANG=clang-$1" >>"$GITHUB_ENV"
    echo "CLANGXX=clang++-$1" >>"$GITHUB_ENV"

    echo "GCOV_EXECUTABLE=llvm-cov-$1 gcov" >>"$GITHUB_ENV"

    echo "CC=clang-$1" >>"$GITHUB_ENV"
    echo "CXX=clang++-$1" >>"$GITHUB_ENV"
}

# Expects first parameter to the the requested version
install_gcc() {
    echo "-- Installing gcc-$1..."
    sudo apt-get install "gcc-$1" "g++-$1" "gcc-$1-multilib" "g++-$1-multilib" -y
    echo "-- Installing gcc-$1 done"

    # Verify versions
    echo "-- Verify gcc-$1..."
    "gcc-$1" --version
    echo "-- Verify gcc-$1 done"

    echo "-- Verify g++-$1..."
    "g++-$1" --version
    echo "-- Verify g++-$1 done"

    # Export values
    # shellcheck disable=SC2129
    echo "GCC=gcc-$1" >>"$GITHUB_ENV"
    echo "GXX=g++-$1" >>"$GITHUB_ENV"

    echo "GCOV_EXECUTABLE=gcov-$1" >>"$GITHUB_ENV"

    echo "CC=gcc-$1" >>"$GITHUB_ENV"
    echo "CXX=g++-$1" >>"$GITHUB_ENV"
}

install_valgrind() {
    echo "-- Installing valgrind..."
    sudo apt-get install valgrind -y
    echo "-- Installing valgring done"

    # Verify
    echo "-- Verifying valgrind..."
    valgrind --version
    echo "-- Verifying valgrind done"
}

# Expects first parameter to the the requested version
install_cppcheck() {
    mkdir cppcheck -p

    # Download archive
    echo "-- Downloading cppcheck..."
    wget --no-check-certificate -O - "https://github.com/danmar/cppcheck/archive/$1.tar.gz" | tar --strip-components=1 -xz -C cppcheck
    echo "-- Downloading cppcheck done"

    # Build CppCheck
    echo "-- Building cppcheck..."
    cd cppcheck || exit

    mkdir build -p
    cd build || exit

    cmake .. -DCMAKE_BUILD_TYPE:STRING="Release" -DUSE_MATCHCOMPILER:BOOL=ON -DHAVE_RULES:BOOL=ON -DCMAKE_CXX_FLAGS:STRING="$cmake_build_flags"
    cmake --build . "-j$(nproc)"
    echo "-- Building cppcheck done"

    # Install CppCheck
    echo "-- Installing cppcheck..."
    sudo make install
    echo "-- Installing cppcheck done"

    # Verify
    echo "-- Verifying cppcheck..."
    cppcheck --version
    echo "-- Verifiying cppcheck done"

    # Export values
    echo "CPPCHECK=cppcheck" >>"$GITHUB_ENV"
    echo "CPPCHECK_VERSION=$1" >>"$GITHUB_ENV"

    cd "$root_dir" || exit
}

# Expects first parameter to the requested version
install_clang_tidy() {
    add_llvm_apt "$1"

    echo "-- Installing clang-tidy-$1..."
    sudo apt-get install "clang-tidy-$1" -y

    # Verify
    echo "-- Verifying clang-tidy-$1..."
    "clang-tidy-$1" --version
    echo "-- Verifiying clang-tidy-$1 done"

    # Export values
    echo "CLANG_TIDY=clang-tidy-$1" >>"$GITHUB_ENV"
    echo "CLANG_TIDY_VERSION=$1" >>"$GITHUB_ENV"

    echo "-- Installing clang-tidy-$1 done"
}

install_llvm() {
    add_llvm_apt "$1"

    # Make sure we also install clang
    install_clang "$1"

    echo "-- Installing llvm-$1..."
    sudo apt-get install "llvm-$1" "llvm-$1-dev" "libclang-$1" "libclang-$1-dev" -y

    # Export values
    echo "LLVM_VERSION=$1" >>"$GITHUB_ENV"

    echo "-- Installing llvm-$1 done"
}

install_iwyu() {
    # Install the appropriate llvm version
    install_llvm "$1"

    echo "-- Cloning iwyu..."
    git clone https://github.com/include-what-you-use/include-what-you-use.git
    echo "-- Cloning iwyu done"

    # Checkut branch
    cd "include-what-you-use" || exit
    git checkout "clang_$1"

    echo "-- Building iwyu..."
    mkdir build -p
    cd build || exit

    cmake .. -DCMAKE_PREFIX_PATH:STRING="/usr/lib/llvm-$1" -DCMAKE_BUILD_TYPE:STRING="Release" -DCMAKE_CXX_FLAGS:STRING="$cmake_build_flags"
    cmake --build . "-j$(nproc)"
    echo "-- Building iwyu done"

    # Install
    echo "-- Installing iwyu..."
    sudo make install
    echo "-- Installing iwyu done"

    # Verify
    echo "-- Verifying iwyu..."
    include-what-you-use --version
    iwyu_tool.py -help
    echo "-- Verifying iwyu done"

    # Export values
    echo "IWYU_VERSION=$1" >>"$GITHUB_ENV"

    cd "$root_dir" || exit
}

install_pvs_studio() {
    # Get gpg key
    echo "-- Adding viva64 repo..."
    wget -q -O - https://files.viva64.com/etc/pubkey.txt | sudo apt-key add
    sudo wget -O /etc/apt/sources.list.d/viva64.list https://files.viva64.com/etc/viva64.list
    echo "-- Adding viva64 repo done"

    # Udpate repo list
    sudo apt-get update

    echo "-- Installing pvs-studio..."
    sudo apt-get install pvs-studio -y
    echo "-- Installing pvs-studio done"

    # Verify
    echo "-- Verifying pvs-studio..."
    # NOTE pvs-studio doens't support a --version flag so we use which
    which pvs-studio-analyzer
    echo "-- Verifying pvs-studio done"
}

install_mull() {
    echo "-- Setting up mull-$1..."
    # https://mull.readthedocs.io/en/latest/Installation.html#install-on-ubuntu
    curl -1sLf 'https://dl.cloudsmith.io/public/mull-project/mull-stable/setup.deb.sh' | sudo -E bash

    # Update repo list
    sudo apt-get update

    echo "-- Setting up mull-$1 done"

    echo "-- Installing mull-$1..."
    sudo apt-get install "mull-$1" -y
    echo "-- Installing mull-$1 done"

    # Verify
    echo "-- Verifying mull-$1..."
    "mull-runner-$1" --version
    echo "-- Verifying mull-$1 done"

    # Export values
    echo "MULL_RUNNER=mull-runner-$1" >>"$GITHUB_ENV"
}

install_clang_format() {
    add_llvm_apt "$1"

    echo "-- Installing clang-format..."
    sudo apt-get install "clang-format-$1" -y
    echo "-- Installing clang-format done"

    # Verify
    echo "-- Verifying clang-format-$1..."
    "clang-format-$1" --version
    echo "-- Verifying clang-format-$1 done"

    # Export values
    echo "CLANG_FORMAT=clang-format-$1" >>"$GITHUB_ENV"
    echo "CLANG_FORMAT_VERSION=$1" >>"$GITHUB_ENV"
}

install_ninja() {
    echo "-- Installing ninja..."
    sudo apt-get install ninja-build -y
    echo "-- Installing ninja done"

    # Verify
    echo "-- Verifying ninja..."
    ninja --version
    echo "-- Verifying ninja done"
}

for tool in "$@"; do
    if [[ "$tool" == "gcovr" ]]; then
        install_gcovr
    elif [[ "$tool" == "cmake-format" ]]; then
        install_cmake_format
    elif [[ "$tool" == gcc-* ]]; then
        install_gcc "${tool:4}"
    elif [[ "$tool" == "valgrind" ]]; then
        install_valgrind
    elif [[ "$tool" == cppcheck-* ]]; then
        install_cppcheck "${tool:9}"
    elif [[ "$tool" == clang-tidy-* ]]; then
        install_clang_tidy "${tool:11}"
    elif [[ "$tool" == clang-format-* ]]; then
        install_clang_format "${tool:13}"
    elif [[ "$tool" == llvm-* ]]; then
        install_llvm "${tool:5}"
    elif [[ "$tool" == clang-* ]]; then
        install_clang "${tool:6}"
    elif [[ "$tool" == iwyu-* ]]; then
        install_iwyu "${tool:5}"
    elif [[ "$tool" == pvs-studio ]]; then
        install_pvs_studio
    elif [[ "$tool" == mull-* ]]; then
        install_mull "${tool:5}"
    elif [[ "$tool" == ninja ]]; then
        install_ninja
    else
        echo "!- Unknown tool '$tool'"
        exit 1
    fi
done
