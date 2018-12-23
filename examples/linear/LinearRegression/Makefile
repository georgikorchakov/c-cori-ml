CC = gcc
CFLAGS = -Wall --pedantic -std=c11

DEP = ../../../src/math/cori-math.c ../../../src/linear/LinearRegression/LinearRegression.c

OBJECTS = cori-math.o LinearRegression.o example_first_number.o example_random.o
OBJECTS_FN = cori-math.o LinearRegression.o example_first_number.o
OBJECTS_R = cori-math.o LinearRegression.o example_random.o

TARGET_FN = example_first_number
TARGET_R = example_random

all: main clean 

cori-math.o: ../../../src/math/cori-math.c
	$(CC) $(CFLAGS) -c ../../../src/math/cori-math.c

LinearRegression.o: ../../../src/linear/LinearRegression/LinearRegression.c
	$(CC) $(CFLAGS) -c ../../../src/linear/LinearRegression/LinearRegression.c

example_first_number.o: example_first_number.c
	$(CC) $(CFLAGS) -c example_first_number.c

example_random.o: example_random.c
	$(CC) $(CFLAGS) -c example_random.c

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET_R) $(OBJECTS_R)
	$(CC) $(CFLAGS) -o $(TARGET_FN) $(OBJECTS_FN)

clean:
	rm $(OBJECTS)

cleanall:
	rm $(OBJECTS) $(TARGET_R) $(TARGET_FN)
