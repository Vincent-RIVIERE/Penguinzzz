#include "SFML/Graphics.hpp"
#include "Bullet.hpp"

//Constructeur
Bullet::Bullet(){
    b_texture.loadFromFile("bullet.png");
    b_sprite.setTexture(b_texture);
    this -> scale = 0.1f;
    b_sprite.setScale(scale,scale);
    
}
	
//Destructeur
Bullet::~Bullet(){
    //rien à faire car pas d'allocation dynamique
}
	
//Methodes
void Bullet::do_damage(float speed){
    b_sprite.move(speed,0);

}

//recuperer l
float Bullet::getX(){
    return b_sprite.getPosition().x*scale;
}

float Bullet::getY(){
    return b_sprite.getPosition().y*scale;
}

float Bullet::getWidth(){
    return b_sprite.getTextureRect().width*scale;
}

float Bullet::getHeight(){
    return b_sprite.getTextureRect().height*scale;
}

void Bullet::draw(sf::RenderWindow &window){
    window.draw(b_sprite);
}

void Bullet::setPosition(sf::Vector2f newPos){
    b_sprite.setPosition(newPos);
}



