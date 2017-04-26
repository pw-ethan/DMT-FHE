CC := g++
COMPILEFLAGS := -g -Wall -DDEBUG #-I/
LIBS := #-l
LINKFLAGS := -L/.

out : server.o libsocket.o VTree.o
	$(CXX) -o $@ $^ $(LINKFLAGS) $(LIBS)

%.o : %.cpp
	$(CXX) -c -o $@ $< -std=c++11 $(COMPILEFLAGS)

clean :
	rm -rf *.o server client

.PHONY : out clean


