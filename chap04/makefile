OBJECTS = ex4-6.o stack.o cal.o
TARGET = ex4-6.out
$(TARGET): $(OBJECTS)
	cc -o $(TARGET) $(OBJECTS) -lm
ex4-6.o: cal.h
cal.o: stack.h
stack_api.o: stack.h

.PHONY: clean
clean:
	rm $(TARGET) $(OBJECTS)
