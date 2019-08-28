all: fibHeap.o main.o
	g++ -o main main.o fibHeap.o
fibHeap.o:
	g++ -c fibHeap.cpp
main.o:
	g++ -c main.cpp
clean:
	rm fibHeap.o
	rm main.o
	rm main.exe