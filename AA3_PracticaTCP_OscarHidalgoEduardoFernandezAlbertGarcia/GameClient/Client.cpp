#pragma once
#include <PlayerInfo.h>
#include <SFML\Network.hpp>
#include<thread>
#include <iostream>
#include <string>
#include <fcntl.h>
#include "Graphics.h"

sf::Packet comando;
int comandClient = 0;
int comandServer = 0;

sf::TcpSocket socket;
std::string prueba = "Prueba conexion";
sf::Packet pack;

PlayerInfo player;
PlayerInfo playerInfo;
Graphics g;

std::list<carta> baraja;

struct playerInfoP2P
{
	std::string name = "";
	sf::IpAddress ip;
	unsigned short port;
	sf::TcpSocket* sock;

	playerInfoP2P(std::string _name,  sf::IpAddress _ip, unsigned short _port) {
		name = _name;
		ip = _ip;
		port = _port;
	};
};

std::list<sf::TcpSocket*>::iterator jugadorActual;
std::list <playerInfoP2P> playersP2P;
std::list <sf::TcpSocket*> peers;
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
int n = 0;
int tiradaDadosP2P;
estados estadoPlayer = WAIT;
sf::Event event;
bool end_game = false;



enum HEAD {
	START, LANZADADOS, ELEGIRPISTA, REVELARPISTA, MOVIMIENTO, NUEVAPOSICION, DEDUCCION, ENVIOSUPOSICION,
	DESMENTIRCS, DESMENTIRSC, NADIE, DESMENTIDO, DESMENTIDOGENERAL, RESOLVERCS, RESOLVERSC, RESOLUCIONCORRECTA, ENDTURNO, RESOLUCIONINCORRECTA, FINPARTIDA, CAMBIOTURNO
};

HEAD c;



