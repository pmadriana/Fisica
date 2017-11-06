/*#include <iostream>
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
    Coche(Vector2f pos)
    {
        txt_coche = new Texture;
        txt_coche->loadFromFile("granada.png"); ///cargar textura del coche
        spr_coche = new Sprite(*txt_coche);
        spr_coche->setPosition(pos); ///pos inicio

        velocidad.x=0;
        velocidad.y= 0; ///negativo para salto

        aceleracion.x=0;
        aceleracion.y=9.78;
    }
    Sprite get_sprite() {return *spr_coche; };
    void actualizar(float delta_t)
    {
        delta_t /= 10;
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
///tiro parabolico
    Event *evento1;
    Sprite *spr_worm;
    Texture *txt_worm;

    Sprite *spr_aim;
    Texture *txt_aim;
    //Coche *jugador1;
    Coche *granada1;
public:

    Juego(sf::Vector2f resolucion, string titulo) ///pone la ventana 1
    {
        ventana1 = new RenderWindow(sf::VideoMode(resolucion.x, resolucion.y), titulo);
        ventana1->setFramerateLimit(60);
        fps = 1/60.f; ///cada un segundo 60
        reloj1 = new sf::Clock();
        tiempo1 = new sf::Time();
        tiempo2 = 0.f;
       // jugador1 = new Coche();
        txt_worm= new Texture; ///gusano
        txt_worm->loadFromFile("worm.png");
        spr_worm = new Sprite(*txt_worm);
        spr_worm->setPosition(0,400);
        spr_worm->setScale(0.5f, 0.5f);

        txt_aim = new Texture;
        txt_aim->loadFromFile("aim.png");
        spr_aim = new Sprite(*txt_aim);
        spr_aim->setPosition(spr_worm->getPosition().x + 200, spr_worm->getPosition().y + 10);
        spr_aim->setOrigin(spr_aim->getTexture()->getSize().x / 2.f, spr_aim->getTexture()->getSize().y / 2.f);

        evento1 = new Event;
        granada1 = new Coche(spr_aim->getPosition());
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
//                jugador1->actualizar(tiempo2);
//                ventana1->draw(jugador1->get_sprite()); ///dibuja coche
                ventana1->draw(*spr_worm);
                ventana1->draw(*spr_aim);
                if(granada1 != NULL) ///si esta creado que lo dibuje
                {
                    granada1->actualizar(tiempo2);
                    ventana1->draw(granada1->get_sprite());
                }
                ventana1->display();
            }
        }
    }
};

int main()
{
    Juego partida1({800,600}, "RUBEL PAPI");
}
*/
