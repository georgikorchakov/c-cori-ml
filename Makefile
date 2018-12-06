CC = gcc
SOURCE = example.c
DEP = src/math/cori-math.c src/linear/LinearRegression/LinearRegression.c
TARGET = example
CFLAGS = -Wall --pedantic -std=c11
OBJECTS = cori-math.o LinearRegression.o example.o

all: main clean 

cori-math.o: src/math/cori-math.c
	$(CC) $(CFLAGS) -c src/math/cori-math.c

LinearRegression.o: src/linear/LinearRegression/LinearRegression.c
	$(CC) $(CFLAGS) -c src/linear/LinearRegression/LinearRegression.c

example.o: example.c
	$(CC) $(CFLAGS) -c example.c


main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

clean:
	rm $(OBJECTS)

cleanall:
	rm $(OBJECTS) $(TARGET)