void inicioPartida()
{	
	sf::Packet connectionPacket;
	int connectionType;
	socket.receive(connectionPacket);
	connectionPacket >> connectionType;	

	if (status != sf::Socket::Done)
	{
		std::cout << "Error al establecer conexion\n";
		exit(0);
	}
	else
	{
		if (connectionType == 0)
		{
			std::cout << "Introduce tu Nick:" << std::endl;
			//cambios por aqui
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
			g.id = id;
		}
		else if (connectionType == 1)
		{
			std::cout << "Introduce tu Nick:" << std::endl;
			std::string name;
			std::cin >> name;
			sf::Packet packNombre;
			packNombre << name;
			socket.send(packNombre);
		}
	}
	std::string str = "hola";

	if (connectionType == 0)
	{
		std::cout << "Conexion en modo Client/Server. " << std::endl;

		do
		{
			socket.receive(packetMano);
			packetMano >> size;

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
					mano.push_back((carta(ARMA, "Candelabro", 7)));
					break;
				case 8:
					mano.push_back((carta(ARMA, "Cuerda", 8)));
					break;
				case 9:
					mano.push_back((carta(ARMA, "Puñal", 9)));
					break;
				case 10:
					mano.push_back((carta(ARMA, "Pistola", 10)));
					break;
				case 11:
					mano.push_back((carta(ARMA, "Tuberia de Plomo", 11)));
					break;
				case 12:
					mano.push_back((carta(ARMA, "Herramienta", 12)));
					break;
				case 13:
					mano.push_back((carta(SALA, "Biblioteca", 13)));
					break;
				case 14:
					mano.push_back((carta(SALA, "Cocina", 14)));
					break;
				case 15:
					mano.push_back((carta(SALA, "Billar", 15)));
					break;
				case 16:
					mano.push_back((carta(SALA, "Baile", 16)));
					break;
				case 17:
					mano.push_back((carta(SALA, "Invernadero", 17)));
					break;
				case 18:
					mano.push_back((carta(SALA, "Comedor", 18)));
					break;
				case 19:
					mano.push_back((carta(SALA, "Vestibulo", 19)));
					break;
				case 20:
					mano.push_back((carta(SALA, "Salon", 20)));
					break;
				case 21:
					mano.push_back((carta(SALA, "Estudio", 21)));
					break;
				default:
					break;
				}
			}

			std::cout << std::endl;
			std::cout << "Tus cartas son las siguientes: " << std::endl;
			for (int i = 0; i < mano.size(); i++)
			{
				std::cout << "-" << mano[i].nombre << std::endl;
			}


			socket.receive(packHabitacion);
			packHabitacion >> numPlayers;

			int hab = 0;
			for (int i = 0; i < numPlayers; ++i)
			{

				packHabitacion >> hab;
				switch (hab)
				{
				case 1:
					player.habitacion = BILLAR;
					player.x = 14;
					player.y = 5;
					break;
				case 2:
					player.habitacion = BIBLIOTECA;
					player.x = 24;
					player.y = 5;
					break;
				case 3:
					player.habitacion = COCINA;
					player.x = 5;
					player.y = 25;
					break;
				case 4:
					player.habitacion = BAILE;
					player.x = 4;
					player.y = 14;
					break;
				case 5:
					player.habitacion = INVERNADERO;
					player.x = 4;
					player.y = 5;
					break;
				case 6:
					player.habitacion = COMEDOR;
					player.x = 20;
					player.y = 25;
					break;
				case 7:
					player.habitacion = VESTIBULO;
					player.x = 35;
					player.y = 10;
					break;
				case 8:
					player.habitacion = SALON;
					player.x = 35;
					player.y = 26;
					break;
				case 9:
					player.habitacion = ESTUDIO;
					player.x = 36;
					player.y = 5;
					break;
				}
				g.playerX = player.x;
				g.playerY = player.y;

				packHabitacion >> player.id;
				players.push_back(player);
				g.ListaJugadores.push_back(player);
			}
			/*for (int i = 0; i < numPlayers; ++i)
			{
				std::cout << "El jugador " << players[i].id << " comienza en la habitacion " << players[i].habitacion << std::endl;
			}*/
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
	

	//P2P connection
	if (connectionType == 1)
	{
		std::cout << "Conexion en modo P2P. " << std::endl;
		sf::IpAddress ip = "0.0.0.0";
		unsigned short port = 0;
		int playersSize = 0;

		sf::Packet pack;
		socket.receive(pack);
		//socket.disconnect();
		pack >> playersSize;
		std::cout << "Hay tantos jugadores : " << playersSize << std::endl;
		std::string ipS = "";
		for (int i = 0; i < playersSize; ++i)
		{
			pack >> ipS >> port;
			std::cout << ipS << port << std::endl;
			sf::TcpSocket *sock = new sf::TcpSocket;
			sock->connect(ipS, port);
			peers.push_back(sock);
		}

		if (playersSize < 3)
		{
			std::cout << "Esperando al resto de jugadores ... " << std::endl;
			sf::TcpListener listener;
			listener.listen(50000 + playersSize);


			for (int i = playersSize; i < 3; ++i)
			{
				std::cout << playersSize << std::endl;
				sf::TcpSocket* sock = new sf::TcpSocket;
				//listener.accept(*sock);
				std::cout << "LISTENEADO" << std::endl;
			}
			listener.close();
		}
	
		sf::Packet packInfo;
		for (int i = 0; i < 3; ++i)
		{
			std::cout << "PASADA" << std::endl;
			std::string name = "";
			sf::IpAddress ip="0.0.0.0";
			unsigned short port=0;
			sf::TcpSocket* sock= new sf::TcpSocket();
			socket.receive(packInfo);
			packInfo >> name >> ip.toString() >> port;
			sock->connect(ip, port);	
			playerInfoP2P p(name, ip, port);
			p.sock = sock;
			playersP2P.push_back(p);
		}
		std::cout << "EMPIEZA LA PARTIDA" << std::endl;
		while (1)
		{

		}
	}
}


void crearBarajaP2P()
{
	//6 personajes
	baraja.push_back(carta(PERSONAJE, "Amapola", 1)); //1
	baraja.push_back(carta(PERSONAJE, "Rubio", 2)); //2
	baraja.push_back(carta(PERSONAJE, "Orquidea", 3));//3
	baraja.push_back(carta(PERSONAJE, "Celeste", 4));//4
	baraja.push_back(carta(PERSONAJE, "Prado", 5));//5
	baraja.push_back(carta(PERSONAJE, "Mora", 6));//6

	//6 armas
	baraja.push_back(carta(ARMA, "Candelabro", 7));//7
	baraja.push_back(carta(ARMA, "Cuerda", 8));//8
	baraja.push_back(carta(ARMA, "Punal", 9));//9
	baraja.push_back(carta(ARMA, "Pistola", 10));//10
	baraja.push_back(carta(ARMA, "Tuberia", 11));//11
	baraja.push_back(carta(ARMA, "Herramienta", 12));//12

	//9 habitaciones
	baraja.push_back(carta(SALA, "Biblioteca", 13));//13
	baraja.push_back(carta(SALA, "Cocina", 14));//14
	baraja.push_back(carta(SALA, "Billar", 15));//15
	baraja.push_back(carta(SALA, "Baile", 16));//16
	baraja.push_back(carta(SALA, "Invernadero", 17));//17
	baraja.push_back(carta(SALA, "Comedor", 18));//18
	baraja.push_back(carta(SALA, "Vestibulo", 19));//19
	baraja.push_back(carta(SALA, "Salon", 20));//20
	baraja.push_back(carta(SALA, "Estudio", 21));//21	
}

