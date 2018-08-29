
.PHONY: all clean

CC=gcc
RM=rm -fr
AR=ar
LDFLAGS=-I./common -I./ap_master
VPATH=ap_master:ap_slave:common

OBJS_M=ap_master.o sap_info.o rcv.o send.o cloud.o epoll.o\
		list.o log.o pipe.o sig.o socket.o timer.o config.o io.o
#OBJS_M=ap_master.c sap_info.c rcv.c send.c cloud.c epoll.c\
		list.c log.c pipe.c sig.c socket.c timer.c config.c io.c
OBJS_S=ap_slave.o epoll.o pipe.o timer.o 
all:apMaster 
	$(shell pwd)

apMaster:$(OBJS_M)
	$(CC) -o $@ $(OBJS_M)
	
apSlave:$(OBJS_S)
	$(CC) -o $@ $< -I.



clean:
	$(RM) *.o apMaster apSlave 
		
%.o: %.c
	$(CC) -c -g $< $(LDFLAGS)

