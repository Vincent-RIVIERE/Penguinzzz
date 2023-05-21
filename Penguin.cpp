#include "Penguin.hpp"

Penguin::Penguin(std::string name, int team){

    // Chargement de l'image vec les textures des penguins
    this->texture.loadFromFile("penguin-frame.png");
    this->penguin.setTexture(texture);

    // Découpage des zonnes de l'image pour chaque texture
    for (int i=0; i<4; i++){
        this->sprite[2*i] = sf::IntRect((0+i+i*19), 0+team*40, 19, 19);
        this->sprite[2*i+1] = sf::IntRect((0+i+i*19), 20+team*40, 19, 19);
    }
    // Application de la texture de base
    this->currentSprite=0;
    this->apply(currentSprite);

    // Nom du penguin
    this->name=name;

    // Vitesse du penguin
    this->speed[0]=0.06;
    this->speed[1] = 0;

    // Etablissement de la zone de collision du penguin
    float x = this->penguin.getPosition().x;
    float y = this->penguin.getPosition().y;
    float w = this->penguin.getTextureRect().width;
    float h = this->penguin.getTextureRect().height;
    this->bounds.setPrimitiveType(sf::Points);
    this->bounds.resize(5);
    this->bounds[0].position = sf::Vector2f(x+0.25*w, y);
    this->bounds[1].position = sf::Vector2f(x+0.75*w, y);
    this->bounds[2].position = sf::Vector2f(x+0.75*w, y+h/3);
    this->bounds[3].position = sf::Vector2f(x+0.5*w, y+h);
    this->bounds[4].position = sf::Vector2f(x+0.25*w, y+h/3);
    // Zone de collision du penguin : 
    //       *-----*
    //       |     |
    //       *     *
    //        \   /
    //         \ /
    //          *


    this->focus = false;

}

void Penguin::apply(int sprite){
    this->penguin.setTextureRect(this->sprite[sprite]);
    this->currentSprite=sprite;
}

int Penguin::animation(int frame, sf::Keyboard::Key lastKey){
    if(!sf::Keyboard::isKeyPressed(lastKey)){
        // Animation du penguin en position statique
        if(frame>=20){
            // Changement de sprite etre position haute et basse
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
            // Changement de mode d'animation, passant de déplacement à statique
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
        // Animation du penguin en déplacement 
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
    for(int i=0; i<5; i++){
        this->bounds[i].position += sf::Vector2f(x,y);
    }
}

void Penguin::move(int x_dir, int y_dir, float dt){
    float x = x_dir*this->speed[0]*dt;
    float y = y_dir*(this->speed[0]+this->speed[1])*dt;
    this->penguin.move(x, y);
    for(int i=0; i<5; i++){
        this->bounds[i].position += sf::Vector2f(x, y);
    }
}

sf::Sprite Penguin::getPenguin(){
    return this->penguin;
}

sf::VertexArray Penguin::getBounds(){
    return this->bounds;
}

float Penguin::getSpeed(int n){
    return this->speed[n];
}

void Penguin::setYspeed(float n){
    this->speed[1]=n;
}

void Penguin::addYspeed(float n){
    this->speed[1]+=n;
}

sf::Keyboard::Key Penguin::getLastKey(){
    return this->lastKey;
}

void Penguin::setLastKey(sf::Keyboard::Key key){
    this->lastKey = key;
}

int Penguin::getFrame(){
    return this->frame;
}

void Penguin::setFrame(int n){
    this->frame = n;
}

bool Penguin::getFocus(){
    return this->focus;
}
void Penguin::setFocus(bool f){
    this->focus = f;
}