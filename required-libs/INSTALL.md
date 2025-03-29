## MSYS Mingw64

```sh
pacman -Syu
```

```sh
pacman -Su
```

```sh
pacman -S mingw-w64-x86_64-libusb mingw-w64-x86_64-fftw mingw-w64-x86_64-swig mingw-w64-x86_64-doxygen mingw-w64-x86_64-python3
```

## Python requirements

```

```

## Install soapy SDR

```sh
cd SoapySDR && mkdir build && cd build
```

```sh
cmake -DSOAPY_SDR_ROOT:PATH="<install_dir>" -DCMAKE_INSTALL_PREFIX:PATH="<install_dir>" ../ -G "MinGW Makefiles" -DCMAKE_POLICY_VERSION_MINIMUM="3.5"
```

```sh
mingw32-make install
```

## Install hackrf 

```sh
cd hackrf && cd host && mkdir build && cd build
```

```sh
cmake ../ -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX:PATH="C:\RadioLibs\shared\hackrf" -DCMAKE_POLICY_VERSION_MINIMUM="3.5"
```