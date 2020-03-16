#pragma once
#include <PlayerInfo.h>
#include <SFML\Network.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <fcntl.h>
#include "Graphics.h"

sf::Packet comando;
int comandClient  = 0 ;
int comandServer = 0;

sf::TcpSocket socket;
std::string prueba = "Prueba conexion";
sf::Packet pack;


PlayerInfo playerInfo;
Graphics g;




sf::Socket::Status status = socket.connect("localhost", 50000, sf::milliseconds(15.f));
sf::Packet packetMano;
std::vector<carta> mano;
std::vector<PlayerInfo> players;
int cartaRepartida = 0;
int size = 0;
int habitacionInicial[3];
sf::Packet packHabitacion;
int numPlayers = 0;
int id = 0;
bool pista = false;
int dados = 0;
int tipoPista = 0;

estados estadoPlayer = WAIT;
sf::Event event;
bool end_game = false;
//enum comandos {
//	START, LANZADADOS, ELEGIRPISTA, REVELARPISTA, MOVIMIENTO, NUEVAPOSICION, DEDUCCION, ENVIOSUPOSICION,
//	DESMENTIRCS, DESMENTIRSC, DESMENTIDO, DESMENTIDOGENERAL, RESOLVERCS, RESOLVERSC, RESOLUCIONCORRECTA
//};


void recibirEnviarPista()
{

}

void inicioPartida()
{

	if (status != sf::Socket::Done)
	{
		std::cout << "Error al establecer conexion\n";
		exit(0);
	}
	else
	{
		std::cout << "Introduce tu Nick:" << std::endl;
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
				mano.push_back((carta(PERSONAJE, "Pu�al", 9)));
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

		int hab = 0;
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
		str = "Fin Inicio";
		/*std::getline(std::cin, str);
		sf::Packet packet;
		packet << str;
		status = socket.send(packet);
		if (status != sf::Socket::Done)
		{
		std::cout << "Error al enviar\n";
		}*/
		std::cout << std::endl;
	} while (str != "Fin Inicio");
}

void turno()
{

	comando >> dados >> pista >> tipoPista;

	std::cout << "Has sacado un " << dados;
	std::string pistaElegir;

	if (!pista)
	{
		std::cout << " y no tienes pista." << std::endl;
	}

	else
	{
		
		
			std::cout << " tienes pista de " << std::endl;
			
			tipoPista = 0;
			switch (tipoPista)
			{
			case 0:
				std::cout << "ARMA. Elige entre Candelabro | Cuerda | Punal | Pistola | Tuberia | Herramienta." << std::endl;
				while (pistaElegir != "Candelabro" && pistaElegir != "Cuerda" && pistaElegir != "Punal" && pistaElegir != "Pistola" && pistaElegir != "Tuberia" && pistaElegir != "Herramienta")
				{
					std::cout << "Introduce el nombre correcto del arma que elijas" << std::endl;
					std::cin >> pistaElegir;
				}
				break;

			case 1:
				std::cout << "SALA. Elige entre Biblioteca | Cocina | Billar | Baile | Invernadero | Comedor | Salon | Estudio." << std::endl;
				while (pistaElegir != "Biblioteca" && pistaElegir != "Cocina" && pistaElegir != "Billar" && pistaElegir != "Baile" && pistaElegir != "Invernadero" && pistaElegir != "Comedor" && pistaElegir != "Salon" && pistaElegir != "Estudio")
				{
					std::cout << "Introduce el nombre correcto de la sala que elijas" << std::endl;
					std::cin >> pistaElegir;
				}
				break;

			case 2:
				std::cout << "PERSONAJE. Elige entre Amapola | Rubio | Orquidea | Celeste | Prado | Mora. " << std::endl;
				while (pistaElegir != "Amapola" && pistaElegir != "Rubio" && pistaElegir != "Orquidea" &&  pistaElegir != "Celeste" && pistaElegir != "Prado" && pistaElegir != "Mora")
				{
					std::cout << "Introduce el nombre correcto del personaje que elijas" << std::endl;
					std::cin >> pistaElegir;
				}
				break;
			}
		}

		comando.clear();
		comandServer = 1;
		comando << comandServer << pistaElegir;    // comando Revelar Pista
		comando << pistaElegir;

		socket.send(comando);
		comando.clear();

		
	

		do {
			//MOVIMIENTO
			//send posicion 
			
			if(event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::K)
				{
					estadoPlayer = WAIT;
				}
			sf::Packet packPos;
			packPos << g.playerX << g.playerY;
			socket.send(packPos);
			estadoPlayer = WAIT;
			//ESTADO = WAIT
		} while (estadoPlayer == TURNO);
}


void revelarPista()
{
	std::string pistaRevelada;
	comando >> pistaRevelada;
	std::cout << pistaRevelada;
	comando.clear();
}

void recibirComando()
{
	
		socket.receive(comando);
		comando >> comandClient;
		switch (comandClient)
		{
		case 1: //Recibes dados
			turno();

			break;
		case 2: //Revelar pista
			revelarPista();


			break;
		}
	
}

void wait()
{
	recibirComando();
	


		/*sf::Packet pistaRevelar;
		socket.receive(pistaRevelar);
		std::string pistaRevelada;
		pistaRevelar >> pistaRevelada;
		std::cout << pistaRevelada;*/
	
}

int main()
{
	g.DrawDungeon();
	inicioPartida();
	while(!end_game)
	{
	 recibirComando();
	}
	
	/*wait();
	turno();*/

	
	//socket.disconnect();

	while (1)
	{

	}


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

