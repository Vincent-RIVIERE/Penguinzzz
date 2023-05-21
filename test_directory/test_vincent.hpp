#include <SFML/Graphics.hpp>

class Penguin{
    public:
        Penguin(std::string name, int team);

        void apply(int sprite);
        int animation(int frame, sf::Keyboard::Key lastKey);

        void setPosition(float x, float y);
        void move(float x_speed, float y_speed, float dt);

        sf::Sprite getPenguin();        
        sf::VertexArray getBounds();
        sf::RectangleShape getArea();
        float getSpeed();
    private:
        std::string name;

        sf::Sprite penguin;
        sf::IntRect sprite[8];
        sf::Texture texture;
        int currentSprite;
        
        sf::VertexArray bounds;
        sf::RectangleShape activeArea;
        
        float speed;
};