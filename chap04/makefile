OBJECTS = ex4-3.o stack.o
TARGET = ex4-3.out
$(TARGET): $(OBJECTS)
	cc -o $(TARGET) $(OBJECTS)
ex4-3.o: stack.h

.PHONY: clean
clean:
	rm $(TARGET) $(OBJECTS)
