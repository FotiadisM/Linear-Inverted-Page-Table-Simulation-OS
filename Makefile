CC = gcc
CFLAGS = -g3 -Wall
LDFLAGS =

BDIR = bin
ODIR = build
IDIR = include
SDIR = src

EXECUTABLE = runner

_DEPS = Address.h InvertedPageTable.h Simulator.h replacmentAlgorithms.h Queue.h defines.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o Address.o InvertedPageTable.o Simulator.o replacmentAlgorithms.o Queue.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(BDIR)/$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean lru ws valgrind-lru valgrind-ws

lru:
	./$(BDIR)/$(EXECUTABLE) -a LRU -f 20 -q 5 -m 100

ws:
	./$(BDIR)/$(EXECUTABLE) -a WS -ws 10 -f 20 -q 5 -m 100

valgrind-lru:
	valgrind --leak-check=full ./$(BDIR)/$(EXECUTABLE) -a LRU -f 20 -q 5 -m 100

valgrind-ws:
	valgrind --leak-check=full ./$(BDIR)/$(EXECUTABLE) -a WS -ws 10 -f 20 -q 5 -m 100

clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/$(EXECUTABLE)