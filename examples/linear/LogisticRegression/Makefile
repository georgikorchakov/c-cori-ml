CC = gcc
CFLAGS = -Wall --pedantic -std=c11
TARGET_EXAMPLE = example
TARGET_IRIS = example_iris
OBJECTS = cori-math.o csv_reader.o LogisticRegression.o example.o example_iris.o
OBJECTS_EXAMPLE = cori-math.o LogisticRegression.o example.o
OBJECTS_IRIS = cori-math.o csv_reader.o LogisticRegression.o example_iris.o

all: main clean 

cori-math.o: ../../../src/math/cori-math.c
	$(CC) $(CFLAGS) -c ../../../src/math/cori-math.c

csv_reader.o: ../../../src/csv/csv_reader.c
	$(CC) $(CFLAGS) -c ../../../src/csv/csv_reader.c

LogisticRegression.o: ../../../src/linear/LogisticRegression/LogisticRegression.c
	$(CC) $(CFLAGS) -c ../../../src/linear/LogisticRegression/LogisticRegression.c

example.o: example.c
	$(CC) $(CFLAGS) -c example.c

example_iris.o: example_iris.c
	$(CC) $(CFLAGS) -c example_iris.c

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET_EXAMPLE) $(OBJECTS_EXAMPLE)
	$(CC) $(CFLAGS) -o $(TARGET_IRIS) $(OBJECTS_IRIS)

clean:
	rm $(OBJECTS)

cleanall:
	rm $(OBJECTS) $(TARGET_EXAMPLE) $(TARGET_IRIS)