void repartirCartasP2P()
{
	/*
	int r;
	for (; baraja.size() != 0;)
	{
		for (int i = 0; 3 > i; i++)
		{
			std::list<carta>::iterator it = baraja.begin();

			if (baraja.size() > 0)
			{
				r = rand() % baraja.size();
				std::advance(it, r);
				listaPlayers[i].mano.push_back(*it);
				baraja.erase(it);

			}	

		}
	}*/
}

bool tirarDados()
{
	int dado1 = rand() % 6 + 1;
	int dado2 = rand() % 6 + 1;

	tiradaDadosP2P = dado1 + dado2;

	if (dado1 == 1 || dado2 == 1)
	{
		return true;
	}
	else
		return false;
}
std::string pistaP2P(int tipoPista)
{
	std::string pistaElegida;
	switch (tipoPista)
	{
	case 0:
		do
		{
			std::cout << "Has sacado una pista de arma." << std::endl;
			std::cout << "Elige entre Candelabro | Cuerda | Punal | Pistola | Tuberia | Herramienta. " << std::endl;
			std::cout << "Introduce el nombre correcto" << std::endl;
			std::cin >> pistaElegida;
		} while (pistaElegida != "Candelabro" && pistaElegida != "Cuerda" && pistaElegida != "Punal" && pistaElegida != "Pistola" && pistaElegida != "Tuberia" && pistaElegida != "Herramienta");
		break;

	case 1:
		do
		{
			std::cout << "Has sacado una pista de sala." << std::endl;
			std::cout << "Elige entre Biblioteca | Invernadero | Billar | Estudio | Baile | Vestibulo | Cocina | Comedor | Salon. " << std::endl;
			std::cout << "Introduce el nombre correcto" << std::endl;
			std::cin >> pistaElegida;
		} while (pistaElegida != "Biblioteca" && pistaElegida != "Invernadero" && pistaElegida != "Billar" && pistaElegida != "Estudio" && pistaElegida != "Baile" && pistaElegida != "Vestibulo" && pistaElegida != "Cocina"&& pistaElegida != "Comedor" && pistaElegida != "Salon");
		break;

	case 2:
		do
		{
			std::cout << "Has sacado una pista de personaje." << std::endl;
			std::cout << " Elige entre Amapola | Rubio | Orquidea | Celeste | Prado | Mora. " << std::endl;
			std::cout << "Introduce el nombre correcto" << std::endl;
			std::cin >> pistaElegida;
		} while (pistaElegida != "Amapola" && pistaElegida != "Rubio" && pistaElegida != "Orquidea" &&  pistaElegida != "Celeste" && pistaElegida != "Prado" && pistaElegida != "Mora");
		break;
	}
	return pistaElegida;
}
void partidaP2P()
{
	std::list <sf::TcpSocket*>::iterator j = peers.begin();
	std::string pista;
	jugadorActual = j;
	int counter = 0;

	while (1)
	{
		if (tirarDados())
		{
			int r = rand() % 2;
			pista = pistaP2P(r);
		}

		else if (!tirarDados())
		{
			//no hay pista
		}

	}
}





