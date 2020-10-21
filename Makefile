CC = gcc
CFLAGS = -g -Wall
FILES = src/lincalc.o src/loadvar.c src/displayvar.c
HEADERFILES = src/defn.h

lincalc: $(FILES)
	$(CC) $(CFLAGS) -o lincalc $(FILES)

$(FILES): $(HEADERFILES)

clean:
	rm -f $(FILES) lincalc
