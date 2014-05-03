OBJECTS = ex4-4.o stack.o stack_api.o
TARGET = ex4-4.out
$(TARGET): $(OBJECTS)
	cc -o $(TARGET) $(OBJECTS)
ex4-3.o: stack.h stack_api.h
stack_api.o: stack.h

.PHONY: clean
clean:
	rm $(TARGET) $(OBJECTS)
