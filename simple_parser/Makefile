CC=gcc

CFLAGS=-Wall

all: build

build: parser.c
	$(CC) $(CFLAGS) parser.c -o execs/parser_win10_x64.exe -llibcurl
	 
clean:
	rm -rf execs/*.exe
