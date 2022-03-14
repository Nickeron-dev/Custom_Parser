CC=gcc

CFLAGS=-Wall -Wextra -Wpedantic -std=c11

site=www.google.com
export site

all: build

build: parser.c
	$(CC) $(CFLAGS) parser.c -o execs/parser_win10_x64.exe -lcurl

run: execs/parser_win10_x64.exe
	./execs/parser_win10_x64.exe $(site)
	 
clean:
	rm -rf execs/*.exe
