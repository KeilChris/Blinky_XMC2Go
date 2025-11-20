# Blinky Project for XMC2Go

This project can be used to verify the basic tool setup and hardware connection to the
[Infineon XMC2Go](https://www.keil.arm.com/boards/infineon-xmc-2go-v1-d3962c0/) development board.

The application blinks `LED0` and `LED1` intermittently in a 1 second interval.

Refer to [Project Configuration](#project-configuration) for board specific settings.

## Prerequisites

The following tools need to be installed on your machine:

- [CMSIS-Toolbox v2.12.0](https://github.com/Open-CMSIS-Pack/cmsis-toolbox/releases) or newer
- [Microsoft Visual Studio Code](https://code.visualstudio.com/download) with
  [Keil Studio Pack](https://marketplace.visualstudio.com/items?itemName=Arm.keil-studio-pack) extension (optional,
  alternatively [CLI](#using-command-line-interface-cli) can be used)
- [Arm Compiler 6](https://developer.arm.com/Tools%20and%20Software/Arm%20Compiler%20for%20Embedded) (automatically
  installed when using Visual Studio Code with vcpkg)

## Build solution

### Using Keil Studio

The following is written for [Keil Studio](https://marketplace.visualstudio.com/items?itemName=Arm.keil-studio-pack), a
set of VS Code extensions.

Required tools described in file `vcpkg-configuration.json` should be automatically installed by vcpkg. You can see the
status of vcpkg in the status bar.

Required CMSIS packs need to be also installed. In case a required pack is missing, a notification window will pop-up
to install the missing pack.

Open the **CMSIS view** from the side bar and press the **Build** button.

### Using command line interface (CLI)

Download required packs (not required if the packs are already available) by executing the following commands:

```sh
csolution list packs -s RTX5_Blinky.csolution.yml -m > packs.txt
cpackget update-index
cpackget add -f packs.txt
```

Build the project by executing the following command:

```sh
cbuild RTX5_Blinky.csolution.yml
```

## Run and debug in Keil Studio

### Run

- Connect the board's Micro-USB to the PC (provides also power).
- Open the 'CMSIS' view from the side bar and press the **Run** button and wait until the image is programmed and
  starts running.

### Debug

Open the **CMSIS** view from the side bar and press the **Debug** button. A connection is established via the on-board
[J-Link Lite](https://www.segger.com/products/debug-probes/j-link/models/j-link-lite/j-link-lite-cortex-m/) debug
adapter.

RTOS awareness is available through the **XRTOS** view in the bottom panel.

## Project Configuration

### Keil RTX5 real-time operating system

The real-time operating system [Keil RTX5](https://arm-software.github.io/CMSIS-RTX/latest/index.html) implements
the resource management.

It is configured with the following settings:

- [Global Dynamic Memory size](https://arm-software.github.io/CMSIS-RTX/latest/config_rtx5.html#systemConfig_glob_mem):
  2048 bytes
- [Default Thread Stack size](https://arm-software.github.io/CMSIS-RTX/latest/config_rtx5.html#threadConfig): 128 bytes
- [Idle Thread Stack size](https://arm-software.github.io/CMSIS-RTX/latest/config_rtx5.html#threadConfig): 128 bytes
- [Timer Thread Stack size](hhttps://arm-software.github.io/CMSIS-RTX/latest/config_rtx5.html#timerConfig): 128 bytes
- [Stack Overflow Checking](https://arm-software.github.io/CMSIS-RTX/latest/config_rtx5.html#threadConfig_ovfcheck) and
  [Stack Usage Watermark](https://arm-software.github.io/CMSIS-RTX/latest/config_rtx5.html#threadConfig_watermark)
  enabled

Refer to [Configure RTX v5](https://arm-software.github.io/CMSIS-RTX/latest/config_rtx5.html) for a detailed
description of all configuration options.
