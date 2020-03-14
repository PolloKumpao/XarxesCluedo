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




int main()
{
	PlayerInfo playerInfo;
	Graphics g;
	g.DrawDungeon();
	sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect("localhost", 50000, sf::milliseconds(15.f));
		sf::Packet packetMano;
		std::vector<carta> mano;
		std::vector<PlayerInfo> players;
		int cartaRepartida  = 0;
		int size = 0;
		int habitacionInicial[3];
		sf::Packet packHabitacion;
		int numPlayers=0;
		int id = 0;

		if (status != sf::Socket::Done)
		{
			std::cout << "Error al establecer conexion\n";
			exit(0);
		}
		else
		{
			std::cout<< "Introduce tu Nick:" <<std::endl;
			std::string name;
			std::cin >> name;
			sf::Packet packNombre;
			packNombre << name;
			socket.send(packNombre);
			sf::Packet packId;
			socket.receive(packId);
			packId >> id;
			std::cout << "Se ha establecido conexion\n";
			std::cout << "Tu id de jugador es: " << id << std::endl;
		}
		std::string str = "hola";
	
		do
		{
			socket.receive(packetMano);
			packetMano >> size;
			
			std::cout << size << std::endl;
			for (int i = 0; i < size; i++)
			{
				packetMano >> cartaRepartida;
				
				switch (cartaRepartida)
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

		
			socket.receive(packHabitacion);		
			packHabitacion >> numPlayers;

			int hab=0;
			for (int i = 0; i < numPlayers; ++i)
			{
				PlayerInfo player;		
				packHabitacion >> hab;
				switch (hab)
				{
				case 1:
					player.habitacion = BILLAR;
					break;
				case 2:
					player.habitacion = BIBLIOTECA;
					break;
				case 3:
					player.habitacion = COCINA;
					break;
				case 4:
					player.habitacion = BAILE;
					break;
				case 5:
					player.habitacion = INVERNADERO;
					break;
				case 6:
					player.habitacion = COMEDOR;
					break;
				case 7:
					player.habitacion = VESTIBULO;
					break;
				case 8:
					player.habitacion = SALON;
					break;
				case 9:
					player.habitacion = ESTUDIO;
					break;		
				}		
				packHabitacion >> player.id;
				players.push_back(player);
			}
			for (int i = 0; i < numPlayers; ++i)
			{
				std::cout << "El jugador " << players[i].id << " comienza en la habitacion " << players[i].habitacion << std::endl;
			}

			sf::Packet dadosPack;
			bool pista = false;
			int dados = 0;
			socket.receive(dadosPack);
			dadosPack >> dados >> pista;
			std::cout << "Has sacado un " << dados;

			if (!pista)
			{
				std::cout << " y no tienes pista." << std::endl;
			}
			
			else
			{
				sf::Packet pistaPack;
				int pista = 0;
				std::cout << " tienes pista." << std::endl;
				socket.receive(pistaPack);
				pistaPack >> pista;
				switch (pista)
				{
				case 0:
					std::cout << "ARMA";
					break;
				case 1:
					std::cout << "SALA";
					break;
				case 2:
					std::cout << "PERSONAJE";
					break;
				}
			}
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
	
	return 0;
}