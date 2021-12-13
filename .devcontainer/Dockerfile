# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.205.2/containers/debian/.devcontainer/base.Dockerfile

# [Choice] Debian version (use bullseye or stretch on local arm64/Apple Silicon): bullseye, buster, stretch
ARG VARIANT="buster"
FROM mcr.microsoft.com/vscode/devcontainers/base:0-${VARIANT}

# ** [Optional] Uncomment this section to install additional packages. **
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
 && apt-get -y install --no-install-recommends wget cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib automake autoconf build-essential texinfo libtool libftdi-dev libusb-1.0-0-dev

RUN mkdir /pico-sdk \
 && cd /pico-sdk \
 && git clone -b master https://github.com/raspberrypi/pico-sdk.git .\
 && git submodule update --init

ENV  PICO_SDK_PATH=/pico-sdk
