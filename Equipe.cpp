#include "Equipe.hpp"

//Constructeur
Equipe::Equipe(int team){
    if (team == 0){
        Penguin *marcus = new Penguin("Marcus", team);
        joueur1.push_back(marcus);
        Penguin *two = new Penguin("Two", team);
        joueur1.push_back(two);
        Penguin *three = new Penguin("Three", team);
        joueur1.push_back(three);

    } else {
        Penguin *francesco = new Penguin("Francesco", team);
        joueur2.push_back(francesco);
        Penguin *dos = new Penguin("Dos", team);
        joueur2.push_back(dos);
        Penguin *tres = new Penguin("Tres", team);
        joueur2.push_back(tres);
    }
    
}
	
//Destructeur
Equipe::~Equipe(){
    //rien à faire car pas d'allocation dynamique
    /*for (size_t i = 0; i < joueur1.size(); i++){
        delete joueur1[i];

    }

    for (size_t i = 0; i < joueur2.size(); i++){
        delete joueur2[i];
    }*/
}