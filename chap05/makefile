OBJ = ex5-12.o settab.o
TAR = ex5-12.out

$(TAR): $(OBJ)
	cc -o $(TAR) $(OBJ)
settab.o: settab.h

.PHONY: clean
clean:
	rm *.o *.out
