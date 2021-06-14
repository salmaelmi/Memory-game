#include <stdio.h>
#include<SDL_ttf.h>
#include "fonctions.h"

//#include <time.h>
//#include<conio.h>







int* menu()
{
    int *tab;
    FILE *fichier;

    printf("         *********************************\n");
    printf("                   JEU DE MEMOIRE  \n");
    printf("         *********************************\n");

    int choix1;     //choix du mode du jeu
    int choix2;     //choix du niveau du jeu
    int nbrecards;  //nombre de cartes

    joueur joueur1,joueur2;

    printf("Veuillez choisir un nombre:\n 1.Jouer individuellement.\n 2.Jouer en 2.\n 3.Je suis un administrateur.\n");
    scanf("%d",&choix1);

    switch(choix1)
     {
      case 1: {
           printf("Entrez votre username : ");
           scanf("%s",&(joueur1.username));
           fichier=fopen("joueur.txt","a");

           printf("Entrez votre nom      : ");
           scanf("%s",joueur1.nom);

           printf("Entrez votre age      : ");
           scanf("%d",&joueur1.age);
           fprintf(fichier,"le username : %s; Le nom   : %s; L'age   : %d  \n",joueur1.username,joueur1.nom,joueur1.age);
        break;}


      case 2: {
               printf("Entrez le username du joueur 1 : ");
               scanf("%s",&(joueur1.username));
               fichier=fopen("joueur.txt","a");
               printf("Donnez le nom du joueur 1      : ");
               scanf("%s",joueur1.nom);
               printf("Entrez l'age du joueur 1       : ");
               scanf("%d",&joueur1.age);
               fprintf(fichier,"le username : %s; le nom : %s; l'age : %d  \n",joueur1.username,joueur1.nom,joueur1.age);

              }

              {
               printf("\n\nEntrez le username du joueur 2  :");
               scanf("%s",&(joueur2.username));
               fichier=fopen("joueur.txt","a");
               printf("Donner le nom du joueur 2       : ");
               scanf("%s",joueur2.nom);
               printf("Entrez l'age du joueur 2        : ");
               scanf("%d",&joueur2.age);
               fprintf(fichier,"le username : %s; le nom : %s; l'age : %d  \n", joueur2.username, joueur2.nom, joueur2.age);


              break;}

      case 3: {
            char currentchar;
            fichier=fopen("joueur.txt","r");
            if (fichier != NULL)
              {
                  do
                    {
                      currentchar = fgetc(fichier);
                      printf("%c", currentchar);
                    } while (currentchar != EOF);

                fclose(fichier);
               _Exit( 0 );
               }
            }  break;

     }

     printf("\n\nVeuillez choisir un niveau:\n 1.Facile.\n 2.Moyen.\n 3.Difficile.\n");
     scanf("%d",&choix2);

     switch(choix2)
     {
         case 1: nbrecards=8;break;
         case 2: nbrecards=12;break;
         case 3: nbrecards=16;break;
     }

     tab=(int*)malloc(2*sizeof(int));
     *tab=nbrecards;
     *(tab+1)=choix1;
     return tab;
}



void tab_niv(int niv,int tab[])
{
    switch(niv)
    {
        case 16: tab[12]=6;tab[13]=6; tab[14]=7; tab[15]=7;
    	case 12: tab[8]=4; tab[9]=4;  tab[10]=5; tab[11]=5;
        case 8:  tab[0]=0; tab[1]=0;  tab[2]=1;  tab[3]=1;tab[4]=2;tab[5]=2;tab[6]=3;tab[7]=3;
        break;

	   }

}


void random(int n,int tab[])
{
	srand(time(0));        //initialise la premiere de valeur aleatoire
    int i,j,temp  ;


    for (i=0;i<n;i++)
    {
        j=i+rand()%(n-i);   //methode congruencielle pour generer des valeurs aleatoires
        temp=tab[i];
        tab[i]=tab[j];
        tab[j]=temp;
        printf("tab[%d]=%d \n",i,tab[i]);

    }
}




void random_image(int niv,int tab[],SDL_Surface* cards[],SDL_Surface* rand_cards[])
{
     int i;
     random(niv,tab);    //mélanger les éléments du tableau
     for (i=0;i<niv;i++)
     {
         rand_cards[i]=cards[tab[i]];
     }
}


