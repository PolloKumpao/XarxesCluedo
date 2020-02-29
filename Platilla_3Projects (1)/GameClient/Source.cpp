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
	


	sf::Socket::Status status = socket.connect("localhost", 5000, sf::seconds(5.f));
	if (status != sf::Socket::Done)
	{
		std::cout << "No se ha podido conectar";
	}
	else {
		std::cout << "Conectado" << std::endl;
	}

	pack << prueba;
	socket.send(pack);

	while (1)
	{

	}
	g.DrawDungeon();
	return 0;
}