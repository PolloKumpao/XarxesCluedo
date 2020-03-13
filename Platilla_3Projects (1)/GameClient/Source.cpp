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
		std::vector<int> mano;
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
				
				std::cout << prueba << std::endl;
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