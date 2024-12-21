#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

using namespace sf;

int main()
{

    RenderWindow window(VideoMode(800, 800), "TP");

    // posicion inicial objeto
    sf::Vector2f position(0.0f, 300.0f);

    // Definir la velocidad inicial del objeto
    float speed = 400.0f;  // Velocidad inicial

    // Velocidad final (máxima)
    const float finalSpeed = 1000.0f;

    // Definir el reloj para controlar el tiempo 
    Clock clock;


    sf::CircleShape object(20.0f);
    object.setFillColor(sf::Color::Blue);

    while (window.isOpen())
    {
        // Manejo de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calcular el tiempo transcurrido entre cuadros
        float deltaTime = clock.restart().asSeconds();

        // Actualizar la posición del objeto
        position.x += speed * deltaTime;

        // Si el círculo se ha salido de la pantalla por el lado derecho
        if (position.x > window.getSize().x)
        {
            // Vuelve por el lado izquierdo
            position.x = -20;

            // Aumenta la velocidad solo si no ha alcanzado la velocidad final
            if (speed < finalSpeed)
            {
                speed += 200.0f;  // Incremento de la velocidad
            }
        }


        window.clear();


        object.setPosition(position);


        window.draw(object);

     
        window.display();
    }

    return 0;
}