#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>

void timer() {
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
}

int main() {

    sf::RenderWindow window(sf::VideoMode(1000, 700), "test");
    sf::CircleShape shape(100.f);
    sf::Color color = sf::Color::Red;
    shape.setFillColor(color);
    shape.setPosition(500-shape.getRadius(), 350-shape.getRadius());
    sf::RectangleShape bounds;
    sf::RectangleShape zone(sf::Vector2f(900, 600));
    zone.setPosition(50, 50);
    zone.setFillColor(sf::Color::Transparent);
    zone.setOutlineThickness(5);
    zone.setOutlineColor(sf::Color::White);
    float speed = 2.f;
    int time = 0;

    while (window.isOpen()) {
        std::thread t1 (timer);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if(bounds.getPosition().x>zone.getPosition().x) {
                shape.move(-speed,0.f);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if((bounds.getPosition().x+bounds.getSize().x)<(zone.getPosition().x+zone.getSize().x)) {
                shape.move(speed,0.f);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if(bounds.getPosition().y>zone.getPosition().y) {
                shape.move(0.f,-speed);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if((bounds.getPosition().y+bounds.getSize().y)<(zone.getPosition().y+zone.getSize().y)) {
                shape.move(0.f,speed);
            }
        }

        bounds.setSize(sf::Vector2f(shape.getLocalBounds().width ,shape.getLocalBounds().height));
        bounds.setPosition(shape.getPosition());
        bounds.setFillColor(sf::Color::Transparent);
        bounds.setOutlineThickness(5);
        bounds.setOutlineColor(sf::Color::Magenta);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.draw(bounds);
        window.draw(zone);
        window.display();
        time++;

        if (color==sf::Color::Red && time==60) {
            color = sf::Color::Green;
            shape.setFillColor(color);
            time=0;
        } else if (color==sf::Color::Green && time==60) {
            color = sf::Color::Blue;
            shape.setFillColor(color);
            time=0;
        } else if (color==sf::Color::Blue && time==60) {
            color = sf::Color::Red;
            shape.setFillColor(color);
            time=0;
        }

        t1.join();
    }
    return 0;
}