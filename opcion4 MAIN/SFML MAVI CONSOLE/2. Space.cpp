#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{

    RenderWindow window(sf::VideoMode(800, 600), "TP");

    // posición inicial del objeto
    sf::Vector2f position(400.0f, 300.0f);  // Comienza en el centro de la ventana

    // Velocidad y aceleración
    float speed = 0.0f;       // Velocidad inicial (en píxeles por segundo)
    const float maxSpeed = 200.0f;   // Velocidad máxima
    const float acceleration = 50.0f;  // Aceleración por segundo
    const float deceleration = 40.0f;  // Desaceleración cuando cambia la direccion

    // Tiempo entre actualizaciones
    Clock clock;


    sf::CircleShape object(20.0f);  // Radio de 20 píxeles
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
            // Aceleración hacia la derecha
            if (speed < maxSpeed) {
                speed += acceleration * deltaTime;  // Aumentar la velocidad
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            // Aceleración hacia la izquierda
            if (speed > -maxSpeed) {
                speed -= acceleration * deltaTime;  // Aumentar la velocidad negativa
            }
        }
       
        

        // Asegurarse de que la velocidad no supere los límites
        if (speed > maxSpeed) speed = maxSpeed;
        if (speed < -maxSpeed) speed = -maxSpeed;

        // Actualizar la posición en base a la velocidad
        position.x += speed * deltaTime;

        // Si el círculo se ha salido de la pantalla por el lado derecho o izquierdo
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