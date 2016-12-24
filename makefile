CC = gcc
INC = -I./inc
DTC = dtc
PRU_ASM = pasm
#LIB = -L/home/emanuel/Embarcados/LAB_4/buildroot-2016.08.1/output/build/am335x-pru-package-5f374ad57cc195f28bf5e585c3d446aba6ee7096/pru_sw/app_loader/lib/
#CFLAGS = -Wall 

all: folder bin 

bin: sensor.o embedded_linux.o app.o pru.o
	$(CC) -lpthread -lprussdrv obj/app.o obj/embedded_linux.o obj/sensor.o obj/pru.o -o APP/app.bin

app.o:
	$(CC) -o app.o -c $(INC) src/app.c -o obj/app.o	

embedded_linux.o:
	$(CC) -o embedded_linux.o -c $(INC) src/embedded_linux.c -o obj/embedded_linux.o	

sensor.o:
	$(CC) -o sensor.o -c $(INC) src/sensor.c -o obj/sensor.o

pru.o:
	$(CC) -o pru.o -c $(INC) src/pru.c -o obj/pru.o

driver: hcsr04.dts
	$(DTC) -O dtb -o APP/hcsr04-00A0.dtbo -b 0 -@ hcsr04.dts

pru: hcsr04.p
	$(PRU_ASM) -b hcsr04.p
	mv hcsr04.bin APP

install: 
	cp APP/hcsr04-00A0.dtbo /lib/firmware
	echo hcsr04 > /sys/devices/bone_capemgr.9/slots
	cat /sys/devices/bone_capemgr.9/slots	

folder:
	mkdir -p obj APP

send: 
	scp -r APP/* root@192.168.7.2:

clean:
	rm -rf obj APP hcsr04-00A0.dtbo