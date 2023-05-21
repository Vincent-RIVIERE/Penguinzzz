EXEC = game
FILES = SFML_Screen.o Penguin.o Map.o Equipe.o

all: $(EXEC)

$(EXEC): $(FILES)
	g++ $(FILES) -o $(EXEC) -lsfml-graphics -lsfml-window -lsfml-system

SFML_Screen.o: SFML_Screen.cpp 
	g++ -c SFML_Screen.cpp

Penguin.o: Penguin.cpp 
	g++ -c Penguin.cpp 

Map.o: Map.cpp
	g++ -c Map.cpp

Equipe.o: Equipe.cpp
	g++ -c Equipe.cpp


clean:
	rm -f *.o
	rm -f $(EXEC)