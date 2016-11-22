#include <stdio.h>
#include <unistd.h>
#include "embedded_linux.h"

#define LED_B		44
#define LED_G		26
#define LED_Y		46
#define LED_R		65
#define BUZZER 		44


void alerta(unsigned int level){
	switch(level){
		case 1:
		set_gpio_low(LED_B);
		set_gpio_low(LED_G);
		set_gpio_low(LED_Y);
		set_gpio_low(LED_R);
		break;

		case 2:
		set_gpio_high(LED_B);
		set_gpio_low(LED_G);
		set_gpio_low(LED_Y);
		set_gpio_low(LED_R);
		break;

		case 3:
		set_gpio_high(LED_B);
		set_gpio_high(LED_G);
		set_gpio_low(LED_Y);
		set_gpio_low(LED_R);
		break;

		case 4:
		set_gpio_high(LED_B);
		set_gpio_high(LED_G);
		set_gpio_high(LED_Y);
		set_gpio_low(LED_R);
		break;

		case 5:
		set_gpio_high(LED_B);
		set_gpio_high(LED_G);
		set_gpio_high(LED_Y);
		set_gpio_high(LED_R);
		break;
	}
}

void init_system(){
	init_analog_pins();
	init_gpio(BUZZER, OUTPUT);
	init_gpio(LED_R, OUTPUT);
	init_gpio(LED_B, OUTPUT);
	init_gpio(LED_G, OUTPUT);
	init_gpio(LED_Y, OUTPUT);

	set_gpio_high(LED_B);
	usleep(100000);
	set_gpio_low(LED_B);
	set_gpio_high(LED_G);
	usleep(100000);
	set_gpio_low(LED_G);
	set_gpio_high(LED_Y);
	usleep(100000);
	set_gpio_low(LED_Y);
	set_gpio_high(LED_R);
	usleep(100000);
	set_gpio_low(LED_R);
	set_gpio_high(LED_Y);
	usleep(100000);
	set_gpio_low(LED_Y);
	set_gpio_high(LED_G);
	usleep(100000);
	set_gpio_low(LED_G);
	set_gpio_high(LED_B);
	usleep(100000);
	set_gpio_low(LED_B);
	usleep(100000);
}

#define DISTANCE_1	3800	
#define DISTANCE_2	3000
#define DISTANCE_3	2000
#define DISTANCE_4	1000
#define DISTANCE_5	500

void main(){
	int distance;
	init_system();
	while(1){
		distance = get_value_ain(0);
		if(distance < DISTANCE_1 && distance > DISTANCE_2){
			alerta(2);
		}
		else if(distance < DISTANCE_2 && distance > DISTANCE_3){
			alerta(3);
		}
		else if(distance < DISTANCE_3 && distance > DISTANCE_5){
			alerta(4);
		} 
		else if(distance < DISTANCE_5){
			alerta(5);
		}else{
			alerta(1);
		}
	}
}