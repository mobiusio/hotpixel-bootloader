#include "derivative.h"
#include "spi.h"
#include "ff.h"
#include "diskio.h"
#include "config.h"

//
// function prototypes
//
void SysTick_Handler (void);
void GPIO_Init(void);

__asm void bootloader_launch_application (unsigned long addr) {
	LDR	R1, [R0] // load R1 from addr(SP)
	LDR R2, [R0, #4] // load R2 from addr+4bytes(PC)
	MOV SP, R1 // update SP
	BX R2 // update PC
}

int main (void) {
	
	//
	// just boot application at APP_ADDR, this is where we would 
	// check to see if there is anything on the SD card to update
	// system firmware
	//
	
	bootloader_launch_application(APP_ADDR);
	
	return(0);
}

void SysTick_Handler (void) {
	//
	// this is the systick interrupt handler, it should
	// execute every 10ms (1/SYSTICKS) seconds

	// FatFS routines
	disk_timerproc();

}

void GPIO_Init() {   


  //
	// Enable PORT D as output, these are the high-side row drivers
	//
	
	/* Enable clock gating to PORTD */
  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	PORTD_PCR0 = PORT_PCR_MUX(1);
	PORTD_PCR0 |= PORT_PCR_DSE_MASK; // high drive strength
	PORTD_PCR1 = PORT_PCR_MUX(1);
	PORTD_PCR1 |= PORT_PCR_DSE_MASK;
	PORTD_PCR2 = PORT_PCR_MUX(1);
	PORTD_PCR2 |= PORT_PCR_DSE_MASK;
	PORTD_PCR3 = PORT_PCR_MUX(1);
	PORTD_PCR3 |= PORT_PCR_DSE_MASK;
	PORTD_PCR4 = PORT_PCR_MUX(1);
	PORTD_PCR4 |= PORT_PCR_DSE_MASK;
	PORTD_PCR5 = PORT_PCR_MUX(1);
	PORTD_PCR5 |= PORT_PCR_DSE_MASK;
	PORTD_PCR6 = PORT_PCR_MUX(1);
	PORTD_PCR6 |= PORT_PCR_DSE_MASK;
	PORTD_PCR7 = PORT_PCR_MUX(1);
	PORTD_PCR7 |= PORT_PCR_DSE_MASK;
	
	GPIOD_PDDR |= 0xFF;
	GPIOD_PDOR = 0xFE;
	
	//
	// Configure PORTE, this controls the LED driver enables,
	// the two LEDs, and switches
	//
	
	/* Enable PTE0,1,2 and drive low to set enable LOW */
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	PORTE_PCR0 = PORT_PCR_MUX(1);
	PORTE_PCR0 |= PORT_PCR_DSE_MASK; // high drive strength
	PORTE_PCR1 = PORT_PCR_MUX(1);
	PORTE_PCR1 |= PORT_PCR_DSE_MASK;
	PORTE_PCR2 = PORT_PCR_MUX(1);
	PORTE_PCR2 |= PORT_PCR_DSE_MASK;
	PORTE_PCR29 = PORT_PCR_MUX(1);
	PORTE_PCR29 |= PORT_PCR_DSE_MASK;
	PORTE_PCR30 = PORT_PCR_MUX(1);
	PORTE_PCR30 |= PORT_PCR_DSE_MASK;
	
	GPIOE_PDDR |= 0x60000007; // PTE29, 30 are LED 1,2
	GPIOE_PDOR =  0x400000F8; // |= 0x20000000 to turn on

	#if defined(MCU_MKL25Z4)  
    /* Enable clock gating to PORTA, PORTB, PORTC, PORTD and PORTE */
    SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK 
              | SIM_SCGC5_PORTB_MASK 
              | SIM_SCGC5_PORTC_MASK 
              | SIM_SCGC5_PORTD_MASK 
              | SIM_SCGC5_PORTE_MASK);
#endif
}
