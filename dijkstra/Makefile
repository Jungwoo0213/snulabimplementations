all: dijkstra.o fibHeap.o main.o
	g++ -o main main.o dijkstra.o fibHeap.o
dijkstra.o:
	g++ -c dijkstra.cpp
fibHeap.o:
	g++ -c fibHeap.cpp
main.o:
	g++ -c main.cpp
clean:
	rm dijkstra.o
	rm fibHeap.o
	rm main.o