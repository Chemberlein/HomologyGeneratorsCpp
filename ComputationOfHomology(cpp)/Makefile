CC=g++
CFLAGS= -w
SOURCES=$(wildcard *.cpp)
DEPS=$(patsubst %.cpp, %.dep, $(SOURCES))
OBJ=$(patsubst %.cpp, %.o, $(SOURCES))

.PHONY:clean


main: $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@ 

clean:
	rm *.o *.dep main


-include $(DEPS)

%.dep: %.c
	g++ -MM $< >$@
