#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#ifndef BULLET_HPP
#define BULLET_HPP

class Bullet{

public:
	//Constructeur
	Bullet();
	
	//Destructeur
	~Bullet();
	
	//Methodes
    void do_damage(float speed);
    float getX();
	float getY();
	float getWidth();
	float getHeight();
	void draw(sf::RenderWindow &window);
	void setPosition(sf::Vector2f newPos);
	sf::Sprite getBullet(){
		return b_sprite;
	}



private:
	
	//Attributs
    sf::Texture b_texture;
    sf::Sprite b_sprite;
	float scale;

};

#endif //BULLET_HPP
