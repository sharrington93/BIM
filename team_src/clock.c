/*
 * clock.c
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan
 */
#include "all.h"


struct CPUTIMER_VARS Clock;
clock_struct Clock_Ticks = CLOCK_TICKS_CLEAR;

void ClockSetup()
{
	Clock.RegsAddr = &CpuTimer1Regs;
	// Initialize timer period to maximum:
	CpuTimer1Regs.PRD.all  = 0xFFFFFFFF;
	// Initialize pre-scale counter to divide by 1 (SYSCLKOUT):
	CpuTimer1Regs.TPR.all  = 0;
	CpuTimer1Regs.TPRH.all = 0;
	// Make sure timer is stopped:
	CpuTimer1Regs.TCR.bit.TSS = 1;
	// Reload all counter register with period value:
	CpuTimer1Regs.TCR.bit.TRB = 1;
	// Reset interrupt counters:
	Clock.InterruptCount = 0;

	ConfigCpuTimer(&Clock,CPU_FREQ_MHZ, CLOCK_PERIOD);

	//pie interrupt
	IER |= M_INT13;

	ReloadCpuTimer1();
	StartCpuTimer1();
}

// Connected to INT13 of CPU (use MINT13 mask):
// ISR can be used by the user.
__interrupt void INT13_ISR(void)     // INT13 or CPU-Timer1
{
	 //***********************************WARNING!!********************************************\\
	//BE CAREFUL YOU NEED TO ALLOW NESTING FOR ANY INTERRUPT THAT MIGHT HAPPEN IN THIS INTERRUPT\\

	 EINT;		//enable all interrupts

	//todo USER: Define Clock ISR
	Clock_Ticks.DataOut++;
	Clock_Ticks.HeartBeat++;

	if (Clock_Ticks.DataOut >= DATAOUT_TICKS)
	{
		//send data or fill data
		SendCAN(Stats1_box);
		SendCAN(Stats2_box);
		SendCAN(Temp3_box);
		SendCAN(Temp2_box);
		SendCAN(Temp1_box);
		Clock_Ticks.DataOut = 0;
	}

	if (Clock_Ticks.HeartBeat >= HEARTBEAT_TICKS)
	{
		HeartBeat();
		Clock_Ticks.HeartBeat = 0;
	}

	ReloadCpuTimer1();
	StartCpuTimer1();

	DINT;
}

void HeartBeat()
{
	FillSendCAN(HEARTBEAT_BOX);
}
