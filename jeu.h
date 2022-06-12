#ifndef JEU_H
#define JEU_H

#include <iostream>
#include "input.h"
#include "sol.h"
#include "joueur.h"
#include "materiaux.h"
#include "hud.h"
#include <vector>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

//Constantes du Programme
const int SCREEN_SIZE_WEIGHT = 960;
const int SCREEN_SIZE_HEIGHT = 960;

using namespace sf;
using namespace std;

class Jeu {
	View vue = View();
	VideoMode ecran;
	Clock clk;
	Mouse laSouris;

	RenderWindow window;

	//Input input;
	Event event;
	

public:

	//Proto du contructeur
	Jeu();

	//getter

	//setter

	//fonction
	void creationJeu();
	void bouclePrincipale();
	bool isOpen();

private:

};
#endif


