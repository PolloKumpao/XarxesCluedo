#pragma once
#include <PlayerInfo.h>
#include <SFML\Network.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <fcntl.h>
#include "Graphics.h"



sf::TcpSocket socket;
std::string prueba = "Prueba conexion";
sf::Packet pack;

enum comandos { START, LANZADADOS, ELEGIRPISTA, REVELARPISTA, MOVIMIENTO, NUEVAPOSICION, DEDUCCION, 
				ENVIOSUPOSICION, DESMENTIRCS, DESMENTIRSC, DESMENTIDO, DESMENTIDOGENERAL, RESOLVERCS, RESOLVERSC, RESOLUCIONCORRECTA };



int main()
{
	PlayerInfo playerInfo;
	Graphics g;
	
	
		sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect("localhost", 50000, sf::milliseconds(15.f));
		sf::Packet packetMano;
		std::vector<carta> mano;
		int prueba  = 0;
		int size = 0;
		if (status != sf::Socket::Done)
		{
			std::cout << "Error al establecer conexion\n";
			exit(0);
		}
		else
		{
			std::cout << "Se ha establecido conexion\n";
		}
		std::string str = "hola";
	
		do
		{
			socket.receive(packetMano);
			packetMano >> size;
			
			std::cout << size << std::endl;
			for (int i = 0; i < size; i++)
			{
				packetMano >> prueba;
				
				switch (prueba)
				{
				case 1:
					mano.push_back((carta(PERSONAJE, "Amapola", 1)));
					break;
				case 2:
					mano.push_back((carta(PERSONAJE, "Rubio", 2)));
					break;
				case 3:
					mano.push_back((carta(PERSONAJE, "Orquidea", 3)));
					break;
				case 4:
					mano.push_back((carta(PERSONAJE, "Celeste", 4)));
					break;
				case 5:
					mano.push_back((carta(PERSONAJE, "Prado", 5)));
					break;
				case 6:
					mano.push_back((carta(PERSONAJE, "Mora", 6)));
					break;
				case 7:
					mano.push_back((carta(PERSONAJE, "Candelabro", 7)));
					break;
				case 8:
					mano.push_back((carta(PERSONAJE, "Cuerda", 8)));
					break;
				case 9:
					mano.push_back((carta(PERSONAJE, "Puñal", 9)));
					break;
				case 10:
					mano.push_back((carta(PERSONAJE, "Pistola", 10)));
					break;
				case 11:
					mano.push_back((carta(PERSONAJE, "Tuberia de Plomo", 11)));
					break;
				case 12:
					mano.push_back((carta(PERSONAJE, "Herramienta", 12)));
					break;
				case 13:
					mano.push_back((carta(PERSONAJE, "Biblioteca", 13)));
					break;
				case 14:
					mano.push_back((carta(PERSONAJE, "Cocina", 14)));
					break;
				case 15:
					mano.push_back((carta(PERSONAJE, "Billar", 15)));
					break;
				case 16:
					mano.push_back((carta(PERSONAJE, "Baile", 16)));
					break;
				case 17:
					mano.push_back((carta(PERSONAJE, "Invernadero", 17)));
					break;
				case 18:
					mano.push_back((carta(PERSONAJE, "Comedor", 18)));
					break;
				case 19:
					mano.push_back((carta(PERSONAJE, "Vestibulo", 19)));
					break;
				case 20:
					mano.push_back((carta(PERSONAJE, "Salon", 20)));
					break;
				case 21:
					mano.push_back((carta(PERSONAJE, "Estudio", 21)));
					break;
				default:
					break;
				}
			}
			for (int i = 0; i < mano.size(); i++)
			{
				std::cout << mano[i].nombre << std::endl;
			}
			std::cout << "Escribe ... ";
			std::getline(std::cin, str);
			sf::Packet packet;
			packet << str;
			status = socket.send(packet);
			if (status != sf::Socket::Done)
			{
				std::cout << "Error al enviar\n";
			}
			std::cout << std::endl;
		} while (str != "exit");
		socket.disconnect();

	


	//sf::Socket::Status status = socket.connect("localhost", 5000, sf::seconds(5.f));
	//if (status != sf::Socket::Done)
	//{
	//	std::cout << "No se ha podido conectar";
	//}
	//else {
	//	std::cout << "Conectado" << std::endl;
	//}

	//pack << prueba;
	//socket.send(pack);

	//while (1)
	//{

	//}
	g.DrawDungeon();
	return 0;
}