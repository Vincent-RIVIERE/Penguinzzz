#include "Gun.hpp"
#include <cstdlib>
#include <iostream>


//Constructeur
Gun::Gun(){
    g_texture.loadFromFile("gun.png");
    gun.setTexture(g_texture);
    this -> scale = 0.25f;
    gun.setScale(scale,scale);
    
}
	
//Destructeur
Gun::~Gun(){
    //rien à faire car pas d'allocation dynamique
}

	
//Methodes
// void Gun::move(sf::Vector2f dir){
// 	gun.move(dir);
// }

// int Gun::getX(){
// 	return gun.getPosition().x;
// }

// int Gun::getY(){
// 	return gun.getPosition().y;
// }

float Gun::getWidth(){
    return gun.getTextureRect().width*scale;
}

float Gun::getHeight(){
    return gun.getTextureRect().height*scale;
}


void Gun::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(gun, states);
}


