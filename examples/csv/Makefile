CC = gcc
CFLAGS = -Wall --pedantic -std=c11
SOURCE = example.c
DEP = ../../src/math/cori-math.c ../../src/csv/csv_reader.c
TARGET = example
OBJECTS = cori-math.o csv_reader.o example.o

all: main clean 

cori-math.o: ../../src/math/cori-math.c
	$(CC) $(CFLAGS) -c ../../src/math/cori-math.c

csv_reader.o: ../../src/csv/csv_reader.c
	$(CC) $(CFLAGS) -c ../../src/csv/csv_reader.c

example.o: example.c
	$(CC) $(CFLAGS) -c example.c

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

clean:
	rm $(OBJECTS)

cleanall:
	rm $(OBJECTS) $(TARGET)
