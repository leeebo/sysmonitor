## Sysmonitor Component

[![Component Registry](https://components.espressif.com/components/leeebo/sysmonitor/badge.svg)](https://components.espressif.com/components/leeebo/sysmonitor) [![Build examples](https://github.com/leeebo/sysmonitor/actions/workflows/build_examples.yml/badge.svg?branch=master)](https://github.com/leeebo/sysmonitor/actions/workflows/build_examples.yml)

- [x] taskmonitor
- [x] memmonitor
- [ ] periphmonitor

### Get the Component From Component Registry

1. using `idf.py add-dependency "leeebo/sysmonitor=*"` to add the component to your project
2. copy `sysmonitor/sdkconfig.defaults` to your project (to enable FreeRTOS stats)

### Taskmonitor Functions

1. include `taskmonitor.h` or other monitor header file
2. init with `taskmonitor_init();`
3. `taskmonitor_start();` to start monitor
4. the task info like below will be dumped with default interval 3s
5. you can change the interval in menuconfig

```
This is esp32s3 chip with 2 CPU core(s), WiFi/BLE, silicon revision v0.1, 2MB external flash
I (3318) TaskMonitor: -----------------Task Dump Start-----------------
|Load   Stack   State   CoreID  PRI     Name|
|0.59   704     Running 0       1       Tmr Svc|
|87.14  1944    Ready   0       1       main|
|100.00 808     Ready   1       0       IDLE1|
|12.27  800     Ready   0       0       IDLE0|
|0.00   536     Suspend 0       24      ipc0|
|0.00   528     Suspend 1       24      ipc1|
I (3328) TaskMonitor: Total Free heap: 383704
I (3328) TaskMonitor: -----------------Task Dump End-------------------
```
* Load：CPU Load (single core)
* Stack Left: left stack size
* Name：task name
* PRI：task priority
