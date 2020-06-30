# Monitor-Task Example

## How to use example

Follow detailed instructions provided specifically for this example. 

Select the instructions depending on Espressif chip installed on your development board:

- [ESP32 Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/stable/get-started/index.html)
- [ESP32-S3 Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/index.html)

## Example folder contents

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt` files that provide set of directives and instructions describing the project's source files and targets (executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── taskmonitor_main.c
└── README.md                  This is the file you are currently reading
```

For more information on structure and contents of ESP-IDF projects, please refer to Section [Build System](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html) of the ESP-IDF Programming Guide.

## Building and running the code

1. Run `idf.py menuconfig` if you want to change the default configuration.
2. Run `idf.py set-target esp32` or `idf.py set-target esp32s3` to select the target chip.
3. Run `idf.py build` to build the project.
4. Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

## Example Output

```
This is esp32s3 chip with 2 CPU core(s), WiFi/BLE, silicon revision v0.1, 2MB external flash
I (3318) TaskMonitor: -----------------Task Dump Start-----------------
|Load   Stack left      Name    PRI|
|0.00   2288            Tmr Svc 1|
|86.72  1976            main    1|
|98.64  808             IDLE1   0|
|12.09  800             IDLE0   0|
|1.19   528             ipc1    24|
|1.18   536             ipc0    24|
I (3328) TaskMonitor: Total Free heap: 383704
I (3328) TaskMonitor: -----------------Task Dump End-------------------
```
* Load：CPU Load (Single Core)
* Stack Left: Left stack size
* Name：task name
* PRI：task priority

## Troubleshooting

* Program upload failure

    * Hardware connection is not correct: run `idf.py -p PORT monitor`, and reboot your board to see if there are any output logs.
    * The baud rate for downloading is too high: lower your baud rate in the `menuconfig` menu, and try again.

