OBJECTS = ex4-11.o
TARGET = ex4-11.out
$(TARGET): $(OBJECTS)
	cc -o $(TARGET) $(OBJECTS) -lm
ex4-6.o: cal.h
cal.o: stack.h
stack_api.o: stack.h

.PHONY: clean
clean:
	rm $(TARGET) $(OBJECTS)
