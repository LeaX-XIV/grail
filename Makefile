CC = gcc
# CFLAGS = -Wall -g -Og
CFLAGS = -O3
LIBS = -lpthread
MKDCMD = mkdir -p

ODIR = src/obj

_OBJ = list.o graph.o interval.o utils.o query.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

BDIR = bin

grail: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# Target broken
test: $(OBJ)
	$(MKDCMD) $(BDIR)
	$(CC) src/list/list_test.c $^ -o $(BDIR)/list_test $(CFLAGS) $(LIBS)
	$(CC) src/graph/graph_test.c $^ -o $(BDIR)/graph_test $(CFLAGS) $(LIBS)

src/obj/list.o: src/list/list.c src/list/list.h src/list/list_p.h $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

src/obj/graph.o: src/graph/graph.c src/graph/graph.h src/graph/graph_p.h src/obj/list.o src/obj/interval.o src/obj/utils.o $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

src/obj/interval.o: src/interval/interval.c src/interval/interval.h $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

src/obj/utils.o: src/utils/utils.c src/utils/utils.h $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

src/obj/query.o: src/query/query.c src/query/query.h src/obj/graph.o $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

src/obj/main.o: src/main.c src/obj/list.o src/obj/graph.o src/obj/query.o $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

 $(ODIR):
	$(MKDCMD) $(ODIR)  

clean:
	rm -rf $(ODIR)/*.o
	rm -rf $(BDIR)/*
	rm -f grail

.PHONY: clean
.PHONY: test
