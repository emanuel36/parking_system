#include <stdio.h>
#include <unistd.h>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include "pru.h"

int init_pru(){
	/* Initialize the PRU */
	tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
	//printf("prussdrv_init();\n");
	prussdrv_init();

	/* Open PRU Interrupt */
	//printf("prussdrv_open (PRU_EVTOUT_0)\n");
	if (prussdrv_open (PRU_EVTOUT_0)){
		// Handle failure
		//printf("ERRO NA INICIALIZACAO PRU");
		return 1;
	}

	/* Get the interrupt initialized */
	//printf("prussdrv_pruintc_init(&pruss_intc_initdata);\n");
	prussdrv_pruintc_init(&pruss_intc_initdata);

	/* Get pointers to PRU local memory */
	//printf("prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, &pruDataMem);\n");
	prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, &pruDataMem);
	pruData = (unsigned int *) pruDataMem;

	/* Execute code on PRU */
	//printf("prussdrv_exec_program(0, 'hcsr04.bin');\n");
	prussdrv_exec_program(0, "hcsr04.bin");
	printf("INIT\n");
	return(0);
}

float read_distance(){
	printf("LEITURA\n");
	prussdrv_pru_wait_event (PRU_EVTOUT_0);
	prussdrv_pru_clear_event(PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);
	printf("FIM LEITURA\n");
	return ((float) pruData[0] / 58.44);
}

void pru_disable(){
	/* Disable PRU and close memory mapping*/
	prussdrv_pru_disable(0);
	prussdrv_exit();
}