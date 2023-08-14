CC = g++ -pthread -g3 -g -std=c++11 

osAsk1: main.o func.o 

	$(CC) -o osAsk1 main.o func.o -lm

main.o: main.cpp func.cpp 

	$(CC) -c main.cpp func.cpp 

func.o: func.cpp

	$(CC) -c func.cpp

run:

	./osAsk1 Stairway.txt 5 10

valgrind:

	valgrind --leak-check=yes ./osAsk1 small_sample.txt 5 10

clean: 

	rm -f *.o
