// TI File $Revision: /main/1 $
// Checkin $Date: January 22, 2009   16:47:21 $
//###########################################################################
//
// FILE:   Boot.h
//
// TITLE:  Boot ROM Definitions.
//
//###########################################################################
// $TI Release: TMS320x2803x Boot ROM V1.0 $
// $Release Date: January 22, 2009 $
//###########################################################################

#ifndef TMS320X2803X_BOOT_H
#define TMS320X2803X_BOOT_H

#include "DSP2803x_Device.h"

//---------------------------------------------------------------------------
// Boot Modes
//
//           GPIO37    GPIO34   TRSTn
// 		      TDO      CMP2OUT
// Mode EMU    x         x        1      Emulator connected 
// Mode 0      0         0        0      Parallel I/O
// Mode 1      0         1        0      SCI
// Mode 2      1         0        0      wait
// Mode 3      1         1        0      "Get Mode" 
 
#define OTP_KEY  			0x3D7BFE	     
#define OTP_BMODE 			0x3D7BFF     
#define KEY_VAL          	0x55AA   

//TODO: This says it's the ROM map, but I think these lines below (35-45) are RAM
#define PARALLEL_BOOT       0x0000                                   
#define SCI_BOOT			0x0001
#define WAIT_BOOT           0x0002
#define GET_BOOT    		0x0003

#define SPI_BOOT			0x0004
#define I2C_BOOT			0x0005
#define OTP_BOOT			0x0006
#define BC_CAN_BOOT         0x0007
#define RAM_BOOT			0x000A
#define FLASH_BOOT          0x000B

//---------------------------------------------------------------------------
// Fixed boot entry points:
//
#define FLASH_ENTRY_POINT 0x3F7FF6
#define OTP_ENTRY_POINT   0x3D7800
#define RAM_ENTRY_POINT   0x000000
#define ROM_ENTRY_POINT   0x3FC000

#define DIVSEL_BY_4             0
#define DIVSEL_BY_2             2
#define DIVSEL_BY_1             3

#define ERROR                   1
#define NO_ERROR                0
#define EIGHT_BIT               8
#define SIXTEEN_BIT            16
#define EIGHT_BIT_HEADER   0x08AA
#define SIXTEEN_BIT_HEADER 0x10AA


#define BOOTSTART	0x3E8000
#define BOOTEND 	0x3EA000
//---------------------------------------------------------------------------
//
typedef Uint16 (* uint16fptr)();
extern  uint16fptr GetWordData;
extern  void (*Flash_CallbackPtr) (void);
extern  Uint32 Flash_CPUScaleFactor;

extern  Uint16 EmuKey;
extern  Uint16 EmuBMode;
#define Device_cal (void   (*)(void))0x3D7C80
#define Get_mode   (Uint16 (*)(void))0x3D7CC0

void Boot(Uint16);
void BootInit(Uint16);
void Confirm(Uint16, Uint16);
void Boot_Restart();
Uint16 BC_CAN_GetWordData();
void BC_CAN_Init(Uint16 Node_ID);

#endif  // end of TMS320x2803x_BOOT_H definition
