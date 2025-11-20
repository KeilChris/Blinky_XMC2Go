/*---------------------------------------------------------------------------
 * Copyright (c) 2025 Arm Limited (or its affiliates). All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *      Name:    Blinky.c
 *      Purpose: RTX example program
 *
 *---------------------------------------------------------------------------*/

#include "Board_LED.h"
#include <stdio.h>
#include "cmsis_os2.h"

static   osThreadId_t tid_thrLED;       // Thread id of thread: LED
volatile     uint32_t g_ledSet = 0;     // Global variable to store LED values:
                                        // 0 = LED0 off, LED1 off
                                        // 1 = LED0 on,  LED1 off
                                        // 2 = LED0 off, LED1 on
                                        // 3 = LED0 on,  LED1 on

// Create thread attribute to show thread name in the XRTOS viewer:
const osThreadAttr_t app_main_attr = {.name = "MainThread"};
const osThreadAttr_t thrLED_attr   = {.name = "LEDThread"};

/*---------------------------------------------------------------------------
  thrLED: blink LED
 *---------------------------------------------------------------------------*/
__NO_RETURN static void thrLED (void *arg) {

  (void)arg;

  for (;;) {
    LED_On(0);
    g_ledSet = 1;
    osDelay(500);
    LED_On(1);
    g_ledSet = 3;
    osDelay(500);
    LED_Off(0);
    g_ledSet = 2;
    osDelay(500);
    LED_Off(1);
    g_ledSet = 0;
    osDelay(500);
  }
}

/*---------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
static void app_main_thread (void *argument) {
  (void)argument;

  tid_thrLED = osThreadNew(thrLED, NULL, &thrLED_attr);         // Create LED thread
  if (tid_thrLED == NULL) { /* add error handling */ }

  for (;;) {                            // Loop forever
  }
}

/*-----------------------------------------------------------------------------
 * Application initialization
 *----------------------------------------------------------------------------*/
int app_main (void) {
  osKernelInitialize();                         // Initialize CMSIS-RTOS2
  osThreadNew(app_main_thread, NULL, &app_main_attr);  // Create application main thread
  osKernelStart();                              // Start thread execution
  return 0;
}
