#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
using namespace sf;


class Puntaje {
private:
	Font fuente;
	int puntos = 0;
	Text puntajeT;
	sf::Clock clock;
	bool juegoIniciado = false;
public:
	Puntaje(Font& newFont) {
		fuente = newFont;
		puntajeT.setFont(fuente);
		puntajeT.setPosition(0, 0);
		puntajeT.setCharacterSize(30);
		puntajeT.setFillColor(Color::White);
	};
	void posicion(int a) {
		switch (a) {
		case 1:
			puntajeT.setPosition(0, 0);
			break;
		case 2:
			puntajeT.setPosition(265, 300);
			break;
		};
	};
	void actualizarPuntaje() {
		puntajeT.setString("Puntaje: " + std::to_string(puntos));
	};

	void Dibujar(RenderWindow& App) {
		App.draw(puntajeT);
	};
	void SumaPuntaje(int valor) {
		puntos += valor;
	};

};

class Reloj {
private:
	sf::Clock clock;
	Text relojT;
	bool juegoIniciado = false;
	Font fuente;

public:
	Reloj(Font& newFont) {
		fuente = newFont;
		relojT.setFont(fuente);
		relojT.setPosition(300, 00); // Posición donde aparecerá el reloj
		relojT.setCharacterSize(30);
		relojT.setFillColor(Color::White);
	}

	void iniciarReloj() {
		if (!juegoIniciado) {
			clock.restart();  // Reinicia el reloj solo si no ha sido iniciado
			juegoIniciado = true;  // Cambiar el estado para indicar que el juego ha comenzado
		}
	}

	void actualizarTiempo() {
		if (juegoIniciado) {
			float tiempo = clock.getElapsedTime().asSeconds(); // Obtener el tiempo transcurrido
			relojT.setString("Tiempo: " + std::to_string(tiempo));  // Mostrar el tiempo en segundos
		}
	}

	void Dibujar(RenderWindow& App) {
		App.draw(relojT);
	}
	float getTiempoTranscurrido() const {
		return clock.getElapsedTime().asSeconds(); 
	}
};
class Fondo {
private:
	Sprite fondo;
	Texture texture;
public:
	void CambiarFondo(Texture& newTexture) {
		texture = newTexture;
		fondo.setTexture(texture);
	}
	void HacerFondo(RenderWindow& App) {
		App.draw(fondo);
	}
};


