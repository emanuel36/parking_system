#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "embedded_linux.h"

void init_gpio(unsigned int gpio, unsigned int direction){
	FILE* f = NULL;
	f = fopen("/sys/class/gpio/export", "w");
	fprintf(f, "%d", gpio);
	fclose(f);

	//DIRECTION
	char path[50];
	sprintf(path, "/sys/class/gpio/gpio%d/direction", gpio);
	f = fopen(path, "w");
	
	if(direction == OUTPUT){
		fprintf(f, "out");
		fclose(f);	
	}
	else{
		fprintf(f, "in");
		fclose(f);	
	}
}

///INPUT
int get_value(unsigned int gpio){
	FILE* f = NULL;
	char leitura, path[50];
	sprintf(path, "/sys/class/gpio/gpio%d/value", gpio);
	f = fopen(path, "r");
	leitura = fgetc(f);
	fclose(f);
	if(strncmp(&leitura, "1", 1) == 0){
		return 1;
	}else{
		return 0;
	}
}

//OUTPUT
void set_gpio_high(unsigned int gpio){
	FILE* f = NULL;
	char path[50];

	sprintf(path, "/sys/class/gpio/gpio%d/value", gpio);
	f = fopen(path, "w");
	fprintf(f, "1");
	fclose(f);
}

void set_gpio_low(unsigned int gpio){
	FILE* f = NULL;
	char path[50];

	sprintf(path, "/sys/class/gpio/gpio%d/value", gpio);
	f = fopen(path, "w");
	fprintf(f, "0");
	fclose(f);
}

void init_analog_pins(){
	FILE* f = NULL;
	char path[50];

	f = fopen("/sys/devices/platform/bone_capemgr/slots", "w");
	fprintf(f, "BB-ADC");
	fclose(f);
	usleep(500000);
}

int get_value_ain(unsigned int ain){
	FILE* f = NULL;
	char path[50], leitura[5];

	//sprintf(path, "/sys/bus/iio/devices/iio\:device0/in_voltage%d_raw", ain);
	f = fopen(path, "r");
	fgets(leitura, 5, f);
	fclose(f);
	return atoi(leitura);
}