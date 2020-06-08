#include "Graphics.h"
#include <iostream>




Graphics::Graphics()
{
	

	Sala invernadero("Invernadero", 0, 0, 8, 10, sf::Color::Yellow);
	Sala salaBillar("Sala de billar", 12, 0, 6, 10, sf::Color::Red);
	Sala biblioteca("Biblioteca", 22, 0, 6, 10, sf::Color::Cyan);
	Sala estudio("Estudio", 32, 0, 8, 10, sf::Color::Magenta);
	Sala salaBaile("Sala de baile", 0, 12, 8, 6, sf::Color::Blue);
	Sala vestibulo("vestibulo", 30, 12, 10, 8, sf::Color::White);
	Sala cocina("cocina", 0, 20, 10, 10, sf::Color::Green);
	Sala comedor("comedor", 13, 20, 13, 10, sf::Color(150, 0, 150));
	Sala salon("salon", 30, 22, 10, 8, sf::Color(0, 150, 150));
	salas[0] = invernadero;
	salas[1] = salaBillar;
	salas[2] = biblioteca;
	salas[3] = estudio;
	salas[4] = salaBaile;
	salas[5] = vestibulo;
	salas[6] = cocina;
	salas[7] = comedor;
	salas[8] = salon;

	centroMensajes.color = sf::Color(150, 150, 150);
	centroMensajes.origen.x = 12;
	centroMensajes.origen.y = 12;
	centroMensajes.longitud.x = 14;
	centroMensajes.longitud.y = 6;
}


/*
Sala invernadero("Invernadero", 0, 0, 8, 10, sf::Color::Yellow);
Sala salaBillar("Sala de billar", 12, 0, 6, 10, sf::Color::Red);
Sala biblioteca("Biblioteca", 22, 0, 6, 10, sf::Color::Cyan);
Sala estudio("Estudio", 32, 0, 8, 10, sf::Color::Magenta);
Sala salaBaile("Sala de baile", 0, 12, 8, 6, sf::Color::Blue);
Sala vestibulo("vestibulo", 30, 12, 10, 8, sf::Color::White);
Sala cocina("cocina", 0, 20, 10, 10, sf::Color::Green);
Sala comedor("comedor", 13, 20, 13, 10, sf::Color(150, 0, 150));
Sala salon("salon", 30, 22, 10, 8, sf::Color(0, 150, 150));*/

bool isInRoom(float plx, float ply)
{
	if ((plx < 8 && ply < 10) || //invernadero
		(plx > 11 && plx < 18 && ply < 10) ||  //salaBillar
		(plx > 21 && plx < 28 && ply < 10) ||   //biblioteca
		(plx > 31 && ply < 10) ||			  //estudio
		(plx < 8 && ply > 11 && ply < 18) ||   //salaBaile
		(plx > 29 && ply > 11 && ply < 20) ||  //vestibulo
		(plx < 10 && ply > 19 && ply < 30) ||  //cocina
		(plx > 12 && plx < 26 && ply >19) ||  //comedor
		(plx > 29 && ply > 21))				  //salon
		return true;

	return false;
}

