CC = gcc
CFLAGS = -Wall -g -Wextra

TARGET = Q7_A_LL

SRCS = Q7_A_LL.c

OBJS = $(SRCS:.c=.o)

all:$(TARGET)
$(TARGET) : $(OBJS)
	$(CC) -o $@ $^

clean :
	rm $(OBJS) $(TARGET)