void turno()
{
	std::cout << std::endl;
	std::cout << "   ****INICIO TURNO****" << std::endl;
	std::cout << "Tiras los dados..." << std::endl;
	comando >> dados >> pista >> tipoPista;
	g.movements = dados;
	std::cout << "Has sacado un " << dados;
	std::string pistaElegir;

	if (!pista)
	{
		std::cout << " y no tienes pista." << std::endl;
		

	}else
	{
		std::cout << " tienes pista de " << std::endl;

		
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
	std::cout << "Muevete con las flechas. Confirma tu posicion final con 'barra espaciadora' o vuelve a elegir los movimientos con la tecla 'Retroceso'. " << std::endl;
	comando.clear();

	
		comando << HEAD::ELEGIRPISTA << pista <<pistaElegir;
		comando << pistaElegir;

		socket.send(comando);
	
	
	comando.clear();




	//do {
	//	//MOVIMIENTO
	//	//send posicion 

	//	if (event.type == sf::Event::KeyPressed)
	//		if (event.key.code == sf::Keyboard::K)
	//		{
	//			estadoPlayer = WAIT;
	//		}
	//	sf::Packet packPos;
	//	packPos << g.yo->x << g.yo->y;
	//	socket.send(packPos);
	//	estadoPlayer = WAIT;
	//	//ESTADO = WAIT
	//} while (estadoPlayer == TURNO);
}

std::string habitacion()
{
	if (g.yo->x < 8 && g.yo->y < 10)
		return "Invernadero";
	else if (g.yo->x > 11 && g.yo->x < 18 && g.yo->y < 10)
		return "Billar";
	else if (g.yo->x > 21 && g.yo->x < 28 && g.yo->y < 10)
		return "Biblioteca";
	else if (g.yo->x > 31 && g.yo->y < 10)
		return "Estudio";
	else if (g.yo->x < 8 && g.yo->y>11 && g.yo->y < 18)
		return "Baile";
	else if (g.yo->x > 29 && g.yo->y > 11 && g.yo->y < 20)
		return "Vestibulo";
	else if (g.yo->x < 10 && g.yo->y >19)
		return "Cocina";
	else if (g.yo->x > 12 && g.yo->x < 26 && g.yo->y >19)
		return "Comedor";
	else if (g.yo->x > 29 && g.yo->y > 21)
		return "Salon";
	else
		return "NONE";
}


void revelarPista()
{
	std::string pistaRevelada;
	comando >> pistaRevelada;
	std::cout << pistaRevelada;
	comando.clear();
}

void enviarMov()
{
	comando.clear();
	while (event.key.code != sf::Keyboard::Enter)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			break;
	}
	while (event.key.code != sf::Keyboard::Enter)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			break;
	}

	comando << HEAD::MOVIMIENTO << g.yo->x << g.yo->y;
	socket.send(comando);
	g.movements = 0;
	comando.clear();

}
void resolver()
{
	comando.clear();
	std::string arma, sala, personaje;


		

			std::cout << std::endl;
			std::cout << "Resuelve: " << std::endl;
			
			do
			{
				std::cout << "Sala. Elige entre Biblioteca | Invernadero | Billar | Estudio | Baile | Vestibulo | Cocina | Comedor | Salon " << sala << std::endl;
				std::cout << "Introduce el nombre correcto" << std::endl;
				std::cin >> sala;

			} while (sala != "Biblioteca" && sala != "Invernadero" && sala != "Billar" && sala != "Estudio" && sala != "Baile" && sala != "Vestibulo" && sala != "Cocina"&& sala != "Comedor" && sala != "Salon");

			
			do
			{
				std::cout << "ARMA. Elige entre Candelabro | Cuerda | Punal | Pistola | Tuberia | Herramienta." << std::endl;
				std::cout << "Introduce el nombre correcto" << std::endl;
				std::cin >> arma;

			} while (arma != "Candelabro" && arma != "Cuerda" && arma != "Punal" && arma != "Pistola" && arma != "Tuberia" && arma != "Herramienta");


			
			while (personaje != "Amapola" && personaje != "Rubio" && personaje != "Orquidea" &&  personaje != "Celeste" && personaje != "Prado" && personaje != "Mora")
			{
				std::cout << "PERSONAJE. Elige entre Amapola | Rubio | Orquidea | Celeste | Prado | Mora. " << std::endl;
				std::cout << "Introduce el nombre correcto" << std::endl;
				std::cin >> personaje;
			}

			comando << HEAD::RESOLVERCS << arma << sala << personaje;
			socket.send(comando);
			comando.clear();
}
void endturno()
{
	std::cout << "***TURNO FINALIZADO***" << std::endl;
	comando.clear();
	comando << HEAD::ENDTURNO;
	socket.send(comando);
}

void deduccion()
{	
	comando.clear();
	std::string arma, sala, personaje,opcion;
	sala = habitacion();
	if (sala == "NONE")
	{
		std::cout << "Necesitas estar en una sala para hacer una deduccion" << std::endl;
		endturno();
	}
	else
	{

	std::cout << "Si quieres Resolver escribe RESOLVER || Si quieres hacer una deduccion Escribe DEDUCCION :" << std::endl;
	std::cin >> opcion;
	if (opcion == "DEDUCCION")
	{

		

			std::cout << "Haz tu deduccion: " << std::endl;
			std::cout << "Sala: " << sala << std::endl;
			std::cout << "ARMA. Elige entre Candelabro | Cuerda | Punal | Pistola | Tuberia | Herramienta." << std::endl;
			do
			{
				std::cout << "Introduce el nombre correcto" << std::endl;
				std::cin >> arma;

			} while (arma != "Candelabro" && arma != "Cuerda" && arma != "Punal" && arma != "Pistola" && arma != "Tuberia" && arma != "Herramienta");


			std::cout << "PERSONAJE. Elige entre Amapola | Rubio | Orquidea | Celeste | Prado | Mora. " << std::endl;
			while (personaje != "Amapola" && personaje != "Rubio" && personaje != "Orquidea" &&  personaje != "Celeste" && personaje != "Prado" && personaje != "Mora")
			{
				std::cout << "Introduce el nombre correcto" << std::endl;
				std::cin >> personaje;
			}

			comando << HEAD::DEDUCCION << arma << sala << personaje;
			socket.send(comando);
			comando.clear();

		
	}
	else if (opcion == "RESOLVER")
	{
		resolver();
	}
	else
	{
		deduccion();
	}
	}
}
void actualizarPos()
{

	float x, y;
	
	comando >> n >> x >> y;
	players[n].x = x;
	players[n].y = y;
	g.ListaJugadores[n].x = x;
	g.ListaJugadores[n].y = y;

	comando.clear();
}

