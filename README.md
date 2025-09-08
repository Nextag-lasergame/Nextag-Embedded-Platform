# Nextag-Embedded-Platform

## How to build
- Clone repository with submodules
- Install avr-gcc 15.1 (add to PATH). Ensure binutils and avr-libc are present.
- Install CMake and Ninja (or use the Docker flow below).
- Install simavr (add to PATH).
- Configure CMake using:
```sh
cmake -G Ninja -S . -B build/Release -DCMAKE_BUILD_TYPE=Release -DNEXTAG_EMBEDDED_PLATFORM_CONFIGURE_AS_UNO=ON
```
- Build using:
```sh
ninja -C build/Release
```
- Run tests using:
```sh
ctest --test-dir build/Release -C Release --output-on-failure
```

## How to build using docker
Alternatively you can use docker to build Nextag Embedded Platform. The docker container is set up to include the correct 
version of the avr toolchain and simavr. The docker toolchain can be used as follows (the commands assume execution from the root directory from bash):

- Clone repository with submodules
- Build the toolchain docker container using: `docker build -t avr-gcc-toolchain:latest -f Dockerfile . --platform=linux/amd64`
- Configure CMake using: 
```bash
docker run --rm -v $PWD:/Nextag-Embedded-Platform:z avr-gcc-toolchain                     \
  cmake -G Ninja -S /Nextag-Embedded-Platform/ -B /Nextag-Embedded-Platform/build/Release \
  -DCMAKE_BUILD_TYPE=Release -DNEXTAG_EMBEDDED_PLATFORM_CONFIGURE_AS_UNO=ON
```

- Run the build using: 
```sh
docker run --rm -v $PWD:/Nextag-Embedded-Platform:z avr-gcc-toolchain                     \
  ninja -C /Nextag-Embedded-Platform/build/Release
```

- Run the tests using: 
```sh
docker run --rm -v $PWD:/Nextag-Embedded-Platform:z avr-gcc-toolchain                     \
  ctest --test-dir /Nextag-Embedded-Platform/build/Release --output-on-failure
```

## Toolchain
The toolchain is based on [mkleemann/cmake-avr](https://github.com/mkleemann/cmake-avr)