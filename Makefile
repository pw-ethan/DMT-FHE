CC := g++
COMPILEFLAGS := -g -Wall -DDEBUG
LIBS := -ljson -pthread
LINKFLAGS := -L /usr/local/lib

server : server.o libsocket.o VTree.o PTree.o
	$(CXX) -o $@ $^ $(LINKFLAGS) $(LIBS)

client : main.o libsocket.o
	$(CXX) -o $@ $^ $(LINKFLAGS) $(LIBS)

%.o : %.cpp
	$(CXX) -c -o $@ $< -std=c++11 $(COMPILEFLAGS)

clean :
	rm -rf *.o server

.PHONY : server clean client


