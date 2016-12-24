#include <stdio.h>
#include "sensor.h"
#include "pru.h"

int main(){
	init_system();
	int distance;
	while(1){
		distance = read_distance();
		printf("%d\n", distance);
		switch(distance){
			case 0 ... 9:
				alerta(5);
				display(0);
			break;

			case 10 ... 19:
				alerta(4);
				display(1);
			break;

			case 20 ... 29:
				alerta(4);
				display(2);
			break;

			case 30 ... 39:
				alerta(4);
				display(3);
			break;

			case 40 ... 49:
				alerta(3);
				display(4);
			break;

			case 50 ... 59:
				alerta(3);
				display(5);
			break;

			case 60 ... 69:
				alerta(3);
				display(6);
			break;

			case 70 ... 79:
				alerta(2);
				display(7);
			break;

			case 80 ... 89:
				alerta(2);
				display(8);
			break;

			case 90 ... 99:
				alerta(2);
				display(9);
			break;

			default:
				alerta(1);
				display(10);
			break;
		}
	}
	pru_disable();
	return 0;
}