#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "test");
    sf::CircleShape shape(100.f);
    sf::Color color = sf::Color::Red;
    shape.setFillColor(color);

    while (window.isOpen()) {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            shape.move(-1.f,0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            shape.move(1.f,0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            shape.move(0.f,-1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            shape.move(0.f,1.f);
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();

        if (color==sf::Color::Red) {
            color = sf::Color::Green;
            shape.setFillColor(color);
        } else if (color==sf::Color::Green) {
            color = sf::Color::Blue;
            shape.setFillColor(color);
        } else if (color==sf::Color::Blue) {
            color = sf::Color::Red;
            shape.setFillColor(color);
        }

    }

    return 0;
}