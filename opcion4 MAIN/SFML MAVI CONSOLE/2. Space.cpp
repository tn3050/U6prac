#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{

    RenderWindow window(sf::VideoMode(800, 600), "TP");

    // posici�n inicial del objeto
    sf::Vector2f position(400.0f, 300.0f);  // Comienza en el centro de la ventana

    // Velocidad y aceleraci�n
    float speed = 0.0f;       // Velocidad inicial (en p�xeles por segundo)
    const float maxSpeed = 200.0f;   // Velocidad m�xima
    const float acceleration = 50.0f;  // Aceleraci�n por segundo
    const float deceleration = 40.0f;  // Desaceleraci�n cuando cambia la direccion

    // Tiempo entre actualizaciones
    Clock clock;


    sf::CircleShape object(20.0f);  // Radio de 20 p�xeles
    object.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
 
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Obtener el tiempo transcurrido entre cuadros
        float deltaTime = clock.restart().asSeconds();

        // Comprobar las teclas presionadas para controlar la direccion
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            // Aceleraci�n hacia la derecha
            if (speed < maxSpeed) {
                speed += acceleration * deltaTime;  // Aumentar la velocidad
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            // Aceleraci�n hacia la izquierda
            if (speed > -maxSpeed) {
                speed -= acceleration * deltaTime;  // Aumentar la velocidad negativa
            }
        }
       
        

        // Asegurarse de que la velocidad no supere los l�mites
        if (speed > maxSpeed) speed = maxSpeed;
        if (speed < -maxSpeed) speed = -maxSpeed;

        // Actualizar la posici�n en base a la velocidad
        position.x += speed * deltaTime;

        // Si el c�rculo se ha salido de la pantalla por el lado derecho o izquierdo
        if (position.x > window.getSize().x) {
            position.x = window.getSize().x;  // Mantener dentro de la ventana
        }
        else if (position.x < 0) {
            position.x = 0;  // Mantener dentro de la ventana
        }


        window.clear();


        object.setPosition(position);


        window.draw(object);

 
        window.display();
    }

    return 0;
}