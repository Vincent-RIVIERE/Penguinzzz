#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    sf::Color color = sf::Color::Red;
    shape.setFillColor(color);

    while (window.isOpen()) {

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