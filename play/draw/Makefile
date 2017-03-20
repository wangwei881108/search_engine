#Linker flags
LDFLAGS = -std=c++11
# Compiler flags
CFLAGS = -std=c++11 -Wall

PROG = flowout

OBJS = produce_bag.cpp bag.o treedecomposition.o indices.o

all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

clean:
	-rm -f *.o

