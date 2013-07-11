all: reader writer

reader: reader.c
	gcc -g -Wall -o $@ $<

writer: writer.c
	gcc -g -Wall -o $@ $<

.PHONY: clean

clean:
	rm reader writer
