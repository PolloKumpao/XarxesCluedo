#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <PlayerInfo.h>
#include <vector>
sf::TcpSocket incoming;
std::list<sf::TcpSocket*> jugadores;

//Funcion por la que el servidor recibe mensajes

enum HEAD {
	START, LANZADADOS, ELEGIRPISTA, REVELARPISTA, MOVIMIENTO, NUEVAPOSICION, DEDUCCION, ENVIOSUPOSICION,
	DESMENTIRCS, DESMENTIRSC, NADIE, DESMENTIDO, DESMENTIDOGENERAL, RESOLVERCS, RESOLVERSC, RESOLUCIONCORRECTA, ENDTURNO, RESOLUCIONINCORRECTA, FINPARTIDA, CAMBIOTURNO
};

struct playerInfoP2P
{
	std::string name = "";
	sf::IpAddress ip;
	unsigned short port;
	sf::TcpSocket* sock;

	playerInfoP2P(std::string _name, sf::IpAddress _ip, unsigned short _port, sf::TcpSocket* _sock) {
		name = _name;
		ip = _ip;
		port = _port;
		sock = _sock;
	};
};

HEAD c;
int dado1;
int dado2;
std::list<carta> baraja;
std::list<carta> crimen;
//std::list<PlayerInfo> listaPlayers;
std::vector<PlayerInfo> listaPlayers;
std::list<sf::TcpSocket*>::iterator jugadorActual;
std::list<sf::TcpSocket*>::iterator jugadorAux;

std::list <playerInfoP2P> playersP2P;

int id_jugadorActual;
sf::Packet comando;
int comandServer;
int comandClient;
bool end_turno = false;
bool p2pConexion;

int n = 0; // ID jugador en listaPlayer


//P2P
struct PeerAdress {
	sf::IpAddress ip;
	unsigned short port;

	PeerAdress(sf::IpAddress _ip, unsigned short _port) {
		ip = _ip;
		port = _port;
	};
};

void EnviarAll(sf::Packet p, sf::TcpSocket* id)
{

	for (std::list<sf::TcpSocket*>::iterator it = jugadores.begin(); jugadores.end() != it; it++)
	{
		if (id != (*it))
		{
			(*it)->send(p);
		}


	}

}
void crearBaraja()
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
void repartirCartas()
{
	int r;
	/*	for (int i = 0; jugadores.size() > i; i++)
		{
			listaPlayers.push_back(PlayerInfo());
		}*/

	for (; baraja.size() != 0;)
	{
		for (int i = 0; listaPlayers.size() > i; i++)
		{
			std::list<carta>::iterator it = baraja.begin();
			//std::list<PlayerInfo>::iterator itP = listaPlayers.begin();

			if (baraja.size() > 0)
			{
				r = rand() % baraja.size();
				std::advance(it, r);
				listaPlayers[i].mano.push_back(*it);
				baraja.erase(it);
			}

		}
	}


}
void enviarRecibirPista()
{

	std::string pista;
	bool b;
	//comando.clear();
	//Recibimos la eleccion de pista del cliente
	//(*jugadorActual)->receive(comando);
	comando >> b >> pista;
	if (b) {
		std::cout << "PISTA ELEGIDA: " << pista << std::endl;
		int i = 0;

		PlayerInfo playerPista;
		playerPista.name = "null";
		for (std::list<sf::TcpSocket*>::iterator it = jugadores.begin(); jugadores.end() != it; it++)
		{
			for (std::list<carta>::iterator ot = listaPlayers[i].mano.begin(); listaPlayers[i].mano.end() != ot; ot++)
			{
				if (pista == (*ot).nombre)
				{
					playerPista.name = listaPlayers[i].name;
					exit;
				}
			}

			i++;
		}
		comando.clear();
		std::string pistaFinal;
		if (playerPista.name == "null")
		{
			pistaFinal = "Ningun jugador tiene la carta " + pista;
			comando << HEAD::REVELARPISTA << pistaFinal;
		}
		else
		{
			pistaFinal = "El jugador con el Nick:  " + playerPista.name + " tiene la carta  " + pista;
			comando << HEAD::REVELARPISTA << pistaFinal;
		}

		(*jugadorActual)->send(comando);
	}
	else {
		comando.clear();
		std::string nula;
		nula = "" ;
	//	std::cout << "REVELARPISTA ENVIADO" << std::endl;
		comando << HEAD::REVELARPISTA << nula;
		(*jugadorActual)->send(comando);
		comando.clear();
	}
	//posible sendALL
	/*for (std::list<sf::TcpSocket*>::iterator it = jugadores.begin(); jugadores.end() != it; it++)
	{
		(*it)->send(comando);
	}*/
}