int main()
{
	Font fuente;
	fuente.loadFromFile("arial.ttf");
	Puntaje puntaje(fuente);
	Reloj reloj(fuente);
	puntaje.actualizarPuntaje();
	reloj.actualizarTiempo();

	Texture MenuJ, InstruccionesJ, GameoverJ, Juegofondo;
	MenuJ.loadFromFile("MenuJuego.png");
	InstruccionesJ.loadFromFile("JuegoInstrucciones.png");
	GameoverJ.loadFromFile("JuegoGameover.png");
	Juegofondo.loadFromFile("JuegoM.png");

	Texture canion,bala;
	canion.loadFromFile("canon1.png");
	bala.loadFromFile("bullet.png");
	Sprite canonT,balaT;
	canonT.setTexture(canion);
	balaT.setTexture(bala);
	canonT.setPosition(-28, 250);
	balaT.setPosition(-28, 278);
	Fondo backgroundJuego;
	backgroundJuego.CambiarFondo(MenuJ);
	// Crear una ventana SFML
	sf::RenderWindow window(sf::VideoMode(800, 600), "TP U6");
	// Definir la posición y velocidad inicial del objeto

	sf::Vector2f position(200.0f, 00.0f);
	sf::Vector2f position2(500.0f, 00.0f);
	sf::Vector2f position3(750.0f, 00.0f);
	sf::Vector2f velocity(00.0f, 50.0f);
	sf::Vector2f velocity2(00.0f, 40.0f);
	sf::Vector2f velocity3(00.0f, 30.0f);
	// Velocidad inicial en el eje x (MRU) yen el eje y(MRUV)
	// Constante de aceleración para el MRUV
	const float acceleration = 0.1f;
	
	// Bucle principal del juego
	const float speed = 0.18f;
	const float bulletSpeed = 0.3f;
	bool bulletMoving = false;
	bool EmpezarJuego = false;
	bool IniciarJuego = false;

	sf::RectangleShape Rec1(sf::Vector2f(50.0f, 50.0f));
	sf::RectangleShape Rec2(sf::Vector2f(50.0f, 50.0f));
	sf::RectangleShape Rec3(sf::Vector2f(50.0f, 250.0f));
	Rec1.setFillColor(sf::Color::Red);
	Rec2.setFillColor(sf::Color::Red);
	Rec3.setFillColor(sf::Color::Green);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			// Verificar si una tecla es presionada
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Num1) {
					backgroundJuego.CambiarFondo(Juegofondo);
					EmpezarJuego = true;
					IniciarJuego = true;
					reloj.iniciarReloj();
				}

				if (event.key.code == sf::Keyboard::Num2 && !EmpezarJuego) {
					backgroundJuego.CambiarFondo(InstruccionesJ);
				}

				if (event.key.code == sf::Keyboard::Num3 && !EmpezarJuego) {
					window.close();
				}

				if (event.key.code == sf::Keyboard::Num4 && !EmpezarJuego) {
					backgroundJuego.CambiarFondo(MenuJ);
				}

				if (event.key.code == sf::Keyboard::Num5) {
					puntaje.SumaPuntaje(5);
				}
			}
		}

		//true
		if (EmpezarJuego){
		// Actualizar la velocidad del objeto en función de la aceleración y eltiempo transcurrido
		float deltaTime = 0.1f / 60.0f; // Suponemos que el juego se estáejecutando a 60 FPS
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			sf::Vector2f currentPos = canonT.getPosition();  // Obtener la posición actual
			if (currentPos.y > 0) {
				canonT.setPosition(currentPos.x, currentPos.y - speed);
				if (!bulletMoving) {
				balaT.setPosition(balaT.getPosition().x, balaT.getPosition().y - speed);
				};
			};
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			sf::Vector2f currentPos = canonT.getPosition(); // Obtener la posición actual
			if (currentPos.y < 550) {
			canonT.setPosition(currentPos.x, currentPos.y + speed);
			if (!bulletMoving) {
				balaT.setPosition(balaT.getPosition().x, balaT.getPosition().y + speed);
			};
		}
		};
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !bulletMoving) {
			bulletMoving = true;
		}

		// actualizar su posición hacia la derecha
		if (bulletMoving) {
			sf::Vector2f bulletPos = balaT.getPosition();
			balaT.setPosition(bulletPos.x + bulletSpeed, bulletPos.y);

			// Si la bala se sale de la pantalla, detener su movimiento
			if (balaT.getPosition().x > window.getSize().x) {
				bulletMoving = false;  // La bala deja de moverse
				balaT.setPosition(canonT.getPosition().x, canonT.getPosition().y+28);  // Resetear la posición de la bala al cañón
			}
		}

		velocity.y += acceleration * deltaTime;
		velocity2.y += acceleration * deltaTime;
		velocity3.y += acceleration * deltaTime;

		// Actualizar la posición del objeto en función de la velocidad y eltiempo transcurrido
		position += velocity * deltaTime;
		position2 += velocity2 * deltaTime;
		position3 += velocity3 * deltaTime;

		// Comprobar si el objeto ha llegado al suelo o techo (límite inferior de laventana)
		if (position.y > 550.0f)
		{
			// Si el objeto ha llegado al suelo, hacer que rebote invirtiendo suvelocidad en y
			position.y = 550.0f;
			velocity.y = -velocity.y;
		}
		if (position.y < 0.0f)
		{
			// Si el objeto ha llegado al suelo o techo, hacer que rebote invirtiendo suvelocidad en y
			position.y = 0.0f;
			velocity.y = -velocity.y;
		}
		if (position2.y > 550.0f)
		{
			// Si el objeto ha llegado al suelo, hacer que rebote invirtiendo suvelocidad en y
			position2.y = 550.0f;
			velocity2.y = -velocity2.y;
		}
		if (position2.y < 0.0f)
		{
			// Si el objeto ha llegado al suelo o techo, hacer que rebote invirtiendo suvelocidad en y
			position2.y = 0.0f;
			velocity2.y = -velocity2.y;
		}
		if (position3.y > 350.0f)
		{
			// Si el objeto ha llegado al suelo, hacer que rebote invirtiendo suvelocidad en y
			position3.y = 350.0f;
			velocity3.y = -velocity3.y;
		}
		if (position3.y < 0.0f)
		{
			// Si el objeto ha llegado al suelo o techo, hacer que rebote invirtiendo suvelocidad en y
			position3.y = 0.0f;
			velocity3.y = -velocity3.y;
		}
		if (balaT.getGlobalBounds().intersects(Rec1.getGlobalBounds())) {
			bulletMoving = false;  
			puntaje.SumaPuntaje(10);  
			balaT.setPosition(canonT.getPosition().x, canonT.getPosition().y + 28);  // Resetear la posición de la bala al cañón
		}

		if (balaT.getGlobalBounds().intersects(Rec2.getGlobalBounds())) {
			bulletMoving = false;  
			puntaje.SumaPuntaje(15);  
			balaT.setPosition(canonT.getPosition().x, canonT.getPosition().y + 28);  // Resetear la posición de la bala al cañón
		}

		if (balaT.getGlobalBounds().intersects(Rec3.getGlobalBounds())) {
			bulletMoving = false;  
			puntaje.SumaPuntaje(50); 
			balaT.setPosition(canonT.getPosition().x, canonT.getPosition().y + 28);  // Resetear la posición de la bala al cañón
		}
		puntaje.actualizarPuntaje();
		reloj.actualizarTiempo();
		}; //true

		if (reloj.getTiempoTranscurrido() > 30) {
			backgroundJuego.CambiarFondo(GameoverJ); // Cambiar el fondo
			puntaje.actualizarPuntaje(); // Actualizar el puntaje
			puntaje.posicion(2); // Posicionar el puntaje
			EmpezarJuego = false; // Detener el juego

			
			while (window.isOpen()) {
				sf::Event event2;
				while (window.pollEvent(event2)) {
					
					if (event2.type == sf::Event::Closed || event2.type == sf::Event::KeyPressed) {
						window.close();
					}
				}

				
				window.clear(Color::White);

				
				backgroundJuego.HacerFondo(window);
				puntaje.Dibujar(window);

				
				window.display();
			}
			
			break;
		}
		// Limpiar la ventana
		window.clear();
		// Dibujar el objeto en su posición actual
        Rec1.setPosition(position);
		Rec2.setPosition(position2);
		Rec3.setPosition(position3);
		backgroundJuego.HacerFondo(window);
		if (IniciarJuego) {
			window.draw(Rec1);
			window.draw(Rec2);
			window.draw(Rec3);
			puntaje.Dibujar(window);
			reloj.Dibujar(window);
			window.draw(balaT);
			window.draw(canonT);
		};


		// Mostrar todo en la ventana
		window.display();
	}
	return 0;
}