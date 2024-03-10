CC = gcc
CFLAGS = -Wall

all: sender-udp receiver-udp

sender-udp: sender-udp.c
	$(CC) $(CFLAGS) sender-udp.c -o sender-udp

receiver-udp: receiver-udp.c
	$(CC) $(CFLAGS) receiver-udp.c -o receiver-udp


.PHONY: clean
clean:
	rm -f sender-udp receiver-udp

# example of use
# 1st terminal ./receiver-udp 5555
# 2nd terminal ./sender-udp 0.0.0.0 5555 "hello there!"
