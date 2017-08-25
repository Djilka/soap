PWD = $(shell pwd)

CC = gcc

SOURCE = 	calc.c \
		 	oil.c \
		 	optim.c

INC = -I$(PWD)
LIB = #-lm
FLAGS = -std=c11

OPT = $(FLAGS) $(INC) $(LIB)

TARGET = calc
#obj-m := 

calc:
	$(CC) -o $(TARGET) $(SOURCE) $(OPT)

clean:
	rm -rf *.o $(TARGET)