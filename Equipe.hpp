#include "Penguin.hpp"

#ifndef EQUIPE_HPP
#define EQUIPE_HPP

class Equipe{

public:
	//Constructeur
	Equipe(int team);
	
	//Destructeur
	~Equipe();
	
	//Methodes
    std::vector<Penguin*> getJoueur1() const{
        return joueur1;
    }
    std::vector<Penguin*> getJoueur2() const{
        return joueur2;
    }




private:
	
	//Attributs
    std::vector<Penguin *> joueur1;
    std::vector<Penguin *> joueur2;

};

#endif //EQUIPE_HPP
