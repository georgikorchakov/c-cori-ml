CC = gcc
CFLAGS = -Wall --pedantic -std=c11
SOURCE = example.c
DEP = ../../../src/math/cori-math.c ../../../src/linear/LogisticRegression/LogisticRegression.c
TARGET = example
OBJECTS = cori-math.o LogisticRegression.o example.o

all: main clean 

cori-math.o: ../../../src/math/cori-math.c
	$(CC) $(CFLAGS) -c ../../../src/math/cori-math.c

LogisticRegression.o: ../../../src/linear/LogisticRegression/LogisticRegression.c
	$(CC) $(CFLAGS) -c ../../../src/linear/LogisticRegression/LogisticRegression.c

example.o: example.c
	$(CC) $(CFLAGS) -c example.c

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

clean:
	rm $(OBJECTS)

cleanall:
	rm $(OBJECTS) $(TARGET)
