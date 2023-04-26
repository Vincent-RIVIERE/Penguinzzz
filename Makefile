EXEC = test

all: $(EXEC)

test: SFML_Screen.cpp
	g++ -c SFML_Screen.cpp
	g++ SFML_Screen.o -o $(EXEC) -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f *.o

vclean:
	rm -f $(EXEC)