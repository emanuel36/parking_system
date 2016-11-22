CC = arm-linux-gnueabihf-gcc

all:
	mkdir -p APP
	$(CC) -I./inc src/*.c -o APP/app.bin
	scp APP/app.bin root@192.168.7.2:/
clean:
	rm -rf APP