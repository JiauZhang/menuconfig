## Standalone menuconfig from Linux Kernel
<div align="center">
    <img src="https://jiauzhang.github.io/ghstatic/images/menuconfig.png" >
</div>

### Usage
```shell
# menuconfig will save .config in the same folder as YOUR_KCONFIG_FILE
# and generate headers in include/generated/*
# default to read ./Kconfig
menuconfig
# manually specify
menuconfig --kconfig YOUR_KCONFIG_FILE
```

### Install dependencies
```shell
./install_deps
```

### Build and Install menuconfig
```shell
mkdir build && cd build
cmake .. && make menuconfig
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
            <td colspan="2"><img src="https://www.chatqkv.com/ghstatic/images/ofa_m.png" style="height: 196px" alt="AliPay.png"></td>
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
            <td><img src="https://www.chatqkv.com/AliPay.png" style="width: 196px; height: 196px" alt="AliPay.png"></td>
            <td><img src="https://www.chatqkv.com/WeChatPay.png" style="width: 196px; height: 196px" alt="WeChatPay.png"></td>
        </tr>
    </tbody>
</table>
