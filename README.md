## Standalone menuconfig from Linux Kernel
<div align="center">
    <img src="https://jiauzhang.github.io/ghstatic/images/menuconfig.png" >
</div>

### Usage
```shell
# shows help message
menuconfig --help
# menuconfig will save .config in the same folder as YOUR_KCONFIG_FILE
# and generate configuration in include/{generated/,config/}
# default to read ./Kconfig
menuconfig --syncconfig
# manually specify
menuconfig --syncconfig --kconfig YOUR_KCONFIG_FILE
```

### Install dependencies
```shell
./install_deps
```

### Build and Install menuconfig
```shell
mkdir build && cd build
cmake .. && make -j
sudo make install
```

### Sponsor
<table align="center">
    <thead>
        <tr>
            <th colspan="2">公众号</th>
        </tr>
    </thead>
    <tbody align="center" valign="center">
        <tr>
            <td colspan="2"><img src="https://jiauzhang.github.io/ghstatic/images/ofa_m.png" style="height: 196px" alt="AliPay.png"></td>
        </tr>
    </tbody>
    <thead>
        <tr>
            <th>AliPay</th>
            <th>WeChatPay</th>
        </tr>
    </thead>
    <tbody align="center" valign="center">
        <tr>
            <td><img src="https://jiauzhang.github.io/AliPay.png" style="width: 196px; height: 196px" alt="AliPay.png"></td>
            <td><img src="https://jiauzhang.github.io/WeChatPay.png" style="width: 196px; height: 196px" alt="WeChatPay.png"></td>
        </tr>
    </tbody>
</table>
