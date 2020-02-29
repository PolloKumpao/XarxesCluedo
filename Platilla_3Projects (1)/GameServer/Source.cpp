#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <PlayerInfo.h>
#include <list>
sf::TcpSocket incoming;

//Funcion por la que el servidor recibe mensajes
enum comandos {START,LANZADADOS,ELEGIRPISTA,REVELARPISTA,MOVIMIENTO,NUEVAPOSICION,DEDUCCION,ENVIOSUPOSICION,
				DESMENTIRCS,DESMENTIRSC,DESMENTIDO,DESMENTIDOGENERAL,RESOLVERCS,RESOLVERSC,RESOLUCIONCORRECTA};
enum tipo { PERSONAJE, ARMA, SALA};

class carta
{
public:
tipo cartatipo;
std::string nombre;

carta(tipo t, std::string s)
	{
		cartatipo = t;
		nombre = s;
	}
private:

};
int dado1;
int dado2;
std::list<carta> baraja;
std::list<carta> crimen;
std::list<PlayerInfo>
void crearBaraja()
{
	
	baraja.push_back(carta(PERSONAJE,"Amapola"));
	baraja.push_back(carta(PERSONAJE,"Rubio"));
	baraja.push_back(carta(PERSONAJE,"Orquidea"));
	baraja.push_back(carta(PERSONAJE,"Celeste"));
	baraja.push_back(carta(PERSONAJE,"Prado"));
	baraja.push_back(carta(PERSONAJE,"Mora"));
	
	
	baraja.push_back(carta(ARMA,"Candelabro"));
	baraja.push_back(carta(ARMA,"Cuerda"));
	baraja.push_back(carta(ARMA,"Puñal"));
	baraja.push_back(carta(ARMA,"Pistola"));
	baraja.push_back(carta(ARMA,"Tuberia de Plomo"));
	baraja.push_back(carta(ARMA,"Herramienta"));
	
	baraja.push_back(carta(SALA,"Biblioteca"));
	baraja.push_back(carta(SALA,"Cocina"));
	baraja.push_back(carta(SALA,"Billar"));
	baraja.push_back(carta(SALA,"Baile"));
	baraja.push_back(carta(SALA,"Invernadero"));
	baraja.push_back(carta(SALA,"Comedor"));
	baraja.push_back(carta(SALA,"Vestibulo"));
	baraja.push_back(carta(SALA,"Salon"));
	baraja.push_back(carta(SALA,"Estudio"));



}



std::list<carta> crearCrimen(std::list<carta> b)
{
	
	std::list<carta> c;
	std::list<carta>::iterator it = b.begin();

	int r;
	r = rand() % 6;
	std::advance(it, r-1);
	c.push_back(*it);
	b.erase(it);

	r = rand() % 6 + 6;
	it = b.begin();
	std::advance(it, r - 1);
	c.push_back(*it);
	b.erase(it);
	

	r = rand() % 9 + 12;
	it = b.begin();
	std::advance(it, r - 1);
	c.push_back(*it);
	b.erase(it);
	return c;
	
}



int main()
{
	srand(time(NULL));
	crearBaraja();
	crimen = crearCrimen(baraja);


	
	/*PlayerInfo playerInfo;

	sf::TcpSocket socket;
	sf::TcpListener dispatcher;
	sf::Packet pack;
	std::string prueba;


	//5000 es el puerto por el que escucha el servidor.
	//El cliente debe conocer la ip del servidor y el puerto por el que escucha.
	sf::Socket::Status status = dispatcher.listen(5000);

	std::list<sf::TcpSocket> clientes;

	std::cout << "Buscando" << std::endl;
	if (status != sf::Socket::Done)
	{
		std::cout << "No se puede vincular" << std::endl;
	}

	//Al conectarse un cliente, el socket incoming pasa a ser el que utilizan este
	//cliente y el servidor para comunicarse en exclusiva
	if (dispatcher.accept(incoming) != sf::Socket::Done)
	{
		std::cout << "Error" << std::endl;
	}
	else
	{
		std::cout << "Conectado el cliente con puerto " << incoming.getRemotePort() << std::endl;
		//clientes.push_back(incoming);
	}

	
	incoming.receive(pack);
	pack >> prueba;
	std::cout << prueba;

	//for(int i = 0; i<clientes.size(); i++)
	


	while (1)
	{

	}*/

	return 0;
}