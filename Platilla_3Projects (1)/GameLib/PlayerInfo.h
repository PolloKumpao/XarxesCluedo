#pragma once
#include <list>
#include <SFML\Graphics.hpp>

enum tipo { PERSONAJE, ARMA, SALA };
class carta
{
public:
	tipo cartatipo;
	std::string nombre;
	int numero;

	carta(tipo t, std::string s, int n)
	{
		cartatipo = t;
		nombre = s;
		numero = n;
	}
private:

};

class PlayerInfo
{

	std::string name;
	sf::Vector2i position;
	
	int lives;
public:
	std::list<carta> mano;
	PlayerInfo();
	~PlayerInfo();
};
