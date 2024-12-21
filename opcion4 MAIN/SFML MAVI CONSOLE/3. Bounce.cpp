#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "TP");

    // Posicion y velocidad inicial de la bola
    sf::Vector2f position(400.0f, 100.0f);  // Posicion inicial 
    sf::Vector2f velocity(0.0f, 0.0f);  // Velocidad inicial

    // Constante de gravedad 
    const float gravity = 0.00098f;  // Gravedad 
    const float bounceFactor = 0.85f;  //Rebote

    // Bucle principal del juego
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Actualizar la velocidad de la bola en funcion de la gravedad
        velocity.y += gravity;

        // Actualizar la posición de la bola en funcion de la velocidad
        position += velocity;

        // Comprobar si la bola ha llegado al suelo (límite inferior de la ventana)
        if (position.y > 600.0f - 20.0f)  // 20.0f es el radio de la bola
        {
            // Si la bola ha llegado al suelo, resetear su posición y aplicar rebote
            position.y = 600.0f - 20.0f;  // Restablecer la posición sobre el suelo
            velocity.y = -velocity.y * bounceFactor;  // Invertir la velocidad y reducirla a la mitad (rebote)
        }

        window.clear();

     
        sf::CircleShape ball(20.0f);  
        ball.setFillColor(sf::Color::Red);
        ball.setPosition(position);
        window.draw(ball);


        window.display();
    }

    return 0;
}