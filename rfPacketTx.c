/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/***** Includes *****/
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* Drivers */
#include <ti/drivers/rf/RF.h>
#include <ti/drivers/PIN.h>
#include <ti/drivers/GPIO.h>

#include "ti-lib.h"
/* Board Header files */
#include "Board.h"

#include "smartrf_settings/smartrf_settings.h"

/* Pin driver handle */
static PIN_Handle ledPinHandle;
static PIN_State ledPinState;

/*
 * Application LED pin configuration table:
 *   - All LEDs board LEDs are off.
 */
PIN_Config pinTable[] =
{
 Board_LED0 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
 Board_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
 Board_LED2 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
 Board_LED3 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
 Board_INPUT_SW_ENABLE | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,

 Board_DIP_SW_A1 | PIN_INPUT_EN | PIN_HYSTERESIS | PIN_PULLUP,
 Board_DIP_SW_A2 | PIN_INPUT_EN | PIN_HYSTERESIS | PIN_PULLUP,
 Board_DIP_SW_A3 | PIN_INPUT_EN | PIN_HYSTERESIS | PIN_PULLUP,
 Board_DIO1 | PIN_INPUT_EN | PIN_HYSTERESIS,

    PIN_TERMINATE
};


/***** Defines *****/
#define TX_TASK_STACK_SIZE 1024
#define TX_TASK_PRIORITY   2

/* Packet TX Configuration */
#define PAYLOAD_LENGTH      30//30
//#define PACKET_INTERVAL     (uint32_t)(4000000*0.5f) /* Set packet interval to 500ms */
#define PACKET_INTERVAL     (uint32_t)(4000000*1.0f) /* Set packet interval to 1000ms */


/***** Prototypes *****/
static void txTaskFunction(UArg arg0, UArg arg1);
static void ledTaskFunction(UArg arg0, UArg arg1);


/***** Variable declarations *****/
static Task_Params txTaskParams, ledTaskParams;
Task_Struct txTask, ledTask;    /* not static so you can see in ROV */
static uint8_t txTaskStack[TX_TASK_STACK_SIZE];
static uint8_t ledTaskStack[TX_TASK_STACK_SIZE];

static RF_Object rfObject;
static RF_Handle rfHandle;

uint32_t time;
static uint8_t packet[PAYLOAD_LENGTH];
static uint16_t seqNumber;
static PIN_Handle pinHandle;

void Led_init()
{
        Task_Params_init(&ledTaskParams);
        ledTaskParams.stackSize = TX_TASK_STACK_SIZE;
        ledTaskParams.priority = TX_TASK_PRIORITY;
        ledTaskParams.stack = &ledTaskStack;
        ledTaskParams.arg0 = (UInt)1000000;

        Task_construct(&ledTask, ledTaskFunction, &ledTaskParams, NULL);
}

static void ledTaskFunction(UArg arg0, UArg arg1)
{
    int i, j;
    while (1)
    {
        if(i >= 2)
            i = 0;

        for(j = 0; j < 4; j++)
            PIN_setOutputValue(ledPinHandle, (Board_LED0 + j), 0);
            PIN_setOutputValue(ledPinHandle, (Board_LED0 + i++), 1);

        Task_sleep(20000);
    }
}

/***** Function definitions *****/
void TxTask_init(PIN_Handle inPinHandle)
{
    pinHandle = inPinHandle;

    Task_Params_init(&txTaskParams);
    txTaskParams.stackSize = TX_TASK_STACK_SIZE;
    txTaskParams.priority = TX_TASK_PRIORITY;
    txTaskParams.stack = &txTaskStack;
    txTaskParams.arg0 = (UInt)1000000;

    Task_construct(&txTask, txTaskFunction, &txTaskParams, NULL);
}

