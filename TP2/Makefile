CC=gcc
CFLAGS=-c -Wall -g
OBJS=src/socket/socket.o src/server/server.o src/client/client.o
%.o: %.c
	@echo 'Building $<'
	$(CC) $(CFLAGS) "$<" -o "$@"
	@echo '$< built.'
	@echo ' '

all: server client

client.exe: $(OBJS) main_client.o
	@echo 'Building target $@'
	@echo 'Linking objects'
	$(CC) -o "$@" $(OBJS) main_client.o
	@echo 'Target $@ built'
	@echo ' '

server: $(OBJS) src/servermain.o
	@echo 'Building target $@'
	@echo 'Linking objects'
	$(CC) -o "$@" $(OBJS) src/servermain.o
	@echo 'Target $@ built'
	@echo ' '

client: $(OBJS) src/clientmain.o
	@echo 'Building target $@'
	@echo 'Linking objects'
	$(CC) -o "$@" $(OBJS) src/clientmain.o
	@echo 'Target $@ built'
	@echo ' '

clean:
	rm -rf $(OBJS) src/clientmain.o src/servermain.o client server
