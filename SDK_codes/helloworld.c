/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "OV_7670.h"
#include "xil_types.h"
#include "xstatus.h"
#include "xil_io.h"
int main()
{
    init_platform();

    print("Hello World\n\r");


    while(1){
    	//OV_7670_mWriteReg(0x43C00000, 4, 0x80000000); //camera



    	int pixels = OV_7670_mReadReg(0x43C00000, 0);

		int onlyred   = pixels & 0x00000f00;//3840-3584-3328-3072-2816-2560-2304-2048-1792-1536-1280-1024-768-512-256
		int onlygreen = pixels & 0x000000f0;//240-224-208-192-176-160-144-128-112-96-80-64-48-32-16
		int onlyblue  = pixels & 0x0000000f;//15-0



		//if (onlyred<3584) onlyred = 3584;
		if (onlygreen>160) onlygreen = 160;
		//if (onlyblue>12) onlyblue = 12;
		int value = 0x00000000 | onlyred | onlygreen | onlyblue  ;
		OV_7670_mWriteReg(0x43C00000, 4, value);
		//int r2b= blue * 256;
		//int r2g = green * 16;
		//int g2r= red / 16;
		//int g2b= blue * 16;
		//int b2g= green / 16;
		//int b2r= red / 256;
		//int value = 0x00000000 | b2r | r2b | green ;
		//xil_printf("red : %d, green : %d, blue : %d\n\r",onlyred,green,onlyblue);
		//xil_printf("red : %d, green : %d, blue : %d\n\r",r2b,green,b2r);
		//OV_7670_mWriteReg(0x43C00000, 4, value);
    	//sleep(1);

    }
    cleanup_platform();
    return 0;
}