static void txTaskFunction(UArg arg0, UArg arg1)
{
    uint32_t time;
    uint8_t pwr;
    RF_Params rfParams;
    RF_Params_init(&rfParams);

    RF_cmdPropTx.pktLen = PAYLOAD_LENGTH;
    RF_cmdPropTx.pPkt = packet;
    RF_cmdPropTx.startTrigger.triggerType = TRIG_ABSTIME;
    RF_cmdPropTx.startTrigger.pastTrig = 1;
    RF_cmdPropTx.startTime = 0;

    /* Request access to the radio */
    rfHandle = RF_open(&rfObject, &RF_prop, (RF_RadioSetup*)&RF_cmdPropRadioDivSetup, &rfParams);

    /* Set the frequency */
    RF_postCmd(rfHandle, (RF_Op*)&RF_cmdFs, RF_PriorityNormal, NULL, 0);

    /* Get current time */
    time = RF_getCurrentTime();
    while(1)
    {
        /* Create packet with incrementing sequence number and random payload */
        packet[0] = (uint8_t)(seqNumber >> 8);
        packet[1] = (uint8_t)(seqNumber++);

        /*
        uint_t adr1 = PIN_getInputValue(Board_DIP_SW_A1);
        uint_t adr2 = PIN_getInputValue(Board_DIP_SW_A2);
        //uint_t adr3 = PIN_getInputValue(Board_DIP_SW_A3);
        PIN_setOutputValue(pinHandle, Board_INPUT_SW_ENABLE,1);
        uint_t adr3 = PIN_getInputValue(Board_DIO1);
        PIN_setOutputValue(pinHandle, Board_INPUT_SW_ENABLE,0);
        packet[2] = adr1;
        packet[3] = adr2;
        packet[4] = !adr3;
        */

//printf ("\npaket poslan");
//pwr = EasyLink_GetRfPwr();
        uint8_t i;

        //ti_lib_gpio_clear_dio(BOARD_IOID_DINPUT_READ_EN);
        //val.byteReg = (readValue >> BOARD_IOID_DINPUT1);
        //  вычитка адреса устройства
        packet[2] = 0;
        packet[2] |= ti_lib_gpio_read_dio (IOID_19);
        packet[2] |= ti_lib_gpio_read_dio (IOID_20) << 1;
        packet[2] |= ti_lib_gpio_read_dio (IOID_21) << 2;
        packet[2] |= ti_lib_gpio_read_dio (IOID_22) << 3;
        packet[2] |= ti_lib_gpio_read_dio (IOID_23) << 4;
        packet[2] |= ti_lib_gpio_read_dio (IOID_24) << 5;
        packet[2] |= ti_lib_gpio_read_dio (IOID_25) << 6;
        packet[2] |= ti_lib_gpio_read_dio (IOID_26) << 7;
        packet[2] = ~packet[5];

        //  вычитка входов
        ti_lib_gpio_set_dio(IOID_13);
        packet[6] = 0;
        packet[6] |= ti_lib_gpio_read_dio (IOID_1);
        packet[6] |= ti_lib_gpio_read_dio (IOID_2) << 1;
        packet[6] |= ti_lib_gpio_read_dio (IOID_3) << 2;
        packet[6] |= ti_lib_gpio_read_dio (IOID_4) << 3;
        packet[6] |= ti_lib_gpio_read_dio (IOID_5) << 4;
        packet[6] |= ti_lib_gpio_read_dio (IOID_6) << 5;
        ti_lib_gpio_clear_dio(IOID_13);


        for (i = 7; i < PAYLOAD_LENGTH; i++)
        {
            //packet[i] = rand();
            packet[i] = 255;
            //packet[i] = 1;
        }

        /* Set absolute TX time to utilize automatic power management */
        time += PACKET_INTERVAL;
        RF_cmdPropTx.startTime = time;

        /* Send packet */
        //PIN_setOutputValue(pinHandle, Board_LED3, 1);

        RF_EventMask result = RF_runCmd(rfHandle, (RF_Op*)&RF_cmdPropTx, RF_PriorityNormal, NULL, 0);
        if (!(result & RF_EventLastCmdDone))
        {
            /* Error */
            while(1);
        }

        //PIN_setOutputValue(pinHandle, Board_LED3,0);
        PIN_setOutputValue(pinHandle, Board_LED3,!PIN_getOutputValue(Board_LED3));
        //--->
        printf ("\nSent packet: ");
        for (i = 0; i < PAYLOAD_LENGTH; i++) printf("0x%02X ", (uint8_t )packet[i]);
        //<---
    }
}

/*
 *  ======== main ========
 */
int main(void)
{
    /* Call board init functions. */
    Board_initGeneral();
    //GPIO_init();

    /* Open LED pins */
    ledPinHandle = PIN_open(&ledPinState, pinTable);
    if(!ledPinHandle)
    {
        System_abort("Error initializing board LED pins\n");
    }

    /* Initialize task */
    printf ("\nBefore TxTask_init");
    TxTask_init(ledPinHandle);
    printf ("\nAfter TxTask_init");
    //Led_init();

    /* Start BIOS */
    printf ("\nBefore BIOS_start");
    BIOS_start();
    printf ("\nAfter BIOS_start");

    return (0);
}

