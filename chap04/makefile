OBJECTS = ex4-5.o stack.o
TARGET = ex4-5.out
$(TARGET): $(OBJECTS)
	cc -o $(TARGET) $(OBJECTS) -lm
ex4-3.o: stack.h stack_api.h
stack_api.o: stack.h

.PHONY: clean
clean:
	rm $(TARGET) $(OBJECTS)
