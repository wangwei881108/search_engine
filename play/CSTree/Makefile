#Linker flags
LDFLAGS = -std=c++11
# Compiler flags
CFLAGS = -std=c++11 -Wall

PROG = main

OBJS = main.cpp TBCSTree.o

all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

clean:
	-rm -f *.o

