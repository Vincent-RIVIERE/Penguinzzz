#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Gun.hpp"
#include "Bullet.hpp"
#include "Penguin.hpp"
#include <list>
#include <vector>

int main(int argc, char **argv)
{

  sf::RenderWindow window(sf::VideoMode(1280.f, 720.f), "Gun Test", sf::Style::Titlebar | sf::Style::Close);

  // Definir les objets
  Gun gun;
  std::list<Bullet *> bullets;

  Penguin *marcus = new Penguin("Marcus", 0);
  std::vector<Penguin *> penguins;
  penguins.push_back(marcus);
  marcus -> setPosition(500.f, 50.f);
  int penguin_timer = 0;

  bool isFiring = false;

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event)){
      switch (event.type){
      case sf::Event::Closed:
        window.close();
      }
    
    }
    float move_speed = 0.5f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
      gun.move(sf::Vector2f(0, -move_speed));
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        isFiring = true;
      }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
      gun.move(sf::Vector2f(0, move_speed));
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        isFiring = true;
      }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
      gun.move(sf::Vector2f(-move_speed, 0));
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        isFiring = true;
      }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
      gun.move(sf::Vector2f(move_speed, 0));
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        isFiring = true;
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
      isFiring = true;
    }
    if (isFiring == true){
      Bullet *newBullet = new Bullet;
      newBullet->setPosition(sf::Vector2f(gun.getWidth() / 2 + gun.getPosition().x + 47 , gun.getHeight() / 2 - 15 + gun.getPosition().y));
      bullets.push_back(newBullet);
      isFiring = false;
    }

    for (auto &bullet : bullets){
      bullet->do_damage(3);

      if (bullet->getX() > window.getSize().x){
        delete bullet;
        //bullet = nullptr;
      }
    }
    std::remove_if(bullets.begin(), bullets.end(), [](Bullet *bullet)
                   { return bullet == nullptr; });
    
    if (penguin_timer < 20){

      penguin_timer ++;
    }

    if (penguin_timer >= 20){
      marcus -> setPosition((rand() % int(window.getSize().x)), 0.f);
      penguins.push_back(marcus);
      penguin_timer = 0;
    }

    for (size_t it = 0; it < penguins.size(); it++){
      //penguins[it] -> move(0.f, 5.f);
      if (penguins[it] -> getPenguin().getPosition().y > window.getSize().y){
        penguins.erase(penguins.begin() + it);
      }
    }

    //Collision
for (auto bullet = bullets.begin(); bullet != bullets.end();) {
    bool bulletDeleted = false;

    for (size_t k = 0; k < penguins.size(); k++) {
        if ((*bullet)->getBullet().getGlobalBounds().intersects(penguins[k] -> getPenguin().getGlobalBounds())) {
            delete *bullet;
            bullet = bullets.erase(bullet);
            bulletDeleted = true;
            penguins.erase(penguins.begin() + k);
            break;
        }
    }

    if (!bulletDeleted) {
        ++bullet;
    }
}


    window.clear();
    window.draw(gun);
    window.draw(marcus -> getPenguin());

    for (auto &bullet : bullets){
      bullet->draw(window);
    }

    window.display();
  }

  return 0;
}
