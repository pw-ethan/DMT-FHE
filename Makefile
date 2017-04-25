CXX := g++
COMPILEFLAGS := -g -Wall #-I/
LIBS := #-l
LINKFLAGS := -L/.

server : main.o libsocket.o
	$(CXX) -o $@ $^ $(LINKFLAGS) $(LIBS)

client : main.o libsocket.o
	$(CXX) -o $@ $^ $(LINKFLAGS) $(LIBS)

%.o : %.cpp
	$(CXX) -c -o $@ $< $(COMPILEFLAGS)

clean :
	rm -rf *.o server client

.PHONY : all clean server client


