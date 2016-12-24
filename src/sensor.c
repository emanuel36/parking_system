#include <stdio.h>
#include <unistd.h>
#include "sensor.h"
#include "embedded_linux.h"
#include "pru.h"

void init_system(){
	init_pru();
	init_gpio(BUZZER, OUTPUT);
	init_gpio(LED_R, OUTPUT);
	init_gpio(LED_B, OUTPUT);
	init_gpio(LED_G, OUTPUT);
	init_gpio(LED_Y, OUTPUT);
	init_gpio(CLK, OUTPUT);
	init_gpio(LOAD, OUTPUT);
	init_gpio(MSG, OUTPUT);

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
		set_gpio_high(BUZZER);
		usleep(50000);
		set_gpio_low(BUZZER);
		usleep(230000);
		break;

		case 3:
		set_gpio_high(LED_B);
		set_gpio_high(LED_G);
		set_gpio_low(LED_Y);
		set_gpio_low(LED_R);
		set_gpio_high(BUZZER);
		usleep(50000);
		set_gpio_low(BUZZER);
		usleep(150000);
		break;

		case 4:
		set_gpio_high(LED_B);
		set_gpio_high(LED_G);
		set_gpio_high(LED_Y);
		set_gpio_low(LED_R);
		set_gpio_high(BUZZER);
		usleep(50000);
		set_gpio_low(BUZZER);
		usleep(90000);
		break;

		case 5:
		set_gpio_high(LED_B);
		set_gpio_high(LED_G);
		set_gpio_high(LED_Y);
		set_gpio_high(LED_R);
		set_gpio_high(BUZZER);
		break;
	}
}

void send_spi(int msg){
	int i;
	msg = msg << 1; //IGNORA O OITAVO BIT
	set_gpio_low(LOAD);
	for(i = 8; i > 0; i--){
		set_gpio_low(CLK);
		if(msg & 0x1)	set_gpio_high(MSG);
		else			set_gpio_low(MSG);
		set_gpio_high(CLK);
		msg = msg >> 1;
	}
	set_gpio_high(LOAD);
}

void display(int number){
	switch(number){
		case 0:
		send_spi(0b1111110);
		break;
		
		case 1:
		send_spi(0b0110000);
		break;		

		case 2:
		send_spi(0b1101101);
		break;

		case 3:
		send_spi(0b1111001);
		break;

		case 4:
		send_spi(0b0110011);
		break;

		case 5:
		send_spi(0b1011011);
		break;

		case 6:
		send_spi(0b1011111);
		break;

		case 7:
		send_spi(0b1110010);
		break;

		case 8:
		send_spi(0b1111111);
		break;

		case 9:
		send_spi(0b1111011);
		break;

		default:
		send_spi(0b0000001);
		break;
	}
}