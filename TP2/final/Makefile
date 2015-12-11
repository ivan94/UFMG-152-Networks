CC=gcc
CFLAGS=-c -Wall -g
OBJS=socket.o server.o client.o
%.o: %.c
	@echo 'Building $<'
	$(CC) $(CFLAGS) "$<" -o "$@"
	@echo '$< built.'
	@echo ' '

all: servidor cliente

servidor: $(OBJS) servermain.o
	@echo 'Building target $@'
	@echo 'Linking objects'
	$(CC) -o "$@" $(OBJS) servermain.o
	@echo 'Target $@ built'
	@echo ' '

cliente: $(OBJS) clientmain.o
	@echo 'Building target $@'
	@echo 'Linking objects'
	$(CC) -o "$@" $(OBJS) clientmain.o
	@echo 'Target $@ built'
	@echo ' '

clean:
	rm -rf $(OBJS) clientmain.o servermain.o cliente servidor
