#include <stdio.h>
#include <unistd.h>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include "pru.h"

int init_pru(){
	/* Initialize the PRU */
	tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
	prussdrv_init();

	/* Open PRU Interrupt */
	if (prussdrv_open (PRU_EVTOUT_0)){
		// Handle failure
		return 1;
	}

	/* Get the interrupt initialized */
	prussdrv_pruintc_init(&pruss_intc_initdata);

	/* Get pointers to PRU local memory */
	prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, &pruDataMem);
	pruData = (unsigned int *) pruDataMem;

	/* Execute code on PRU */
	prussdrv_exec_program(0, "hcsr04.bin");
	return(0);
}

float read_distance(){
	prussdrv_pru_wait_event (PRU_EVTOUT_0);
	prussdrv_pru_clear_event(PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);
	return ((float) pruData[0] / 58.44);
}

void pru_disable(){
	/* Disable PRU and close memory mapping*/
	prussdrv_pru_disable(0);
	prussdrv_exit();
	printf(">> PRU Disabled.\r\n");
}