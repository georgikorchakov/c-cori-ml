CC = gcc
SOURCE = example.c
DEP = ../../../src/math/cori-math.c ../../../src/linear/LinearRegression/LinearRegression.c
TARGET = example_first_number example_random
CFLAGS = -Wall --pedantic -std=c11
OBJECTS = cori-math.o LinearRegression.o example_first_number.o example_random.o
OBJECTS_FN = cori-math.o LinearRegression.o example_first_number.o
OBJECTS_R = cori-math.o LinearRegression.o example_random.o

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
	$(CC) $(CFLAGS) -o example_random $(OBJECTS_R)
	$(CC) $(CFLAGS) -o example_first_number $(OBJECTS_FN)

clean:
	rm $(OBJECTS)

cleanall:
	rm $(OBJECTS) $(TARGET)