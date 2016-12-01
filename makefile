CC = arm-linux-gnueabihf-gcc
INC = -I./inc
LIB = -L/home/emanuel/Embarcados/LAB_4/buildroot-2016.08.1/output/build/am335x-pru-package-5f374ad57cc195f28bf5e585c3d446aba6ee7096/pru_sw/app_loader/lib/
CFLAGS = -Wall -I/home/emanuel/Embarcados/LAB_4/buildroot-2016.08.1/output/host/usr/arm-buildroot-linux-gnueabihf/sysroot/usr/include

all: folder bin clean send

bin: sensor.o embedded_linux.o app.o pru.o
	$(CC) $(LIB) -lpthread -lprussdrv obj/app.o obj/embedded_linux.o obj/sensor.o obj/pru.o -o APP/app.bin

app.o:
	$(CC) -o app.o -c $(INC) src/app.c -o obj/app.o	

embedded_linux.o:
	$(CC) -o embedded_linux.o -c $(INC) src/embedded_linux.c -o obj/embedded_linux.o	

sensor.o:
	$(CC) -o sensor.o -c $(INC) src/sensor.c -o obj/sensor.o

pru.o:
	$(CC) $(CFLAGS) -o pru.o -c $(INC) src/pru.c -o obj/pru.o

folder:
	mkdir -p obj

send: 
	scp -r APP/ root@192.168.7.2:

clean:
	rm -rf obj