ESP32 specific code.

This code depends on the ESP-IDF toolchain.

## Generating build files.
Since this code isn't supported by the BMPTK++ toolchain, it is required to generate new build files.
This is done by the ESP-IDF toolchain.

To generate the files, run:
```make menuconfig```
(It is assumed that all the PATH variables have been set beforehand)
