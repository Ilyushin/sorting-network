CXX=mpixlcxx_r
CFLAGS=-qarch=450d -qtune=450 -O5 -c
EXECUTABLE=sortingNetworkExec

objects=main.o heapSort.o dhSort.o permutation.o point.o quickSort.o sortingNetwork.o

all: $(EXECUTABLE)

sortingNetworkExec: $(objects)
	$(CXX) -o $(EXECUTABLE) $(objects)

main.o: 
	$(CXX) $(CFLAGS) main.cpp

heapSort.o:
	$(CXX) $(CFLAGS) -o heapSort.o heapSort.cpp

dhSort.o:
	$(CXX) $(CFLAGS) -o dhSort.o dhSort.cpp

permutation.o:
	$(CXX) $(CFLAGS) -o permutation.o permutation.cpp

point.o:
	$(CXX) $(CFLAGS) -o point.o point.cpp

quickSort.o:
	$(CXX) $(CFLAGS) -o quickSort.o quickSort.cpp

sortingNetwork.o:
	$(CXX) $(CFLAGS) -o sortingNetwork.o sortingNetwork.cpp

clean:
	rm $(objects) $(EXECUTABLE)
