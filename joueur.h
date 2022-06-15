#ifndef JOUEUR_H
#define JOUEUR_H

//include
#include <SFML/Graphics.hpp>
#include <iostream>
#include "input.h"
#include "materiaux.h"
#include "inventaire.h"
#include <vector>


//namespaces
using namespace sf;
using namespace std;

class Joueur {
	//recupere les actions du joueur (shift pour aller plus vite)
	Input inputPerso;
	Mouse laSouris;
	Inventaire inventaire;


	//structure utilis�e dans Perso.cpp
	struct Pos { int posX, posY; };

	//Texture du personnage (image dans un dossier)
	Texture texture_joueur;
	//Sprite du personnage (apparence du personnage en jeu)
	Sprite sprite_joueur;
	//Liste des directions o� peut regarder notre personnage
	enum Dir { Down, Left, Right, Up };
	//(x, y) x = colonne d'animation (de 1 � 3) et y = ligne d'animation (choix de la liste juste au dessus)
	Vector2i anim;
	//Toutes les clocks
	Clock timeDeplacementPerso;
	Clock timeAnimationPerso;

	//Caract�ristiques du personnage
	bool updateFPS;
	int vitesse;
	float positionXSourisVue;
	float positionYSourisVue;

	int ramassage = 0;

	//Fonction public
public:
	//Proto du contructeur
	Joueur(int x, int y, Inventaire& inventaireDuJoueur);

	//Setter
	void setInput(Input input);
	void setPosX(int x);
	void setPosY(int y);

	//Getter
	Pos getPos(void) const;
	Sprite getSprite();

	//fontion
	void loadTexturePerso();
	void deplacementPerso(vector<Materiaux>& listeDesMateriaux);
	void ramasseMateriaux(RenderWindow& window, vector<Materiaux>& listeDesMateriaux);
	void animationPerso(int y);
	void vitesseDeplacementPerso(int vitesse, vector<Materiaux>& listeDesMateriaux);
	void controlePerso(RenderWindow& window, vector<Materiaux>& listeDesMateriaux);
	float anglePoints(int x1, int y1, int x2, int y2);
	float anglePointsDegree(int x1, int y1, int x2, int y2);



	//attribut private
private:
	Pos posJoueur;
};
#endif
