## standalone menuconfig from linux kernel

### usage
```shell
# menuconfig will save .config in the same folder as YOUR_KCONFIG_FILE
# and generate headers in include/generated/*
# default to read ./Kconfig
menuconfig
# manually specify
menuconfig --kconfig YOUR_KCONFIG_FILE
```

### install dependencies
```shell
./install_deps
```

### build and install menuconfig
```shell
mkdir build && cd build
cmake .. && make menuconfig
sudo make install
```
