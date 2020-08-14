CC = gcc
CFLAGS = -Wall -g
LIBS = -lpthread

ODIR = src/obj

_OBJ = list.o graph.o interval.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

grail: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test: src/obj/list_test.o src/obj/graph_test.o
	$(CC) -o $^ $(OBJ) $(CFLAGS) $(LIBS)

src/obj/list.o: src/list/list.c src/list/list.h src/list/list_p.h
	$(CC) -c -o $@ $< $(CFLAGS)

src/obj/graph.o: src/graph/graph.c src/graph/graph.h src/obj/list.o src/obj/interval.o
	$(CC) -c -o $@ $< $(CFLAGS)

src/obj/interval.o: src/interval/interval.c src/interval/interval.h
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o

.PHONY: clean
