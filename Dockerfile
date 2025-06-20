FROM ubuntu:24.04

LABEL authors="Tim Herreijgers"

RUN apt-get update  \
    && apt-get install -y cmake \
    build-essential \
    ninja-build \
    gdb \
    wget \
    python3 \
    simavr \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/ZakKemble/avr-gcc-build/releases/download/v14.1.0-1/avr-gcc-14.1.0-x64-linux.tar.bz2
RUN mkdir /avr-toolchain/
RUN tar -xf avr-gcc-14.1.0-x64-linux.tar.bz2 -C /avr-toolchain
RUN rm avr-gcc-14.1.0-x64-linux.tar.bz2

ENV PATH="$PATH:/avr-toolchain/avr-gcc-14.1.0-x64-linux/bin"