void affecter_pos(int niv,SDL_Rect rectpos[])
{
    int i,marge;
    for (i=0;i<niv;i++)
    {
        switch(niv){case 8: marge=100; break;  case 12: marge=50;break; case 16: marge=0;}

    if (i>=0&&i<4) {   rectpos[i].x=450+i*132;       rectpos[i].y=120+marge; rectpos[i].w=130; rectpos[i].h=130;}
    if (i>=4&&i<8) {   rectpos[i].x=450+(i-4)*132;   rectpos[i].y=252+marge; rectpos[i].w=130; rectpos[i].h=130;}
    if (i>=8&&i<12) {  rectpos[i].x=450+(i-8)*132;   rectpos[i].y=384+marge; rectpos[i].w=130; rectpos[i].h=130;}
    if (i>=12&&i<16){  rectpos[i].x=450+(i-12)*132;  rectpos[i].y=516+marge; rectpos[i].w=130; rectpos[i].h=130;}

    }

}



void retourn_imag(int i,int u,SDL_Surface* imageretourne,SDL_Surface* screen,SDL_Rect rect[],SDL_Surface* imagert[2],SDL_Renderer* rend)
{
    SDL_Texture* teximg = SDL_CreateTextureFromSurface(rend, imageretourne);
    SDL_Rect rectimg;
    rectimg.x=rect[i].x; rectimg.y=rect[i].y; rectimg.w=rect[i].w; rectimg.h=rect[i].h;

    SDL_RenderCopy(rend, teximg, NULL, &rectimg);
    SDL_RenderPresent(rend);

    imagert[u]=imageretourne;  //Memorise les deux images cliquées


}


void supp_img(int i,int positionx[2],int positiony[2],SDL_Surface* screen,SDL_Renderer* rend)
{

    SDL_Surface* supp=IMG_Load("images/supp.png");
    SDL_Texture* texsupp=SDL_CreateTextureFromSurface(rend, supp);
    int x=positionx[i]; int y=positiony[i];
    SDL_Rect rectsupp;
    rectsupp.x=x; rectsupp.y=y; rectsupp.w=130; rectsupp.h=130;
    SDL_RenderCopy(rend, texsupp, NULL, &rectsupp);
    SDL_RenderPresent(rend);

}


void renv_img(SDL_Surface* dos,int i,int positionx[2],int positiony[2],SDL_Renderer* rend)
{
   SDL_Texture* texdos=SDL_CreateTextureFromSurface(rend, dos);
   int x=positionx[i]; int y=positiony[i];    //les coordonnées de la carte à renverser

   SDL_Rect rectdos;
   rectdos.x=x; rectdos.y=y; rectdos.w=130; rectdos.h=130;
   SDL_RenderCopy(rend, texdos, NULL, &rectdos);
   SDL_RenderPresent( rend );

}


void gagnant(int nbjoueur, int niv, int score1, int score2, int score )
{
    if (nbjoueur==2 && score1>score2)
        {
            printf(" \n    C'est le joueur1 qui a gagne!!");
        }
    else
        {
            if (nbjoueur==2 && score1<score2)
            {
                printf("\n   C'est le joueur2 qui a gagne!!");
            }
            else if (nbjoueur==2 && score1==score2)
            {
               printf("\n   IT's a Tie");
            }
            else if (nbjoueur==1 && score==niv/2) printf("\n   Victoire!!");
         }
}




void displaytext(char text[],char fontut[],int taille,int c1,int c2,int c3,int x, int y,SDL_Renderer* renderer) // affichage du text avec lecture du font
{
    TTF_Font *font = TTF_OpenFont(fontut, taille);
    SDL_Color color = { c1, c2, c3 };
    SDL_Surface *surface_text = TTF_RenderText_Solid(font,text, color);
    SDL_Texture *texture_text = SDL_CreateTextureFromSurface(renderer, surface_text);
    SDL_Rect textc = { x, y, 50, 50 };
    SDL_QueryTexture(texture_text, NULL, NULL, &textc.w, &textc.h);
    SDL_RenderCopy(renderer, texture_text, NULL, &textc);
    SDL_FreeSurface(surface_text);
    SDL_DestroyTexture(texture_text);
    TTF_CloseFont(font);

}

void chrono(unsigned int currentTime)
{
    unsigned int sec,min=00;
    sec=(SDL_GetTicks()-currentTime);//valeur retournée en ms
    sec=sec/1000;               //transformation en sec
     if (sec>59){
        min=sec/60;
        sec=sec%60;
    }

    printf("\n\n****** La partie a duree %02u min :%u sec ******** ",min,sec);

}