void tirarDados()
{
	
	end_turno = false;
	comando.clear();
	

	bool pista = false;
	int r = 0;
	dado1 = rand() % 6 + 1;
	dado2 = rand() % 6 + 1;

	if (dado1 == 1 || dado2 == 1)
	{
		pista = true;
		r = rand() % 2;
	}


	dado1 += dado2;

	comando << HEAD::LANZADADOS << dado1 << pista << r;

	(*jugadorActual)->send(comando);



	/*sf::Packet dadosPack;
	dadosPack.clear();

	dado1 = rand() % 6 + 1;
	dado2 = rand() % 6 + 1;

	std::cout << dado1 << "  "<< dado2 << std::endl;
	if (dado1 == 1 || dado2 == 1)
		pista = true;

	dado1 += dado2;
	dadosPack << dado1 << pista;
	(*jugadorActual)->send(dadosPack);

	if (pista)
		enviarRecibirPista();*/
}

void actualizarPos()
{
	
	float x;
	float y;
	comando >> x >> y;
	 

	comando.clear();

	comando << HEAD::NUEVAPOSICION << n << x << y;

	for (std::list<sf::TcpSocket*>::iterator it = jugadores.begin(); jugadores.end() != it; it++)
	{
		(*it)->send(comando);
	}
	comando.clear();
	comando << HEAD::DEDUCCION;
	(*jugadorActual)->send(comando);
	std::cout <<"Envio deduccion" << std::endl;
}



void Enviar()
{
	int i = 0;
	for (std::list<sf::TcpSocket*>::iterator it = jugadores.begin();jugadores.end() != it; it++)
	{
		sf::Packet packMano;
		std::list<carta>::iterator itM = listaPlayers[i].mano.begin();

		int manosize = listaPlayers[i].mano.size();
		packMano << manosize;
		//std::cout << listaPlayers[i].mano.size();
		for (int j = 0; listaPlayers[i].mano.size() > j; j++)
		{
			packMano << itM->numero;
			//std::cout << itM->numero << std::endl;
			itM++;
		}
		//packMano << 1;

		(*it)->send(packMano);
		i++;
	}

}

void asignarHabitacion()
{
	int counter1 = 0;
	int counter = 0;
	sf::Packet packHabitacion;

	int* r = NULL;
	r = new int[listaPlayers.size()];

	int tamaño = listaPlayers.size();
	//Se envia a clientes cuantos jugadores hay en la partida
	packHabitacion << tamaño;

	for (std::list<sf::TcpSocket*>::iterator it = jugadores.begin(); jugadores.end() != it; it++)
	{
		r[counter1] = rand() % 9 + 1;
		counter1++;
	}

	for (std::list<sf::TcpSocket*>::iterator it = jugadores.begin(); jugadores.end() != it; it++)
	{
		packHabitacion << r[counter] << listaPlayers[counter].id;
		counter++;
	}

	for (std::list<sf::TcpSocket*>::iterator it = jugadores.begin(); jugadores.end() != it; it++)
	{
		(*it)->send(packHabitacion);
	}
}

std::list<carta> crearCrimen(std::list<carta> &b)
{

	std::list<carta> c;
	std::list<carta>::iterator it = b.begin();

	int r;
	r = rand() % 6;
	std::advance(it, r);
	c.push_back(*it);
	std::cout << std::endl;
	std::cout << "El crimen que se tiene que acertar es el siguiente" << std::endl;
	std::cout <<"-"<< it->nombre << std::endl;
	b.erase(it);

	r = rand() % 5 + 6;
	it = b.begin();
	std::advance(it, r);
	c.push_back(*it);
	std::cout << "-" << it->nombre << std::endl;
	b.erase(it);


	r = rand() % 7 + 12;
	it = b.begin();
	std::advance(it, r);
	c.push_back(*it);
	std::cout << "-" << it->nombre << std::endl;
	std::cout <<std::endl;
	b.erase(it);
	return c;

}


void inicioPartida()
{
	crearBaraja();
	crimen = crearCrimen(baraja);
	repartirCartas();
	Enviar();
	asignarHabitacion();

}


