SRCS	= crc32.cc test_crc32.cc
OBJS	= $(SRCS:%.cc=%.o)
NRT		= test_crc32

CC		= g++
CCFLAGS	= -Wall -o0 -std=c++23
LDFLAGS	=
RM		= rm -f

all:	$(NRT)

$(NRT):	$(OBJS) Makefile
		$(CC) $(CCFLAGS) $(OBJS) -o $@ $(LDFLAGS)

.cc.o:
		$(CC) $(CCFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS) $(NRT)

ack:
		@echo $(SRCS)
		@echo $(OBJS)
		@echo $(NRT)

run:
		./$(NRT) 


crc32.o: crc32.h
test_crc32.o: binary_header.h crc32.h
