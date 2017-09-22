objects = program.o
fileWrite: $(objects)
	gcc -o fileWrite $(objects)
$(objects): program.c program.h
	gcc -c program.c
.PHONY: clean run
clean:
	rm fileWrite $(objects) 
run:
	./fileWrite
usage:
	@echo make
	@echo make run
