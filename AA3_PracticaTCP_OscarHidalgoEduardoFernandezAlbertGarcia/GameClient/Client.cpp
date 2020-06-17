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



std::list<sf::TcpSocket*>::iterator jugadorActual;
std::list <sf::TcpSocket*> peers;
sf::Socket::Status status = socket.connect("localhost", 50001, sf::milliseconds(15.f));
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
	//Client/server connection
	if (status != sf::Socket::Done)
	{
		std::cout << "Error al establecer conexion\n";
		exit(0);
	}
	else
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

		sf::TcpListener listener;
		listener.listen(50000 + playersSize);

		for (int i = size; i < 3; ++i)
		{
			sf::TcpSocket* sock = new sf::TcpSocket;
			listener.accept(*sock);
		}
		listener.close();
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
