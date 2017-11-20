
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <math.h>
#include <sstream>
using namespace std;
using namespace sf;
class Coche
{
    public:
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
        spr_coche->setScale({0.1f,0.1f});
        spr_coche->setPosition(pos); ///pos inicio
//        velocidad=vel;
//        velocidad.x=0;
//        velocidad.y= 0; ///negativo para salto
       // aceleracion.x=0;
        //aceleracion.y=2;
    }
    Sprite get_sprite() {return *spr_coche; };
    void actualizar(float delta_t)
    {
        delta_t /= 10;
        ///v= a*t;
        velocidad.x += aceleracion.x * delta_t;
        velocidad.y += aceleracion.y * delta_t;
        ///x = x_0 + v*t
        if(spr_coche->getPosition().y > 400){
                 spr_coche->setPosition(spr_coche->getPosition().x + velocidad.x * delta_t, 400);
                 velocidad={0.f,0.f};
                 aceleracion={0.f,0.f};
                // spr_coche->setPosition(100,400);
        }
        spr_coche->setPosition(spr_coche->getPosition().x + velocidad.x * delta_t, spr_coche->getPosition().y + velocidad.y*delta_t);

    }
};
class Juego
{
public:
    Juego(Vector2f resolucion, string titulo)
    {
        ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
        ventana1->setFramerateLimit(60);
        fps = 1/10.f; ///cada un segundo 60
        reloj1 = new sf::Clock();
        tiempo1 = new sf::Time();
        tiempo2 = 0.f;
        txt_worm= new Texture; ///gusano
        txt_worm->loadFromFile("worm.png");
        spr_worm = new Sprite(*txt_worm);
       // spr_worm->setPosition(0,400); ///400
        spr_worm->setScale(0.2f, 0.2f);
        txt_aim = new Texture;
        txt_aim->loadFromFile("flecha.png");
        spr_aim = new Sprite(*txt_aim);
        spr_aim->setScale(Vector2f(0.2f,0.2f));
        spr_aim->setPosition(0,400); ///+32,+16
        spr_aim->setOrigin(spr_aim->getTexture()->getSize().x / 2.f, spr_aim->getTexture()->getSize().y / 2.f);
        evento1 = new Event;
        font.loadFromFile("fonts/Gidole.ttf");
       jugador1 = new Coche(spr_aim->getPosition());

        gameloop();
    }
    void gameloop()
    {
         while(!gameover)
        {
            *tiempo1 = reloj1->getElapsedTime();
            if(tiempo1->asSeconds() > (tiempo2+fps))
            {
                tiempo2 = tiempo1->asSeconds();
                procesar_eventos();
                ventana1->clear();
               // ventana1->draw(*spr_worm);
                imprimir();
                ventana1->draw(*spr_aim);
                procesar_eventos();
                 if(jugador1 != NULL) ///si esta creado que lo dibuje
                {
                    jugador1->actualizar(tiempo2);
                    ventana1->draw(jugador1->get_sprite());
                }
                ventana1->display();
            }
        }
    }
    void procesar_eventos()
    {
        while(ventana1->pollEvent(*evento1))
        {
            switch (evento1->type)
            {
                case Event::Closed:
                    ventana1->close();
                    break;
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Space))
        {
          //  jugador1 = new Coche(spr_aim->getPosition());
            float angulo_mira2 = spr_aim->getRotation();
            jugador1->aceleracion.x=0;
            jugador1->aceleracion.y=9.8;
            velocidades.x = potencia_disparo * cos(grados_a_radianes(angulo_mira2));
            velocidades.y = potencia_disparo * sin(grados_a_radianes(angulo_mira2));
            jugador1->velocidad=velocidades;

        }
         if(Keyboard::isKeyPressed(Keyboard::Left))
        {
            spr_aim->rotate(-1);
            angulo_mira += 1;
        }
        else if(Keyboard::isKeyPressed(Keyboard::Right))
        {
            spr_aim->rotate(1);
            angulo_mira -=1;

        }
        else if(Keyboard::isKeyPressed(Keyboard::A))
            imprimir_consola();

    }
    float grados_a_radianes(float grados) {return grados * 3.14 / 180; }

    void imprimir_consola()
    {
        cout<<"------MOVIMIENTO PARABOLICO-------------"<<endl;
        cout<<"Gravedad: 9.8"<<endl;
        cout<<"X: "<<jugador1->get_sprite().getOrigin().x<<endl;
        cout<<"Altura"<<jugador1->get_sprite().getOrigin().y<<endl;
        cout<<"Angulo: "<<angulo_mira<< " en radian: "<<grados_a_radianes(angulo_mira)<<endl;
        cout<<"Posicion final X: "<<jugador1->get_sprite().getPosition().x<<endl;
        cout<<"Velocidad inicial: "<<potencia_disparo<<endl;
        cout<<"Velocidad en X: "<< velocidades.x<<endl;
        cout<<"Velocidad final Y: "<<velocidades.y*-1<<endl;
      
    }
    string float_string(float f)
    {
        ostringstream ss;
        ss << f;
        return ss.str();
    }
    void imprimir()
    {
        font.loadFromFile("fonts/Gidole.ttf");
        Text pos_x("X: " + float_string(jugador1->get_sprite().getPosition().x) + "m",font,20);
        Text pos_y("Y: " + float_string(jugador1->get_sprite().getPosition().y) + "m",font,20);
        pos_y.setPosition(pos_x.getPosition().x, pos_x.getPosition().y+20);
        Text vel_t("Velocidad inicial: " + float_string(potencia_disparo) + "Km/h",font,20);
        vel_t.setPosition(pos_x.getPosition().x, pos_y.getPosition().y+20);
        Text vel_x("Velocidad x: " + float_string(jugador1->velocidad.x) + "Km/h",font,20);
        vel_x.setPosition(pos_x.getPosition().x, vel_t.getPosition().y+20);
        Text vel_y("Velocidad y: " + float_string(jugador1->velocidad.y) + "Km/h",font,20);
        vel_y.setPosition(pos_x.getPosition().x, vel_x.getPosition().y+20);
        Text angulo("Angulo: " + float_string(angulo_mira) + "°  == " + float_string(grados_a_radianes(angulo_mira)) + "radián" ,font,20);
        angulo.setPosition(pos_x.getPosition().x, vel_y.getPosition().y+20);
        ventana1->draw(pos_x);
        ventana1->draw(pos_y);
        ventana1->draw(vel_t);
        ventana1->draw(vel_x);
        ventana1->draw(vel_y);
        ventana1->draw(angulo);
    }
private:
    RenderWindow* ventana1;
    Clock* reloj1;
    Time* tiempo1;
    float tiempo2;
    Event* evento1;
    Sprite* spr_worm;
    Texture* txt_worm;
    Sprite* spr_aim;
    Texture* txt_aim;
    float fps;
    bool gameover=false;
    Coche *jugador1;
    Font font;
    float potencia_disparo=50;
    Vector2f velocidades;
    float angulo_mira=0;
};
int main()
{
    Juego partida1({900,600}, "FISICA");
}
