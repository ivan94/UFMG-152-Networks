CC=gcc
CFLAGS=-c -Wall -g
OBJS=client/client.o connection/connection.o server/server.o
%.o: %.c
	@echo 'Building $<'
	$(CC) $(CFLAGS) "$<" -o "$@"
	@echo '$< built.'
	@echo ' '

all: client.exe server.exe testgen

client.exe: $(OBJS) main_client.o
	@echo 'Building target $@'
	@echo 'Linking objects'
	$(CC) -o "$@" $(OBJS) main_client.o
	@echo 'Target $@ built'
	@echo ' '

server.exe: $(OBJS) main_server.o
	@echo 'Building target $@'
	@echo 'Linking objects'
	$(CC) -o "$@" $(OBJS) main_server.o
	@echo 'Target $@ built'
	@echo ' '

testgen: testgen.o
	@echo 'Building target $@'
	@echo 'Linking objects'
	$(CC) -o "$@" testgen.o
	@echo 'Target $@ built'
	@echo ' '

clean:
	rm -rf $(OBJS) main_client.o main_server.o client.exe server.exe testgen
