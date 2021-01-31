CC = gcc
LD = ld
LDFLAGS = -static
CFLAGS = -fno-pie -fno-asynchronous-unwind-tables -Os -Wall -Wno-main
STRIP = strip -g --remove-section=.comment --remove-section=.note.GNU-stack

FILES = swap.o relo3.o mismatch str main lazy

all: $(FILES) merge-1.map merge-2.map

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^
	$(STRIP) $@

%.s: %.c
	$(CC) $(CFLAGS) -S -o $@ $^

foo.o: CFLAGS+=-fno-common
bar.o: CFLAGS+=-fno-common

merge-1.map: foo.o bar.o
	$(LD) -M=$@ -r -o merge-1.o $^

merge-2.map: bar.o foo.o 
	$(LD) -M=$@ -r -o merge-2.o $^

mismatch: mismatch-a.o mismatch-b.o
	$(CC) $(LDFLAGS) -o $@ $^

main: even.o odd.o start.o 
	$(LD) $(LDFLAGS) -M=$@.map -o $@ $^

str: str-a.o str-b.o
	$(CC) $(LDFLAGS) -o $@ $^

lazy: lazy.c
	gcc -Os -Wall -ggdb -o $@ $^

clean:
	rm -f *.o *.s *.map *~
	rm -f $(FILES)

# vim: ts=8 sw=8 noet
