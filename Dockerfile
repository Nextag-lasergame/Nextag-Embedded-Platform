FROM ubuntu:24.04

LABEL authors="Tim Herreijgers"

RUN apt-get update  \
    && apt-get install -y cmake \
    build-essential \
    ninja-build \
    gdb \
    curl \
    python3 \
    simavr \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN curl -L https://github.com/ZakKemble/avr-gcc-build/releases/download/v15.1.0-1/SHA256SUMS -o SHA256SUMS
RUN curl -L https://github.com/ZakKemble/avr-gcc-build/releases/download/v15.1.0-1/avr-gcc-15.1.0-x64-linux.tar.bz2 \
    -o avr-gcc-15.1.0-x64-linux.tar.bz2
RUN sha256sum --ignore-missing -c SHA256SUMS


RUN mkdir /avr-toolchain/
RUN tar -xf avr-gcc-15.1.0-x64-linux.tar.bz2 -C /avr-toolchain
RUN rm avr-gcc-15.1.0-x64-linux.tar.bz2
RUN rm SHA256SUMS

ENV PATH="$PATH:/avr-toolchain/avr-gcc-15.1.0-x64-linux/bin"