void setUp(sf::TcpSocket* _client)
{
	PlayerInfo player;
	int _id;
	_id = listaPlayers.size();
	sf::Packet packNombre;
	std::string _name;
	_client->receive(packNombre);
	packNombre >> _name;
	player.name = _name;
	player.id = _id;
	sf::Packet packId;
	packId << _id;
	_client->send(packId);
	listaPlayers.push_back(player);



	std::cout << "LLega el cliente con nick: " << _name;
}

void ControlServidor()
{
	bool running = true;
	bool inicio = false;
	// Create a socket to listen to new connections

	// Create a list to store the future clients
	std::string connectionType;
	std::cout << "Escoja que tipo de conexion quiere para la partida: " << std::endl;
	std::cout << "Escriba 'clientserver' para cliente/servidor y 'p2p' para P2P. " << std::endl;
	std::cin >> connectionType;

	if (connectionType == "clientserver")
	{
		p2pConexion = false;
		std::cout << " Creando partida con conexion Client/Server. " << std::endl;
		std::cout << "Esperando jugadores... La partida empezara cuando hayan 3 jugadores:  " << std::endl;
		// Create a selector
		sf::TcpListener listener;
		sf::Socket::Status status = listener.listen(50001);
		if (status != sf::Socket::Done)
		{
			std::cout << "Error al abrir listener\n";
			exit(0);
		}
		sf::SocketSelector selector;
		int CSconnection = 0;
		// Add the listener to the selector
		selector.add(listener);
		// Endless loop that waits for new connections
		while (running)
		{
			// Make the selector wait for data on any socket
			if (selector.wait())
			{
				// Test the listener
				if (selector.isReady(listener))
				{
					// The listener is ready: there is a pending connection
					sf::TcpSocket* client = new sf::TcpSocket;
					if (listener.accept(*client) == sf::Socket::Done)
					{
						sf::Packet pack;
						pack << CSconnection;
						client->send(pack);
						pack.clear();

						// Add the new client to the clients list
						setUp(client);
						std::cout << " y con puerto: " << client->getRemotePort() << std::endl;
						jugadores.push_back(client);
						// Add the new client to the selector so that we will
						// be notified when he sends something
						selector.add(*client);

						

					}
					else
					{
						// Error, we won't get a new connection, delete the socket
						std::cout << "Error al recoger conexion nueva\n";
						delete client;
					}
				}
				else
				{
					// The listener socket is not ready, test all other sockets (the clients)
					for (std::list<sf::TcpSocket*>::iterator it = jugadores.begin(); it != jugadores.end(); ++it)
					{
						sf::TcpSocket& client = **it;
						if (selector.isReady(client))
						{
							// The client has sent some data, we can receive it
							sf::Packet packet;
							status = client.receive(packet);
							if (status == sf::Socket::Done)
							{
								std::string strRec;
								packet >> strRec;
								std::cout << "He recibido " << strRec << " del puerto " << client.getRemotePort() << std::endl;
							}
							else if (status == sf::Socket::Disconnected)
							{
								selector.remove(client);
								std::cout << "Elimino el socket que se ha desconectado\n";
							}
							else
							{
								std::cout << "Error al recibir de " << client.getRemotePort() << std::endl;
							}
						}
					}
				}
			}
			if (jugadores.size() == 3 || inicio)
			{
				inicioPartida();
				std::cout << "Empieza la partida: " << std::endl;
				inicio = true;
				running = false;
			}
		}
	}
	else if (connectionType == "p2p")
	{
		p2pConexion = true;
		std::cout << " Creando partida con conexion P2P. " << std::endl;
		std::cout << "Esperando jugadores... La partida empezara cuando hayan 3 jugadores:  " << std::endl;

		sf::Packet packName;
		std::string name = "";
		std::list <PeerAdress> aPeers;
		sf::TcpListener listener;
		int P2Pconnection = 1;

		for (int i = 0; i < 3; ++i)
		{
			
			listener.listen(50000);
			sf::TcpSocket *sock = new sf::TcpSocket;
			listener.accept(*sock);
			PeerAdress pa(sock->getRemoteAddress(), sock->getRemotePort());
			sf::Packet pack;
			pack << P2Pconnection;
			sock->send(pack);
			pack.clear();
			std::cout << "Ha llegado el cliente con IP: " << sock->getRemoteAddress() << "y con puerto: " << sock->getRemotePort() << std::endl;
			sock->receive(packName);
			packName >> name;
			std::cout << "Y con nombre " << name << std::endl;
			aPeers.push_back(pa);
			playerInfoP2P p(name, sock->getRemoteAddress(), sock->getRemotePort(), sock);
			playersP2P.push_back(p);
			//setUp(sock);
			int a = aPeers.size();
			pack << a;
			//sock->send(pack);
			std::cout << "Hay tantos jugadores : " << aPeers.size() << std::endl;
			int counter = 0;
			for (std::list<PeerAdress>::iterator ot = aPeers.begin(); counter != aPeers.size(); ++ot)
			{				
				std::cout << ot->ip.toString() << std::endl;
				pack << ot->ip.toString() << ot->port;
				counter++;
			}

			sock->send(pack);
			delete sock;
			pack.clear();
		}
		sf::Packet playersPack;
		for (std::list <playerInfoP2P>::iterator it = playersP2P.begin(); it != playersP2P.end(); it++)
		{
			playersPack<< it->name << it->ip.toString() << it->port;
			it->sock->send(playersPack);
			playersPack.clear();
		}
		listener.close();
	}
}

