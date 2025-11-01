exec = copper.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g

$(exec): $(objects)
    gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -0 $@

clean: 
	-rm *.out
	-rm *.objects
	-rm src/*.o
