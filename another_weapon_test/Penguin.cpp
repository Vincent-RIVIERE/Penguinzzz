#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include "Penguin.hpp"

Penguin::Penguin(std::string name, int team){

    this->texture.loadFromFile("penguin-frame.png");
    this->penguin.setTexture(texture);

    int scale = 1;
    this->penguin.setScale(scale, scale);

    for (int i=0; i<4; i++){
        this->sprite[2*i] = sf::IntRect((0+i+i*19), 0+team*40, 19, 19);
        this->sprite[2*i+1] = sf::IntRect((0+i+i*19), 20+team*40, 19, 19);
    }
    this->currentSprite=0;
    this->apply(currentSprite);

    float x = this->penguin.getPosition().x*scale;
    float y = this->penguin.getPosition().y*scale;
    float w = this->penguin.getTextureRect().width*scale;
    float h = this->penguin.getTextureRect().height*scale;

    this->name=name;

    this->speed=1.f*this->penguin.getScale().x;

    this->bounds.setPrimitiveType(sf::Points);
    this->bounds.resize(5);
    this->bounds[0].position = sf::Vector2f(x+0.25*w, y);
    this->bounds[1].position = sf::Vector2f(x+0.75*w, y);
    this->bounds[2].position = sf::Vector2f(x+0.75*w, y+h/3);
    this->bounds[3].position = sf::Vector2f(x+0.5*w, y+h);
    this->bounds[4].position = sf::Vector2f(x+0.25*w, y+h/3);

    this->activeArea.setSize(sf::Vector2f(w, h)); //dessine le rectangle magenta autour du penguin
    this->activeArea.setPosition(x,y);
    this->activeArea.setFillColor(sf::Color::Magenta); 

}

void Penguin::apply(int sprite){
    this->penguin.setTextureRect(this->sprite[sprite]);
    this->currentSprite=sprite;
}

int Penguin::animation(int frame, sf::Keyboard::Key lastKey){
    if(!sf::Keyboard::isKeyPressed(lastKey)){
        if(frame>=20){
            switch(this->currentSprite){
                case 0:
                    this->apply(2);
                    break;
                case 1:
                    this->apply(3);
                    break;
                case 2:
                    this->apply(0);
                    break;
                case 3:
                    this->apply(1);
                    break;
            }
            return 0;
        } else if(frame>=4 && this->currentSprite>3){
            switch(this->currentSprite){
                case 4:
                    this->apply(0);
                    break;
                case 5:
                    this->apply(1);
                    break;
                case 6:
                    this->apply(4);
                    break;
                case 7:
                    this->apply(5);
                    break;
            }
            return 0;
        } else {
            return ++frame;
        }
    } else {
        if(this->currentSprite<4){
            frame=0;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            this->apply(5);
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            this->apply(4);
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(frame==0){
                this->apply(5);
            } else if(frame>=4){
                this->apply(7);
            }
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(frame==0){
                this->apply(4);
            } else if(frame>=4){
                this->apply(6);
            }
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            if(this->currentSprite==0 || this->currentSprite==2){
                this->apply(0);
            } else if(this->currentSprite==1 || this->currentSprite==3){
                this->apply(1);
            }
        }
        return ++frame;
    }
}

void Penguin::setPosition(float x, float y){
    this->penguin.setPosition(x,y);
    this->activeArea.setPosition(x,y);
    for(int i=0; i<5; i++){
        this->bounds[i].position += sf::Vector2f(x,y);
    }
}

void Penguin::move(float x_speed, float y_speed){
    this->penguin.move(x_speed, y_speed);
    this->activeArea.move(x_speed, y_speed);
    for(int i=0; i<5; i++){
        this->bounds[i].position += sf::Vector2f(x_speed, y_speed);
    }
}

sf::Sprite Penguin::getPenguin(){
    return this->penguin;
}

sf::VertexArray Penguin::getBounds(){
    return this->bounds;
}

sf::RectangleShape Penguin::getArea(){
    return this->activeArea;
}

float Penguin::getSpeed(){
    return this->speed;
}





/*int main() {
    std::ifstream file("map1.txt");
    std::string data;
    file >> data;
    int map[1000][700];
    int i=700000-1;
    for(int y=0; y<700; y++){
        for(int x=0; x<1000; x++){
            if(data[i]=='1'){
                map[x][y]=1;
            } else {
                map[x][y]=0;
            }
            i--;
        }
    }
    sf::VertexArray sol;
    sol.setPrimitiveType(sf::Points);

    Penguin marcus("Marcus", 0);

    sf::Clock clock;
    
    sf::RenderWindow window(sf::VideoMode(1000, 700), "test");
    sf::RectangleShape zone(sf::Vector2f(900, 600));
    zone.setPosition(50, 50);
    zone.setFillColor(sf::Color::Transparent);
    zone.setOutlineThickness(5);
    zone.setOutlineColor(sf::Color::White);

    sf::RectangleShape fat(sf::Vector2f(2000, 400));
    fat.setPosition(500, 350);
    fat.setFillColor(sf::Color::Green);

    marcus.setPosition(650, 0);
    
    bool jump = false;
    int frame = 0;
    int height = 0;
    sf::Keyboard::Key lastKey;

    while (window.isOpen()) {

        sol.resize(0);
        for(int y=0; y<700; y++){
            for(int x=0; x<1000; x++){
                if(map[x][y]==1){
                    sf::Vertex pix(sf::Vector2f(x,y),sf::Color::Green);
                    sol.append(pix);
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if(map[(int)marcus.getBounds()[4].position.x-1][(int)marcus.getBounds()[4].position.y]==0) {
                marcus.move(-marcus.getSpeed(), 0.f);
                if(map[(int)marcus.getBounds()[3].position.x-1][(int)marcus.getBounds()[3].position.y]==1){
                    marcus.move(0.f, -marcus.getSpeed());
                }
            }
            lastKey=sf::Keyboard::Left;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if(map[(int)marcus.getBounds()[2].position.x+1][(int)marcus.getBounds()[2].position.y]==0) {
                marcus.move(marcus.getSpeed(), 0.f);
                if(map[(int)marcus.getBounds()[3].position.x+1][(int)marcus.getBounds()[3].position.y]==1){
                    marcus.move(0.f, -marcus.getSpeed());
                }
            }
            lastKey=sf::Keyboard::Right;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if(jump==false && map[(int)marcus.getBounds()[3].position.x][(int)marcus.getBounds()[3].position.y+1]==1){
                jump=true;
            }
            lastKey=sf::Keyboard::Space;
        }

        if(jump==false){
            if(map[(int)marcus.getBounds()[3].position.x][(int)marcus.getBounds()[3].position.y]==0) {
                marcus.move(0.f, marcus.getSpeed());
                height=0;
            }
        } else {
            if(height<20 && map[(int)marcus.getBounds()[0].position.x][(int)marcus.getBounds()[0].position.y-1]==0 && map[(int)marcus.getBounds()[1].position.x][(int)marcus.getBounds()[1].position.y-1]==0){
                marcus.move(0.f, -marcus.getSpeed());
                height++;
            } else {
                jump=false;
            }
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        while(clock.getElapsedTime().asMilliseconds()<16);

        frame = marcus.animation(frame, lastKey);
        window.clear();
        window.draw(zone);
        window.draw(sol);
        window.draw(marcus.getArea());
        window.draw(marcus.getPenguin());
        window.display();
        clock.restart();
        
    }
    return 0;
}
*/