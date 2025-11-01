exec = copper.exe
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

INSTALL_DIR = C:\tools

install:
	make
	copy .\copper.exe $(INSTALL_DIR)

clean: 
	-del $(exec)
	-del *.o
	-del src\*.o
