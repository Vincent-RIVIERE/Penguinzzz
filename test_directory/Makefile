EXEC = test_vincent

all: $(EXEC)

test_vincent: test_vincent.hpp test_vincent.cpp
	g++ -c test_vincent.cpp
	g++ test_vincent.o -o $(EXEC) -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f *.o

vclean:
	rm -f $(EXEC)