void Graphics::DrawDungeon(sf::TcpSocket &socket)
{
	yo = ListaJugadores.begin();
	sf::Packet packet;
	sf::RenderWindow _window(sf::VideoMode(800, 600), "Ventanita");
	sf::RectangleShape shape(sf::Vector2f(SIZE, SIZE));
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(2.f);


	int c_movements = 0;

	float playerX_init = playerX;
	float playerY_init = playerY;

	//PLAYER
	
	std::vector <sf::RectangleShape> cuadradoJugadores;
	
	for (yo; ListaJugadores.end() != yo; yo++)
	{
		if (yo->id == id)
		{
			break;
		}
	}

	sf::RectangleShape player(sf::Vector2f(SIZE, SIZE));
	/*player.setOutlineColor(sf::Color::Black);
	player.setOutlineThickness(1.f);*/
	for (int i = 0; i < ListaJugadores.size() ; i++ )
	{
		
		switch (i)
		{
		case 0:player.setOutlineColor(sf::Color::Black);
			break;
		case 1:player.setOutlineColor(sf::Color::Blue);
			break;
		case 2:player.setOutlineColor(sf::Color::Green);
			break;
		case 3:player.setOutlineColor(sf::Color::Magenta);
			break;
		case 4:player.setOutlineColor(sf::Color::Yellow);
			break;
		}
		player.setOutlineThickness(1.f);
		cuadradoJugadores.push_back(player);
	}
	std::cout << cuadradoJugadores.size() << std::endl;
	while (_window.isOpen())
	{
		sf::Event event;
		bool playerMoved = false;
		while (_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				_window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					packet.clear();
					_window.close();
					socket.send(packet);
					std::cout << "desconectado" << std::endl;
				}
				if (event.key.code == sf::Keyboard::Left)
				{
					if (yo->x > 0 && c_movements < movements)
					{
						if (!(yo->x == 26 && yo->y < 18 && yo->y>11))
						{
							yo->x--;
							if (!isInRoom(yo->x, yo->y))
								c_movements++;
						}
					}
					std::cout << "MOVIMIENTOS RESTANTES: " << movements - c_movements << std::endl;
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					if (yo->y > 0 && c_movements < movements)
					{
						if (!(yo->y == 18 && yo->x > 11 && yo->x < 26))
						{
							yo->y--;
							if (!isInRoom(yo->x, yo->y))
								c_movements++;

						}
					}
					std::cout << "MOVIMIENTOS RESTANTES: " << movements - c_movements << std::endl;
				}

				else if (event.key.code == sf::Keyboard::Right)
				{
					if (yo->x < 39 && c_movements < movements)
					{
						if (!(yo->x == 11 && yo->y < 18 && yo->y>11))
						{
							yo->x++;
							if (!isInRoom(yo->x, yo->y))
								c_movements++;
						}
					}
					std::cout << "MOVIMIENTOS RESTANTES: " << movements - c_movements << std::endl;
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					if (yo->y < 29 && c_movements < movements)
					{
						if (!(yo->y == 11 && yo->x > 11 && yo->x < 26))
						{
							yo->y++;
							if (!isInRoom(yo->x, yo->y))
								c_movements++;
						}
					}
					std::cout << "MOVIMIENTOS RESTANTES: " << movements - c_movements << std::endl;
				}
				else if (event.key.code == sf::Keyboard::BackSpace)
				{
					yo->x = playerX_init;
					yo->y = playerY_init;
					c_movements = 0;
					std::cout << "Reset";
					std::cout << c_movements;
				}
				else if (event.key.code == sf::Keyboard::Enter)
				{
					
				}
				break;

			}

		}
		_window.clear();
		std::vector<PlayerInfo>::iterator ot = ListaJugadores.begin();
		for (int i = 0; i < W_WINDOW_TITLE; i++)
		{
			for (int j = 0; j < H_WINDOW_TITLE; j++)
			{
				
				shape.setFillColor(sf::Color(90, 90, 90, 255));
				player.setFillColor(sf::Color(255, 0, 0, 255));

				shape.setPosition(sf::Vector2f(i*SIZE, j*SIZE));
				player.setPosition(sf::Vector2f(playerX*SIZE, playerY*SIZE));

				_window.draw(shape);
				
				
				for (std::vector<sf::RectangleShape>::iterator it = cuadradoJugadores.begin(); cuadradoJugadores.end() != it; it++)
				{
					shape.setFillColor(sf::Color(90, 90, 90, 255));
					it->setFillColor(sf::Color(255, 0, 0, 255));
					
					shape.setPosition(sf::Vector2f(i*SIZE, j*SIZE));
					it->setPosition(sf::Vector2f(ot->x*SIZE,ot->y*SIZE));

					_window.draw(shape);
					ot++;
				}
				ot = ListaJugadores.begin();
				
			}
		}
		//for (int i = 0; i < W_WINDOW_TITLE; i++)
		//{
		//	for (int j = 0; j < H_WINDOW_TITLE; j++)
		//	{

		//		shape.setFillColor(sf::Color(90, 90, 90, 255));
		//		player.setFillColor(sf::Color(255, 0, 0, 255));

		//		shape.setPosition(sf::Vector2f(i*SIZE, j*SIZE));
		//		player.setPosition(sf::Vector2f(playerX*SIZE, playerY*SIZE));

		//		_window.draw(shape);
		//	}
		//}


		for (size_t i = 0; i < salas.size(); i++)
		{
			salas[i].Draw(_window);
			for (std::vector<sf::RectangleShape>::iterator it = cuadradoJugadores.begin(); cuadradoJugadores.end() != it; it++)
			{
				_window.draw(*it);
			}
			/*salas[i].Draw(_window);
			_window.draw(player);*/
		}
		centroMensajes.Draw(_window);

		

		_window.display();
	}

}


Graphics::~Graphics()
{
}

