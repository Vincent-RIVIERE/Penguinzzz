#include "Map.hpp"

#ifndef PENGUIN_HPP
#define PENGUIN_HPP

class Penguin{
    public:
        /**
         * Constructeur par défaut, ne fait rien
        */
        Penguin();

        /**
         * Constructeur pour les penguins
         * @param name le nom du penguin @param team sont numéro d'équipe
        */
        Penguin(std::string name, int team);

        /**
         * Méthode qui applique une texture au penguin
         * @param sprite la texture a appliquer
        */
        void apply(int sprite);

        /**
         * Méthode qui permet d'animer le penguin, dépendant de ses déplacement
         * @param frame nombre d'images passés depuis la dernière modification de sprite d'animation
         * @param lastKey dernière touche appuyer pour déterminer l'animation a utiliser 
         * @return le numéro de l'image affiché pour déterminer l'état suivant de l'animation
        */
        int animation(int frame, sf::Keyboard::Key lastKey);

        /**
         * Déplacement instantané du penguin sur la carte
         * @param x position en x
         * @param y position en y
        */
        void setPosition(float x, float y);

        /**
         * Déplacement du penguin sur la carte en fonction de sa vitesse
         * @param x_speed vitesse selon x
         * @param y_speed vitesse selon y
         * @param dt temps passé entre deux images pour avoir un déplacement en fonction du temps
        */
        void move(int x_dir, int y_dir, float dt);

        /**
         * @return l'image du penguin actuelle
        */
        sf::Sprite getPenguin();       

        /**
         * @return la zone de collision du penguin 
        */ 
        sf::VertexArray getBounds();

        /**
         * @return les vitesses du peguin défini dans le constructeur
        */
        float getSpeed(int n);
        
        /**
         * Méthode pour modifier la vitesse lié à la gravité
         * @param n vitesse a appliquer
        */
        void setYspeed(float n);
        
        /**
         * Méthode pour incrémenter/décrémenter la vitesse lié à la gravité
        */
        void addYspeed(float n);

        /**
         * @return la dernière touche utilisé lors du contrôle du penguin
        */
        sf::Keyboard::Key getLastKey();
        
        /**
         * Méthode pour enregistrer la dernière touche utilisé lors du contrôle du penguin
        */
        void setLastKey(sf::Keyboard::Key key);
        
        /**
         * @return le nombre d'images passées par le penguin dans un état pour les animations
        */
        int getFrame();
        
        /**
         * Méthode pour conserver le nombre d'images passées par le penguin dans un état pour les animations
        */
        void setFrame(int n);
        
        /**
         * @return true si le penguin est contrôlé par le joueur, false sinon
        */
        bool getFocus();
        
        /**
         * Méthode qui modifie l'état de contrôle du penguin par le joueur
        */
        void setFocus(bool f);
    private:
        std::string name;
        sf::Sprite penguin;
        sf::IntRect sprite[8];
        sf::Texture texture;
        int currentSprite;
        sf::VertexArray bounds;
        sf::Keyboard::Key lastKey;
        float speed[2];
        int frame;
        bool focus;
};

#endif