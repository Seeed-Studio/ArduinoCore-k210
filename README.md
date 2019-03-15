# ArduinoCore-k210

```
git clone https://github.com/kendryte/kendryte-freertos-sdk
git clone https://github.com/seeed-Studio/ArduinoCore-k210 kendryte-freertos-sdk/src
mkdir build && cd build
cmake .. -DPROJ=ArduinoCore-k210 -DTOOLCHAIN=/opt/kendryte-toolchain/bin && make -j8
```