CC=gcc
#CC=arm-linux-gcc

all:
	$(CC) -g main.c fx-serial.c  socket_client.c proto/header.pb-c.c proto/getdata.pb-c.c proto/control.pb-c.c protobuf-c/protobuf-c.c -Ipriqueue  -I./proto -o Serial -lpthread

clean:
	rm -rf Serial a.out
