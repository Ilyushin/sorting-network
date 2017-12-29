CXX=mpixlcxx_r
CFLAGS=-qarch=450d -qtune=450 -O5 -c
EXECUTABLE=sortingNetworkExec

objects=main.o point.o quickSort.o dhSort.o

all: $(EXECUTABLE)

sortingNetworkExec: $(objects)
	$(CXX) -o $(EXECUTABLE) $(objects)

main.o: 
	$(CXX) $(CFLAGS) main.cpp

point.o:
	$(CXX) $(CFLAGS) -o point.o point.cpp

quickSort.o:
	$(CXX) $(CFLAGS) -o quickSort.o quickSort.cpp

dhSort.o:
        $(CXX) $(CFLAGS) -o dhSort.o dhSort.cpp

clean:
	rm $(objects) $(EXECUTABLE)
