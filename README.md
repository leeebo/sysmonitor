## Sysmonitor Component

- [x] taskmonitor
- [ ] memmonitor
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
* Load：CPU Load (single core)
* Stack Left: left stack size
* Name：task name
* PRI：task priority
