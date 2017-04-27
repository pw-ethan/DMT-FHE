CC := g++
COMPILEFLAGS := -g -Wall -DDEBUG #-I/
LIBS := #-l
LINKFLAGS := -L/.

server : server.o libsocket.o VTree.o PTree.o
	$(CXX) -o $@ $^ $(LINKFLAGS) $(LIBS)

%.o : %.cpp
	$(CXX) -c -o $@ $< -std=c++11 $(COMPILEFLAGS)

clean :
	rm -rf *.o server

.PHONY : server clean