void desmentir()
{
	std::string arma, sala, personaje;
	int jugadorIzquierda = n + 1;
	comando >> arma >> sala >> personaje;

	std::string deduccion = "El jugador " + listaPlayers[n].name + " ha hecho la siguiente deduccion: " + personaje + " " + sala + " " + arma;
	comando.clear();
	
	comando << HEAD::ENVIOSUPOSICION << deduccion;
	for (std::list<sf::TcpSocket*>::iterator it = jugadores.begin(); jugadores.end() != it; it++)
	{
		(*it)->send(comando);
		//std::cout << "Envio deduccion" << std::endl;
	}
	comando.clear();
	
	comando << HEAD::DESMENTIRSC;
	int j = 0;
	bool tieneAlguna = false;

	for (std::list<sf::TcpSocket*>::iterator it = jugadores.begin(); jugadores.end() != it; it++)
	{
		if (jugadorActual != (it))
		{



			for (std::list<carta>::iterator ot = listaPlayers[j].mano.begin(); listaPlayers[j].mano.end() != ot; ot++)
			{
				if ((ot->nombre == arma))
				{
					comando << arma;
					tieneAlguna = true;
				}

				if ((ot->nombre == sala))
				{
					comando << sala;
					tieneAlguna = true;
				}
				if ((ot->nombre == personaje))
				{
					comando << personaje;
					tieneAlguna = true;
				}
			}

			if (tieneAlguna)
			{
				//std::cout << "Enviando desmentir" << std::endl;
				(*it)->send(comando);
				jugadorAux = jugadorActual;
				jugadorActual = it;
				comando.clear();
				break;
			}
		}
		j++;
	}
	if (!tieneAlguna)
	{
		std::string nadie = "Ningun jugador tiene ninguna de las 3 cartas. ";
		for (std::list<sf::TcpSocket*>::iterator it = jugadores.begin(); jugadores.end() != it; it++)
		{
			comando.clear();
			
			comando << HEAD::NADIE << nadie;
			(*it)->send(comando);

		}
		end_turno = true;
	}

}

void enseñarCarta()
{

	std::cout << "Enseña carta " << std::endl;
	jugadorActual = jugadorAux;
	std::string carta;
	comando >> carta;
	comando.clear();
	
	comando << HEAD::DESMENTIDOGENERAL << carta;
	for (std::list<sf::TcpSocket*>::iterator it = jugadores.begin(); jugadores.end() != it; it++)
	{
		(*it)->send(comando);
	}
	end_turno = true;
}

void comprobar() 
{
	std::string arma, sala, personaje;
	int tres = 0;
	comando >> arma >> sala >> personaje;
	for (std::list<carta>::iterator it = crimen.begin(); it != crimen.end(); it++)
	{
		if ((*it).nombre == arma || (*it).nombre == sala || (*it).nombre == personaje)
		{
			tres++;
		}
	}
	if (tres == 3)
	{
		std::string nombre;
		comando.clear();
		std::cout << " ¡HAS GANADO! " << std::endl;
		comando << HEAD::RESOLUCIONCORRECTA;
		for (std::vector<PlayerInfo>::iterator it = listaPlayers.begin(); it != listaPlayers.end(); it++)
		{
			if (id_jugadorActual == (*it).id)
			{
				nombre = (*it).name;
			}
		}
		comando << nombre;
		(*jugadorActual)->send(comando);
		comando.clear();
		comando << HEAD::FINPARTIDA<<nombre;
		EnviarAll(comando,(*jugadorActual));
	}
	else
	{
		std::cout << "No es correcto... " << std::endl;
		comando.clear();
		comando << HEAD::RESOLUCIONINCORRECTA;
		(*jugadorActual)->send(comando);
		comando.clear();
		comando << HEAD::RESOLVERSC;
		//jugadores.begin();
		jugadorActual++;
		
		if (jugadorActual == jugadores.end())
			jugadorActual = jugadores.begin();

			(*jugadorActual)->send(comando);
		
	}
}