void printDeduccion()
{
	std::string deduccionPlayer;
	comando >> deduccionPlayer;
	std::cout << deduccionPlayer << std::endl;
	comando.clear();
}

void opcionesDesmentir()
{
	std::string opcion1, opcion2, opcion3;
	std::string eleccion;
	comando >> opcion1 >> opcion2 >> opcion3;
	comando.clear();
	std::cout << "Escoge la carta que quieras mostrar: " << opcion1 << " | " << opcion2 << " | " << opcion3 << std::endl;
	do
	{
		std::cout << "Introduce una de las opciones" << std::endl;
		std::cin >> eleccion;
	} while (eleccion != opcion1 && eleccion != opcion2 && eleccion != opcion3);
	comando.clear();

	comando << HEAD::DESMENTIDO << eleccion;
	socket.send(comando);
	//std::cout << "Desmentido enviado" << std::endl;
	comando.clear();
}
void nadie()
{
	std::string mensaje;
	comando >> mensaje;
	std::cout << mensaje << std::endl;
	comando.clear();
}
void printCarta()
{
	std::string carta;
	comando >> carta;
	std::cout << "Se muestra la carta: " << carta;
	comando.clear();
}
void finpartida()
{
	std::string ganador;
	comando >> ganador;
	std::cout << "                    ******La partida ha acabado******" << std::endl;
	std::cout << "Ha ganado el jugador con el nick: " << ganador << std::endl;

}
void recibirComando()
{
	while (!end_game)
	{
	/*	std::cout << "esperando packet" << std::endl;*/
		socket.receive(comando);
		
		comando >> comandClient;
		c=(HEAD)comandClient;
		//std::cout << c << std::endl;
		switch (c)
		{
		case HEAD::LANZADADOS: //Recibes dados
		{
			//std::cout << "Recibo LANZADADOS" << std::endl;
			turno();
			break;
		}

		case HEAD::REVELARPISTA: //Revelar pista
		{
			//std::cout << "Recibo REVELARPISTA" << std::endl;
			revelarPista();
			enviarMov();
			break;
		}

		case HEAD::NUEVAPOSICION: //Actualizar pos
		{
			//std::cout << "Recibo NUEVAPOSICION" << std::endl;
			actualizarPos();
			break;
		}

		case HEAD::DEDUCCION: //Deduccion
		{
			//std::cout << "Recibo DEDUCCION" << std::endl;
			deduccion();
			
			break;
		}

		case HEAD::ENVIOSUPOSICION: //Printar deduccion
		{
			//std::cout << "Recibo ENVIOSUPOSICION" << std::endl;
			printDeduccion();
			break;
		}

		case HEAD::DESMENTIRSC: //Opciones a elegir
		{
			//std::cout << "Recibo DESMENTIRSC" << std::endl;
			opcionesDesmentir();

			break;
		}

		case HEAD::NADIE: //Nadie tiene ninguna
		{
			//std::cout << "Recibo NADIE" << std::endl;
			nadie();
			break;
		}

		case HEAD::DESMENTIDOGENERAL: //Printa la carta escogida por la pantalla de todos los jugadores
		{
			//std::cout << "Recibo DESMENTIDOGENERAL" << std::endl;
			printCarta();
			break;
		}
		case HEAD::RESOLVERSC: 
		{
			//std::cout << "Recibo RESOLVERSC" << std::endl;
			resolver();
			break;
		}
		case HEAD::RESOLUCIONINCORRECTA:
		{
			//std::cout << "No es correcto" << std::endl;
			break;
		}
		case HEAD::RESOLUCIONCORRECTA:
		{
			std::cout << "                        ******HAS GANADO******" << std::endl;
			finpartida();
			break;
		}
		case HEAD::FINPARTIDA:
		{
			finpartida();
			break;
		}case HEAD::CAMBIOTURNO:
		{
			std::string ij;
			comando >> ij;

			std::cout << "                        ******Turno de " << ij << "******" << std::endl;
			break;
		}
		}
	}

}





