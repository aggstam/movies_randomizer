GENRE = all

all:
	$(info Executing C code...)
	gcc -o movies_randomizer movies_randomizer.c
	./movies_randomizer $(GENRE)

script:
	$(info Executing bash script...)
	chmod a+x movies_randomizer.sh
	./movies_randomizer.sh $(GENRE)

clean:
	rm -f movies_randomizer

.PHONY: all script clean
