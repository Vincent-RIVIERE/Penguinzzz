#include <iostream>
#include <cmath>
#include "Equipe.hpp"

float detect_collision(sf::VertexArray penguin, int **map, int point, int x, int y){
    if(map[(int)penguin[point].position.x+x][(int)penguin[point].position.y+y]==0){
        return 0;
    } else {
        return 1;
    }
}

Penguin* changePenguin(Equipe equipe0, Equipe equipe1){
    for(int i = 0; i < equipe0.getJoueur1().size(); i++){
        if(equipe0.getJoueur1()[i]->getFocus()){
            return equipe0.getJoueur1()[i];
        }
    }
    for(int i = 0; i < equipe1.getJoueur2().size(); i++){
        if(equipe1.getJoueur2()[i]->getFocus()){
            return equipe1.getJoueur2()[i];
        }
    }
    return NULL;
}

int main() {
    // Génération de la fenêtre
    sf::RenderWindow window(sf::VideoMode(1000, 700), "test");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    // Pointeur pour le controle du penguin
    Penguin *onFocus;

    // Génération de la première équipe
    Equipe equipe0(0);
    equipe0.getJoueur1()[0]->setPosition(100, 368);
    equipe0.getJoueur1()[1]->setPosition(200, 470);
    equipe0.getJoueur1()[2]->setPosition(430, 520);
    
    // Génération de la deuxième équipe
    Equipe equipe1(1);
    equipe1.getJoueur2()[0]->setPosition(570, 520);
    equipe1.getJoueur2()[1]->setPosition(800, 470);
    equipe1.getJoueur2()[2]->setPosition(900, 368);
    
    // Génération de la matrice de la carte
    Map map(2);

    // Horologe pour le calcul des déplacement
    float prev_clock = 0;
    sf::Clock now_clock;

    // Attributs pour les conditions des états des penguins
    bool jump = false;
    int frame = 0;
    int height = 0;

    // Le penguin contrôlé est le premier de la première équipe
    equipe0.getJoueur1()[0]->setFocus(true);
    onFocus = equipe0.getJoueur1()[1];
    
    // Génération de la carte
    map.reset();

    // Timer pour un tour
    int turn_time = 3;
    sf::Clock timer;

    // Police pour le texte a afficher
    sf::Font font;
    //font.loadFromFile("planet beson 2.otf");
    font.loadFromFile("Animated.ttf");

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);

    // Pour test de la destruction de la carte
    sf::Vector2i mousePosition;
    sf::CircleShape ball;
    ball.setRadius(30);
    ball.setFillColor(sf::Color::Red);
    bool boom = false;

    while (window.isOpen()) {

        text.setCharacterSize(30);
        text.setOutlineThickness(5);
        if(turn_time-timer.getElapsedTime().asSeconds()>9){
            text.setString("0:"+std::to_string((int)(turn_time-timer.getElapsedTime().asSeconds())));
        } else {
            text.setString("0:0"+std::to_string((int)(turn_time-timer.getElapsedTime().asSeconds())));
        }
        text.setPosition(10, 10);

        // Selection du penguin à contrôler
        onFocus = changePenguin(equipe0, equipe1);

        sf::VertexArray penguin = onFocus->getBounds();
        int **mapArray = map.getMap();

        // Calcul des déplacements du penguin contrôlé
        int x_dir = 0; // Direction du penguin selon x
        int y_dir = 0; // Direction du penguin selon y
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(detect_collision(penguin, mapArray, 4, 1, 0)==0){
                x_dir = -1;
            }
            onFocus->setLastKey(sf::Keyboard::Left);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(detect_collision(penguin, mapArray, 2, -1, 0)==0){
                x_dir = 1;
            }
            onFocus->setLastKey(sf::Keyboard::Right);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            if(jump==false && detect_collision(penguin, mapArray, 3, 0, 1)==1){
                jump=true;
                onFocus->setYspeed(0.06);
            }
            onFocus->setLastKey(sf::Keyboard::Space);
        }
        // Gestion des pentes
        if(detect_collision(penguin, mapArray, 3, x_dir, 0)==1){
            y_dir = -1;
        }
        if(jump==false){
            // Application de la gravité sur tout les penguins
            if(detect_collision(penguin, mapArray, 3, 0, 1)==0) {
                y_dir = 1;
                onFocus->addYspeed(0.003);
                height = 0;
            } else {
                onFocus->setYspeed(0);
            }
        } else {
            if(height<20 && detect_collision(penguin, mapArray, 0, 0, -1)==0 && detect_collision(penguin, mapArray, 1, 0, -1)==0){
                y_dir = -1;
                onFocus->addYspeed(-0.003);
                height++;
            } else {
                jump=false;
                onFocus->setYspeed(0);
            }
        }

        // Déplacement des penguins
        float dt = now_clock.getElapsedTime().asMilliseconds()-prev_clock;
        // Application du déplacement lié à la gravité sur tout les penguins
        for(size_t i = 0; i < equipe0.getJoueur1().size(); i++){
            if(!equipe0.getJoueur1()[i]->getFocus()){
                if(detect_collision(equipe0.getJoueur1()[i]->getBounds(), mapArray, 3, 0, 1)==0) {
                    equipe0.getJoueur1()[i]->addYspeed(0.003);
                    equipe0.getJoueur1()[i]->move(0, 1, dt);
                } else {
                    equipe0.getJoueur1()[i]->setYspeed(0);
                }
            }
        }
        for(size_t i = 0; i < equipe1.getJoueur2().size(); i++){
            if(!equipe1.getJoueur2()[i]->getFocus()){
                if(detect_collision(equipe1.getJoueur2()[i]->getBounds(), mapArray, 3, 0, 1)==0) {
                    equipe1.getJoueur2()[i]->addYspeed(0.003);
                    equipe1.getJoueur2()[i]->move(0, 1, dt);
                } else {
                    equipe1.getJoueur2()[i]->setYspeed(0);
                }
            }
        }
        // Déplacement du penguins contrôlé
        onFocus->move(x_dir, y_dir, dt);

        // Gestion de la fermeture de la fenêtre
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        std::cout << dt <<std::endl;
        
        // Animation des penguins
        for(size_t i = 0; i < equipe0.getJoueur1().size(); i++){
            if(!equipe0.getJoueur1()[i]->getFocus()){
                equipe0.getJoueur1()[i]->setFrame(equipe0.getJoueur1()[i]->animation(equipe0.getJoueur1()[i]->getFrame(), sf::Keyboard::K));
            }
        }
        for(size_t i = 0; i < equipe1.getJoueur2().size(); i++){
            if(!equipe1.getJoueur2()[i]->getFocus()){
                equipe1.getJoueur2()[i]->setFrame(equipe1.getJoueur2()[i]->animation(equipe1.getJoueur2()[i]->getFrame(), sf::Keyboard::K));
            }
        }
        onFocus->setFrame(onFocus->animation(onFocus->getFrame(), onFocus->getLastKey()));

        prev_clock = now_clock.getElapsedTime().asMilliseconds();

        // Destruction du terrain
        mousePosition = sf::Mouse::getPosition(window);
        // ball.setPosition(sf::Vector2f(mousePosition.x-ball.getRadius(), mousePosition.y-ball.getRadius()));
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            if(boom==false && ball.getRadius()==0){
                boom = true;
                ball.setPosition(sf::Vector2f(mousePosition.x, mousePosition.y));
            }
        }
        if(boom==true){
            ball.setRadius(ball.getRadius()+5);
            ball.setPosition(ball.getPosition().x-5, ball.getPosition().y-5);
            if(ball.getRadius()>=30){
                boom = false;
                int x_ball = ball.getPosition().x;
                int y_ball = ball.getPosition().y;
                int x_center = x_ball+ball.getRadius();
                int y_center = y_ball+ball.getRadius();
                for(int y = y_ball; y < y_ball+2*(y_center-y_ball); y++){
                    for(int x = x_ball; x < x_ball+2*(x_center-x_ball); x++){
                        if(sqrtf(powf(x-x_center, 2)+powf(y-y_center, 2))<ball.getRadius()){
                            if((x < map.getXsize() && x > -1) && (y < map.getYsize() && y > -1))
                            mapArray[x][y] = 0;
                            map.setChangeState();
                        }
                    }
                }
            }
        } else {
            ball.setRadius(ball.getRadius()-5);
            if(ball.getRadius()>0){
                ball.setPosition(ball.getPosition().x+5, ball.getPosition().y+5);
            } else {
                ball.setRadius(0);
            }
        }

        // Si la carte a été modifié, on la regénére
        if(map.wereChanged()){
            map.reset();
        }

        // Affichage de tout les éléments
        window.clear();
        window.draw(map.getGround());
        window.draw(map.getAir());

        window.draw(ball);

        for(size_t i = 0; i < equipe0.getJoueur1().size(); i++){
            if(!equipe0.getJoueur1()[i]->getFocus()){
                window.draw(equipe0.getJoueur1()[i]->getPenguin());
            }
        }
        for(size_t i = 0; i < equipe1.getJoueur2().size(); i++){
            if(!equipe1.getJoueur2()[i]->getFocus()){
                window.draw(equipe1.getJoueur2()[i]->getPenguin());
            }
        }

        window.draw(onFocus->getPenguin());

        window.draw(text);

        window.display();

        // Changement du penguin à contrôler
        if(turn_time-timer.getElapsedTime().asSeconds()<0){
            if(equipe0.getJoueur1()[0]->getFocus()){
                onFocus->setFocus(false);
                equipe1.getJoueur2()[0]->setFocus(true);
            }
            else if(equipe0.getJoueur1()[1]->getFocus()){
                onFocus->setFocus(false);
                equipe1.getJoueur2()[1]->setFocus(true);
            }
            else if(equipe0.getJoueur1()[2]->getFocus()){
                onFocus->setFocus(false);
                equipe1.getJoueur2()[2]->setFocus(true);
            }
            else if(equipe1.getJoueur2()[0]->getFocus()){
                onFocus->setFocus(false);
                equipe0.getJoueur1()[1]->setFocus(true);
            }
            else if(equipe1.getJoueur2()[1]->getFocus()){
                onFocus->setFocus(false);
                equipe0.getJoueur1()[2]->setFocus(true);
            }
            else if(equipe1.getJoueur2()[2]->getFocus()){
                onFocus->setFocus(false);
                equipe0.getJoueur1()[0]->setFocus(true);
            }
            timer.restart();
        }

    }

    return 0;
}