## standalone menuconfig from linux kernel

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
