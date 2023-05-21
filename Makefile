main: vector.o
	g++ -o main main.cpp vector.o
vector: vector.cpp
	g++ -c vector.cpp
clean:
	rm *.o main