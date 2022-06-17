#include "joueur.h"

//Constructeur perso 
Joueur::Joueur(int x, int y, Inventaire* inventaireDuJoueur) {
    //attribut la position du joueur � sa g�n�ration
    setPosX(x);
    setPosY(y);

    Vector2i anim(1, Down);
    vitesse = 0;
    updateFPS = true;

    inventaire = inventaireDuJoueur;
}

//Getter
Joueur::Pos Joueur::getPos(void) const
{
    return posJoueur;
}

Sprite Joueur::getSprite() {
    return sprite_joueur;
}

//Setter
void Joueur::setInput(Input input) {
    inputPerso = input;
}

void Joueur::setPosX(int x)
{
    posJoueur.posX = x;
}
void Joueur::setPosY(int y)
{
    posJoueur.posY = y;
}




//Fonctions
//Permet de telecharger la texture du perso dans le dossier res
void Joueur::loadTexturePerso()
{
    if (!texture_joueur.loadFromFile("res/img/perso1.png")) {
        cout << "erreur" << endl;
    }
    else {
        sprite_joueur.setTexture(texture_joueur);
    }
    if (!texture_boite.loadFromFile("res/img/chargement1.png")) {
        cout << "erreur" << endl;
    }
    else {

        sprite_boite.setTexture(texture_boite);
    }
    if (!texture_chargement.loadFromFile("res/img/chargement2.png")) {
        cout << "erreur" << endl;
    }
    else {

        sprite_chargement.setTexture(texture_chargement);
    }

}

//permet de determiner la vitesse de d�placement du perso
void Joueur::vitesseDeplacementPerso(int vitesse, vector<Materiaux>& listeDesMateriaux) {
    if (timeDeplacementPerso.getElapsedTime().asMilliseconds() >= vitesse) {
        deplacementPerso(listeDesMateriaux);
        timeDeplacementPerso.restart();
    }
}

//Dirige le personnage

void Joueur::deplacementPerso(vector<Materiaux>& listeDesMateriaux) {
    int memoX = getPos().posX;
    int memoY = getPos().posY;

    updateFPS = false;
    vitesse = 10;
    if (inputPerso.GetButton().left == true) {
        if (inputPerso.GetButton().clicG != true) {
            anim.y = Left;
        }
        updateFPS = true;
        setPosX(getPos().posX - 1);
    }
    if (inputPerso.GetButton().right == true) {
        if (inputPerso.GetButton().clicG != true) {
            anim.y = Right;
        }
        updateFPS = true;
        setPosX(getPos().posX + 1);
    }
    if (inputPerso.GetButton().down == true) {
        if (inputPerso.GetButton().clicG != true) {
            anim.y = Down;
        }
        updateFPS = true;
        setPosY(getPos().posY + 1);
    }
    if (inputPerso.GetButton().up == true) {
        if (inputPerso.GetButton().clicG != true) {
            anim.y = Up;
        }
        updateFPS = true;
        setPosY(getPos().posY - 1);
    }
    if (inputPerso.GetButton().shift == true) {
        vitesse = 5;
    }
    for (int i = 0; i < listeDesMateriaux.size(); i++) {
        if (listeDesMateriaux.at(i).getSprite().getGlobalBounds().contains(getPos().posX + 20, getPos().posY + 32)) {
            setPosX(memoX);
            setPosY(memoY);
        }
    }

    sprite_joueur.setPosition(getPos().posX, getPos().posY);

    

}

//Fonction qui donne l'annimation du perso en fonction de sa direction
void Joueur::animationPerso(int y) {

    if (updateFPS) {
        if (timeAnimationPerso.getElapsedTime().asMilliseconds() >= 140) {
            anim.x++;
            if (anim.x * 48 >= texture_joueur.getSize().x) {
                anim.x = 0;
            }
            timeAnimationPerso.restart();
        }
    }
    else {
        anim.x = 1;
    }

    sprite_joueur.setTextureRect(IntRect(anim.x * 48, anim.y * 48 + y, 48, 48));
}

//Prolongation de la boucle principale.
//Dessine le perso dans la fen�tre
void Joueur::controlePerso(RenderWindow& window, vector<Materiaux>& listeDesMateriaux) {
    
    if (inputPerso.GetButton().clicG) {
        ramasseMateriaux(window,listeDesMateriaux);
    }
    else {
        ramassage = 0;
    }
    vitesseDeplacementPerso(vitesse, listeDesMateriaux);
    
    animationPerso(0);
    window.draw(sprite_joueur);
}

void Joueur::ramasseMateriaux(RenderWindow& window, vector<Materiaux>& listeDesMateriaux) {
    
    int positionSourisX = laSouris.getPosition().x + getPos().posX - window.getPosition().x-450;
    int positionSourisY = laSouris.getPosition().y + getPos().posY - window.getPosition().y - 475;

    

    for (int i = 0; i < listeDesMateriaux.size(); i++) {
        if (listeDesMateriaux.at(i).getSprite().getPosition().x <= getPos().posX + 80 && listeDesMateriaux.at(i).getSprite().getPosition().x >= getPos().posX-28 && listeDesMateriaux.at(i).getSprite().getPosition().y <= getPos().posY + 75 && listeDesMateriaux.at(i).getSprite().getPosition().y >= getPos().posY-28) {
            if (listeDesMateriaux.at(i).getSprite().getGlobalBounds().contains(positionSourisX, positionSourisY)) {
           
                sprite_boite.setPosition(getPos().posX, getPos().posY - 32);
                window.draw(sprite_boite);

                sprite_chargement.setPosition(getPos().posX, getPos().posY - 32);
                sprite_chargement.setTextureRect(IntRect(0, 0, 48* ramassage / listeDesMateriaux.at(i).solidite, 24));
                window.draw(sprite_chargement);

                ramassage++;
                if (ramassage >= listeDesMateriaux.at(i).solidite) {
                    bool dejaPresent = false;
                    for (int j = 0; j < inventaire->idMateriaux.size(); j++) {
                        if (inventaire->idMateriaux.at(j) == listeDesMateriaux.at(i).idMateriaux) {
                            inventaire->quantite.at(j)++;
                            dejaPresent = true;
                        }
                    }
                    if (!dejaPresent) {
                        inventaire->idMateriaux.push_back(listeDesMateriaux.at(i).idMateriaux);
                        inventaire->quantite.push_back(1);
                    }
                    listeDesMateriaux.erase(listeDesMateriaux.begin() +  i);
                    ramassage = 0;
                }
                
            }
        }
    }
}

//gives the angle from point one to point two
float Joueur::anglePoints(int x1, int y1, int x2, int y2)
{
    return atan2(y2 - y1, x2 - x1);
}

//gives the true angle from point one to point two
float Joueur::anglePointsDegree(int x1, int y1, int x2, int y2)
{
    float prem = atan2(y2 - y1, x2 - x1);
    if (prem <= 0) {
        return abs(prem) * 60;
    }
    else {
        return 360 - (prem * 60);
    }

}