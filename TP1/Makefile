CC=gcc
CFLAGS=-c -Wall
OBJS=client/client.o connection/connection.o server/server.o
%.o: %.c
	@echo 'Building $<'
	$(CC) $(CFLAGS) "$<" -o "$@"
	@echo '$< built.'
	@echo ' '

all: client server

client: $(OBJS) main_client.o
	@echo 'Building target $@'
	@echo 'Linking objects'
	$(CC) -o "$@.exe" $(OBJS) main_client.o
	@echo 'Target $@ built'
	@echo ' '

server: $(OBJS) main_server.o
	@echo 'Building target $@'
	@echo 'Linking objects'
	$(CC) -o "$@.exe" $(OBJS) main_server.o
	@echo 'Target $@ built'
	@echo ' '

clean:
	rm -rf $(OBJS) main_client.o main_server.o client.exe server.exe