void recibirPacket()
{
	(*jugadorActual)->receive(comando);	
	
	int temp;
	
	comando >> temp;
	c = (HEAD)temp;
	//std::cout << "He recibido " << comandServer;
	switch (c)
	{
	case HEAD::ELEGIRPISTA:    //Recibir Pista
		//std::cout << "Recibo ELEGIRPISTA" << std::endl;
		enviarRecibirPista();
		break;
	case HEAD::MOVIMIENTO:		//Recibir pos
	//	std::cout << "Recibo MOVIMIENTO" << std::endl;
		actualizarPos();
		break;
	case HEAD::DEDUCCION:     //Recibir deduccion
		//std::cout << "Recibo DEDUCCION" << std::endl;
		desmentir();
		break;
	case HEAD::DESMENTIDO:
		//std::cout << "Recibo DESMENTIDO" << std::endl;
		enseñarCarta();
		break;
	case HEAD::RESOLVERCS:
	//	std::cout << "Recibo RESOLVERCS" << std::endl;
		comprobar();
		break;
	case HEAD::ENDTURNO:
		end_turno = true;
		comando.clear();
		break;
	}
}

void turno()
{


	//(*jugadorActual)->send(comando);
	tirarDados();
	while (!end_turno)
	{
		recibirPacket();

	}


}

void partida()
{
	//std::cout << "Entro en la partida." << std::endl;
	std::list<sf::TcpSocket*>::iterator j = jugadores.begin();
	std::string nom;
	nom = listaPlayers[0].name;

	sf::Packet cambio;
	cambio << HEAD::CAMBIOTURNO << nom;
	jugadorActual = j;
	EnviarAll(cambio, *jugadorActual);
	cambio.clear();

	
	int counter = 0;

	while (1)
	{
	
		turno();
	
		if (counter!=(listaPlayers.size()-1))
		{		
			counter++;
			j++;
			jugadorActual = j;
		}
		else
		{
			j = jugadores.begin();
			counter = 0;
			jugadorActual = j;			
		}
		if ((listaPlayers.size()-1) == n)
		{
			n = 0;
		}
		else
		{
			n++;
		}

		nom = listaPlayers[n].name;
		cambio <<HEAD::CAMBIOTURNO << nom;
		EnviarAll(cambio,*jugadorActual);
		cambio.clear();
	}
}

int main()
{

	srand(time(NULL));
	ControlServidor();

	if (!p2pConexion)
		partida();

	//tirarDados();
	std::string a;
	std::cin >> a;


	return 0;
}

/*#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace sf;

const unsigned short MAX_PLAYERS = 5;
const unsigned short SERVER_PORT = 50000;

struct Address {
	std::string nick;
	IpAddress ipAdress;
	unsigned short port;

	Address(std::string _nick, IpAddress _ipAddress, unsigned short _port) : nick(_nick), ipAdress(_ipAddress), port(_port) {}

};

void print(std::string text) {
	std::cout << text << std::endl;
}

int main()
{
	std::vector<Address*> peer;
	TcpListener listener;

	unsigned int random = (unsigned int)rand();

	listener.listen(SERVER_PORT);

	for (short i = 0; i < MAX_PLAYERS; i++)
	{
		TcpSocket socket;
		if (listener.accept(socket) != Socket::Status::Done) {
			print("error al listener");
		}

		std::string nickname;
		Packet nickPacket;
		socket.receive(nickPacket);
		nickPacket >> nickname;

		Packet pack;
		Address* newAddress = new Address(nickname, socket.getRemoteAddress(), socket.getRemotePort());
		peer.push_back(newAddress);

		int count = peer.size() - 1;
		pack << count;
		
		pack << random;

		for (int i = 0; i < peer.size() - 1; i++) {
			pack << peer[i]->ipAdress.toString() << peer[i]->port << peer[i]->nick;
			std::cout << peer[i]->nick << std::endl;
		}

		socket.send(pack);
		socket.disconnect();
	}

	listener.close();
	return 0;
}*/