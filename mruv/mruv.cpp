#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
using namespace std;
using namespace sf;


class Coche
{
    Sprite *spr_coche;
    Texture *txt_coche;
    Vector2f velocidad; ///en x, y
    Vector2f aceleracion;

public:
    Coche()
    {
        txt_coche = new Texture;
        txt_coche->loadFromFile("captura.png"); ///cargar textura del coche
        spr_coche = new Sprite(*txt_coche);
        spr_coche->setPosition(1,20); ///pos inicio

        velocidad.x=0;
        velocidad.y= -10 * 5; ///negativo para salto

        aceleracion.x=0;
        aceleracion.y=9.78;
    }
    Sprite get_sprite() {return *spr_coche; };
    void actualizar(float delta_t)
    {
        ///v= a*t;
        velocidad.x += aceleracion.x * delta_t;
        velocidad.y += aceleracion.y * delta_t;
        ///x = x_0 + v*t
        spr_coche->setPosition(spr_coche->getPosition().x + velocidad.x * delta_t, spr_coche->getPosition().y + velocidad.y*delta_t);

    }

};

class Juego
{
    sf::RenderWindow* ventana1;
    sf::Clock* reloj1;
    sf::Time* tiempo1;
    float tiempo2;

    bool gameover = false;
    float fps;

    Coche *jugador1;
public:

    Juego(sf::Vector2f resolucion, string titulo) ///pone la ventana 1
    {
        ventana1 = new RenderWindow(sf::VideoMode(resolucion.x, resolucion.y), titulo);
        ventana1->setFramerateLimit(60);
        fps = 1/60.f; ///cada un segundo 60
        reloj1 = new sf::Clock();
        tiempo1 = new sf::Time();
        tiempo2 = 0.f;

        jugador1 = new Coche();
        gameloop();
    }
    void gameloop() ///tiempo con el que vamos a ir vanzando por los fps
    {
        while(!gameover)
        {
            *tiempo1 = reloj1->getElapsedTime();
            if(tiempo1->asSeconds() > (tiempo2+fps))
            {
                tiempo2 = tiempo1->asSeconds();
                ventana1->clear();
                jugador1->actualizar(tiempo2);
                ventana1->draw(jugador1->get_sprite()); ///dibuja coche
                ventana1->display();
            }
        }
    }
};

int main()
{
    Juego partida1({800,600}, "RUBEL PAPI");
}
