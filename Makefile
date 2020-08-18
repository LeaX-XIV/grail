CC = gcc
CFLAGS = -Wall -g
LIBS = -lpthread

ODIR = src/obj

_OBJ = list.o graph.o interval.o utils.o query.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

grail: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test: $(OBJ)
	$(CC) src/list/list_test.c $^ -o bin/list_test $(CFLAGS) $(LIBS)
	$(CC) src/graph/graph_test.c $^ -o bin/graph_test $(CFLAGS) $(LIBS)


src/obj/list.o: src/list/list.c src/list/list.h src/list/list_p.h
	$(CC) -c -o $@ $< $(CFLAGS)

src/obj/graph.o: src/graph/graph.c src/graph/graph.h src/obj/list.o src/obj/interval.o
	$(CC) -c -o $@ $< $(CFLAGS)

src/obj/interval.o: src/interval/interval.c src/interval/interval.h
	$(CC) -c -o $@ $< $(CFLAGS)

src/obj/utils.o: src/utils/utils.c src/utils/utils.h
	$(CC) -c -o $@ $< $(CFLAGS)

src/obj/query.o: src/query/query.c src/query/query.h src/obj/list.o src/obj/graph.o src/obj/interval.o
	$(CC) -c -o $@ $< $(CFLAGS)

src/obj/main.o: src/main.c src/obj/list.o src/obj/graph.o src/query/query.o
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o
	rm -f bin/*

.PHONY: clean
.PHONY: test
