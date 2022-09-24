#!bin/bash
echo "Tested On WSL Ubuntu-22.04"
apt-get update && apt-get upgrade -y
apt install -y \
        build-essential \
        cmake \
        x11-apps \
        ccache \
        clang \
        clang-format \
        clang-tidy \
        cppcheck \
        curl \
        doxygen \
        gcc \
        git \
        graphviz \
        make \
        ninja-build \
        python3 \
        python-is-python3 \
        tar \
        zip \
        unzip \
        vcpkg \
        catch2