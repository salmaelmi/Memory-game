#ifndef fontions_h_
#define fonctions_h_
#include <SDL.h>
#include <time.h>

//Les prototypes des fonctions

int* menu();
void tab_niv(int niv,int tab[]);
void random(int n,int tab[n]);

void random_image(int niv,int tab[],SDL_Surface* cards[],SDL_Surface* rand_cards[]);
void affecter_pos(int niv,SDL_Rect rectpos[]);
void retourn_imag(int i,int u,SDL_Surface* imageretourne,SDL_Surface* screen,SDL_Rect rect[],SDL_Surface* imagert[2],SDL_Renderer* rend);
void supp_img(int i,int positionx[2],int positiony[2],SDL_Surface* screen,SDL_Renderer* rend);
void renv_img(SDL_Surface* dos,int i,int positionx[2],int positiony[2],SDL_Renderer* rend);

void chrono(unsigned int currentTime);
void gagnant(int nbjoueur, int niv, int score1, int score2, int score );

void displaytext(char text[],char fontut[],int taille,int c1,int c2,int c3,int x, int y,SDL_Renderer* renderer);



//la structure

typedef struct{
    char nom[20];
    char username[20];
    int age;
}joueur;



#endif // fontions_h


