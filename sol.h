#ifndef SOL_H
#define SOL_H

//include
#include <SFML/Graphics.hpp>
#include <iostream>
#include "joueur.h"
#include <vector>


//namespaces
using namespace sf;
using namespace std;

class Sol {


	Texture texture_sol;
	Texture texture_sol2;
	Texture texture_sol3;

	Sprite sprite_sol;
	Sprite sprite_sol2;

	int niveauX = 0;
	int niveauY = 0;


public:
	//Proto du contructeur
	Sol();

	//fontion
	void loadTextureSol();
	void afficheSol(RenderWindow& window, Joueur& leJoueur);




	//attribut private
private:

};
#endif

