#ifndef WEAPONS_HPP
#define WEAPONS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Weapon{

public:

	
	//Methodes
	virtual void do_damage(float speed) =0;


};

#endif //WEAPONS_HPP
