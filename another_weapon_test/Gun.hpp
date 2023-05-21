#ifndef GUN_HPP
#define GUN_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
//#include "Weapon.hpp"
#include "Bullet.hpp"
#include <vector>

class Gun : public sf::Drawable, public sf::Transformable
{ //: public Weapon{

public:
	//Constructeur
	Gun();
	
	//Destructeur
	~Gun();
	
	//Methodes
	// void move(sf::Vector2f dir);
	// int getX();
	// int getY();
	float getWidth();
	float getHeight();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;



	
private:
	
	//Attributs
	//float bullet_speed;
	//float fire_rate;
	sf::Texture g_texture;
	sf::Sprite gun;
	float scale;
	//std::vector<Bullet*> bullets;
	//sf::Clock fire_clock;


};

#endif //GUN_HPP