int main()
{
	inicioPartida();

	//recieve;
	std::thread recieve(recibirComando);

	g.DrawDungeon(socket);








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
/*#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include "Graphics.h"
#include <PlayerInfo.h>
#include <Utils.h>
#include <LobbyRoom.h>
#include <Messages.h>

using namespace sf;

const std::string SERVER_IP = "127.0.0.1";
const unsigned short SERVER_PORT = 50000;
const unsigned short SERVER_WAIT_TIME = 5;
const unsigned short MAX_PLAYERS = 3;

std::vector<std::string> aMensajes;

struct Player {
	TcpSocket* tcpSocket;
	short order;
	PlayerInfo info;

	Player(TcpSocket* _tcpSocket, std::string _nick) :tcpSocket(_tcpSocket), info(_nick) {}
};

void print(std::string text) {
	std::cout << text << std::endl;
}

void PeerListener(Player* player, LobbyRoom& lobbyRoom) {
	
	while (true) {
		sf::Packet packet;
		player->tcpSocket->receive(packet);		
		std::string mensaje;
		packet >> mensaje;
		aMensajes.push_back(player->info.GetName() + mensaje);

		if (aMensajes.size() > 25)
		{
			aMensajes.erase(aMensajes.begin(), aMensajes.begin() + 1);
		}
		lobbyRoom.NextTurn();
	}
}

void ReceivesManager(PlayerInfo& _playerInfo, std::vector<Player>& players, int peerID, LobbyRoom& lobbyRoom, unsigned int random) {
	bool connectedToPeer = true;
	while (connectedToPeer) {
		sf::Packet receivePacket;
		sf::Socket::Status peerStatus;


		peerStatus = players[peerID].tcpSocket->receive(receivePacket);

		if (peerStatus == sf::Socket::Status::Disconnected) {
			Utils::print("Server has been disconected!");
			connectedToPeer = false;
		}
		else if (peerStatus != sf::Socket::Status::Done) {
			Utils::print("Something went wrong trying to receive a packet from server");
			continue;
		}

		std::string headder;

		receivePacket >> headder;

		switch (Messages::IsMessage(headder)) {
		case Messages::Msg::MSG: {
			std::string nickName;
			std::string message;

			receivePacket >> nickName >> message;
			aMensajes.push_back(nickName + "> " + message);

			if (aMensajes.size() > 25)
				aMensajes.erase(aMensajes.begin(), aMensajes.begin() + 1);

			break;
		}
		case Messages::Msg::DADO: {
			int status;
			receivePacket >> status;

			if(status !=0)
				lobbyRoom.NextTurn();

			players[peerID].info.SetDieThrow(lobbyRoom.RollDie());
			std::cout << "Dado de " << players[peerID].info.GetName() << " : " << players[peerID].info.GetDieThrow() << std::endl;
			break;
			}

		case Messages::Msg::PISTA: {
			std::string name;
			int idPlayer;
			receivePacket >> name;
			Card::CardName cardName = _playerInfo.StringToCardName(name);
			lobbyRoom.EraseClueCard(cardName);
			receivePacket >> idPlayer;

			if(idPlayer != -1)
				std::cout << "La carta " << name << " la tiene: " << players[idPlayer].info.GetName() << std::endl;
			else
				std::cout << "La carta que se ha descubierto es: " << name << ". Esta dentro del sobre! " << std::endl;

			lobbyRoom.NextTurn();

			break;
			}
								 
		}
	}
}

std::vector<std::string*> GetParameters(std::string str)
{
	std::vector<std::string*> parameters;
	std::string word = "";

	for (auto x : str)
	{
		if (x == ' ')
		{
			parameters.push_back(new std::string(word));
			word = "";
		}
		else
		{
			word = word + x;
		}
	}

	parameters.push_back(new std::string(word));
	return parameters;
}

void GetChatCommand(std::vector<Player>& players, PlayerInfo& playerInfo, std::string _message, short myPlayerOrder, LobbyRoom& lobbyRoom, unsigned int random) {
	sf::Packet packetCommand;
	std::vector<std::string*> parameters = GetParameters(_message);
	switch (Messages::IsChatMessage(*parameters[0])) {
			
		case Messages::Msg::DADO: {
			packetCommand << "DADO";
			
			players[myPlayerOrder].info.SetDieThrow(LobbyRoom::RollDie());
			std::cout << "Te ha tocado un " << players[myPlayerOrder].info.GetDieThrow() << std::endl;

			if (players[myPlayerOrder].info.GetDieThrow() == 1)
			{
				short type = rand() % 3;
					std::cout <<type << std::endl;

				if (type == 0)
				{
					std::cout << "Pista! Escoge una carta del tipo ARMA con el comando \\clue y la carta deseada: " << std::endl;
					playerInfo.SetClueCardType(Card::CardType::TOOL);
				}
				else if (type == 1)
				{
					std::cout << "Pista! Escoge una carta del tipo PERSONAJE con el comando \\clue y la carta deseada: " << std::endl;
					playerInfo.SetClueCardType(Card::CardType::CHARACTER);
				}
				else if (type == 2)
				{
					std::cout << "Pista! Escoge una carta del tipo LUGAR con el comando \\clue y la carta deseada: " << std::endl;
					playerInfo.SetClueCardType(Card::CardType::ROOM);
				}
				packetCommand << 0;
			}
			else
			{
				lobbyRoom.NextTurn();
				packetCommand << 1;
			}

			for (int i = 0; i < players.size(); i++)
			{
				if (i != myPlayerOrder)
				{
					if (players[i].tcpSocket->send(packetCommand) == sf::Socket::Done) {
						Utils::print("se ha enviado el dado");

					}
				}
			}

			break;
		}	
		case Messages::Msg::PISTA: {
			Card::CardName name = playerInfo.StringToCardName(*parameters[1]);
			std::vector<Card> cards = lobbyRoom.GetClueCards();
			std::vector<Card> playerCards;
			int idPlayer;
			bool found = false;
			for (int i = 0; i < cards.size(); i++)
			{
				if (cards[i].GetName() == name)
				{
					if (cards[i].GetType() == playerInfo.GetClueCardType())
					{
						
						for (int j = 0; j < players.size(); j++)
						{
							playerCards = players[j].info.GetCards();
							for (int k = 0; k < playerCards.size(); k++)
							{
								if (playerCards[k].GetName() == name) {
									std::cout << "La carta " << *parameters[1] << " la tiene: " << players[j].info.GetName() << std::endl;
									found = true;
									idPlayer = j; 
									lobbyRoom.EraseClueCard(name);
									break;
								}
							}
						}
						if (!found)
						{
							std::cout << "La carta " << *parameters[1] << " esta dentro del sobre! " << std::endl;
							lobbyRoom.EraseClueCard(name);
							idPlayer = -1;
							found = true;
						}


						packetCommand << "PISTA";
						packetCommand << *parameters[1];
						packetCommand << idPlayer;

						lobbyRoom.NextTurn();

						for (int j = 0; j < players.size(); j++)
						{
							if (j != myPlayerOrder)
							{
								if (players[j].tcpSocket->send(packetCommand) == sf::Socket::Done) {
									Utils::print("se ha enviado la pista");

								}
							}
						}

					}
					else
						std::cout << "Esta carta no forma parte del tipo que te he pedido!" << std::endl;
				}
			}
			if (!found)
				Utils::print("¡Esta carta no existe o ya se ha descubierto con una pista!");
		}
	}
}


int main()
{
	Vector2i screenDimensions(800, 600);
	Font font;
	RenderWindow window;
	TcpListener listener;
	TcpSocket socket;
	int playersCount;
	unsigned int random;
	std::vector<Player> peers;
	unsigned short portServer;
	Packet pack;
	Socket::Status serverStatus;
	sf::String mensaje;
	std::string nickname;
	PlayerInfo playerInfo;
	short order = 0;
	short myPlayerOrder;
	TcpSocket* mySocket = new TcpSocket();
	

#pragma region CONNECTION TO SERVER
	Utils::print("Connecting...");
	serverStatus = socket.connect(SERVER_IP, SERVER_PORT, sf::seconds(SERVER_WAIT_TIME));

	if (serverStatus != Socket::Status::Done) {
		print("There was a problem trying to connect to the server");
		return 0;
	}
	Utils::print("Conected!");

	std::cout << "Type your nickname:" << std::endl;
	std::cin >> nickname;

	playerInfo.SetName(nickname);

	pack << nickname;
	socket.send(pack);

	portServer = socket.getLocalPort();

	serverStatus = socket.receive(pack);
	if (serverStatus != Socket::Status::Done) {
		print("Esta reventando en el receive");
	}

	socket.disconnect();

	pack >> playersCount;

	pack >> random;

	srand(random);

	for (short i = 0; i < playersCount; i++)
	{
		std::string ip_peer;
		short port_peer;
		std::string nick_peer;
		pack >> ip_peer >> port_peer >> nick_peer;
		TcpSocket* sockAux = new TcpSocket();
		sockAux->connect(ip_peer, port_peer);
		peers.push_back(Player(sockAux, nick_peer));
		peers[i].order = order;
		order++;
		Packet nickPack;
		nickPack << nickname;
		sockAux->send(nickPack);
	}

	peers.push_back(Player(mySocket, playerInfo.GetName()));
	myPlayerOrder = order;
	order++;

	print("Waiting for other players...");
	std::cout << MAX_PLAYERS - playersCount - 1 << std::endl;

	if (listener.listen(portServer) != Socket::Status::Done)
	{
		print("error at listener");
	}

	for (int i = 0; i < MAX_PLAYERS - playersCount - 1; i++)
	{
		TcpSocket* socketToAccept = new TcpSocket();
		listener.accept(*socketToAccept);
		std::string nickpeer;
		socketToAccept->receive(pack);
		pack >> nickpeer;
		print((nickpeer + "entrered"));
		peers.push_back(Player(socketToAccept, nickpeer));
		peers[i].order = order;
		order++;
	}

	listener.close();
#pragma endregion

	window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Chat " + nickname);
	if (!font.loadFromFile(FONT_PATH))
	{
		std::cout << "Can't load the font file" << std::endl;
	}

	mensaje = "";

	sf::Text chattingText(mensaje, font, 14);
	chattingText.setFillColor(sf::Color(0, 160, 0));
	chattingText.setStyle(sf::Text::Bold);

	sf::Text text(mensaje, font, 14);
	text.setFillColor(sf::Color(0, 160, 0));
	text.setStyle(sf::Text::Bold);
	text.setPosition(0, 560);

	sf::RectangleShape separator(sf::Vector2f(800, 5));
	separator.setFillColor(sf::Color(200, 200, 200, 255));
	separator.setPosition(0, 550);

	LobbyRoom lobbyRoom;

	for (int i = 0; i < peers.size(); i++) {
		if (peers[i].tcpSocket != mySocket)
		{
			Utils::print("Thread");
			std::thread thread(&ReceivesManager, std::ref(playerInfo), std::ref(peers), i, std::ref(lobbyRoom), random);
			thread.detach();
			Utils::print("detach");
		}
	}
	LobbyRoom lb("Room", "1234", MAX_PLAYERS);
	lobbyRoom = lb;
	
	for (short i = 0; i < peers.size(); i++)
	{
		lobbyRoom.AddPlayer(peers[i].tcpSocket, &peers[i].info);
		lobbyRoom.SetUniqueColor(&peers[i].info);
	}

	for (int i = 0; i < peers.size(); i++)
	{
		std::cout <<"ID COLOR: " <<peers[i].info.GetIdColor() << std::endl;
	}

	std::map<short, std::vector<Card>> cardsMap;

	cardsMap = lobbyRoom.SetPeersCards();

	std::cout << "CardsMap: " << cardsMap.size() << ", " << myPlayerOrder << std::endl;
	for (short i = 0; i < cardsMap.size(); i++)
	{
		if (i == myPlayerOrder)
		{
			peers[i].info.SetCards(cardsMap[i]);
			playerInfo.SetCards(cardsMap[i]);
		}
		else
			peers[i].info.SetCards(cardsMap[i]);
	}

	std::cout << "cartes repartides" << std::endl;
	
	std::vector<Card> cards = playerInfo.GetCards();
	Utils::print("Cards: " + std::to_string(cards.size()));

	for (int i = 0; i < cards.size(); i++) {
		Utils::print(cards[i].print());
	}
	
	while (window.isOpen())
	{
		sf::Event evento;
		while (window.pollEvent(evento))
		{
			switch (evento.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (evento.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				else if (evento.key.code == sf::Keyboard::Return && lobbyRoom.IsPlayerTurn(peers[myPlayerOrder].tcpSocket))
				{
					sf::Packet packet;
					std::string packetToSend = mensaje;
					if (mensaje[0] == '\\') {
						Utils::print("COMMAND");
						GetChatCommand(peers, playerInfo, mensaje, myPlayerOrder, lobbyRoom, random);
					}
					else {
						Utils::print("MEssage");
						packet << "MSG" << playerInfo.GetName() << packetToSend;
						for (int i = 0; i < peers.size(); i++) {
							if (peers[i].tcpSocket != mySocket)
								peers[i].tcpSocket->send(packet);
						}
						
					}					
					mensaje = "";
				}
				break;

			case sf::Event::TextEntered:
				if (evento.text.unicode >= 32 && evento.text.unicode <= 126)
					mensaje += (char)evento.text.unicode;
				else if (evento.text.unicode == 8 && mensaje.getSize() > 0)
					mensaje.erase(mensaje.getSize() - 1, mensaje.getSize());
				break;
			}
		}

		window.draw(separator);

		for (size_t i = 0; i < aMensajes.size(); i++)
		{
			std::string chatting = aMensajes[i];
			chattingText.setPosition(sf::Vector2f(0, 20 * i));
			chattingText.setString(chatting);
			window.draw(chattingText);
		}


		std::string mensaje_ = mensaje + "_";
		text.setString(mensaje_);
		window.draw(text);

		window.display();
		window.clear();
	}
	return 0;
}*/