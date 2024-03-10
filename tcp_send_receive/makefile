CC = gcc
CFLAGS = -Wall

all: serveurTCP clientTCP

serveurTCP: serveurTCP.c
	$(CC) $(CFLAGS) serveurTCP.c -o serveurTCP

clientTCP: clientTCP.c
	$(CC) $(CFLAGS) clientTCP.c -o clientTCP


.PHONY: clean
clean:
	rm -f serveurTCP clientTCP

# example of use
# 1st terminal ./serveurTCP 5555 
# 2nd terminal ./clientTCP 0.0.0.0 5555 "hi there"
