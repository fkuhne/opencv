default: all

CPP = g++

CFLAGS = -Wall $(shell pkg-config --cflags opencv)
LDFLAGS = $(shell pkg-config --libs --static opencv)

SRCS = Drawing_1.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = drawing1

all: $(SRCS) $(EXEC)

%.o: %.cpp
	$(CPP) $(CFLAGS) -c -o $@ $<

$(EXEC): $(OBJS)
	$(CPP) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)
