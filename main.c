#include <stdlib.h>
#include <string.h>

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_timer.h>
#include "fonctions.h"




int main(int argc, char *argv[])
{

    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ); //Initialize SDL_mixer
    Mix_AllocateChannels(10);                           // possibilité de jouer 10 sons simultanément

    int mus;
    printf("   Voulez vous de la Musique? \n    1 : oui. \t 2: non.\n");
    scanf("%d", &mus);
    if(mus==1){
    Mix_Music *musique=NULL; //Création du pointeur de type Mix_Music

    musique = Mix_LoadMUS("musique.mp3");

     //Chargement de la musique
    Mix_PlayMusic(musique, -1); //Jouer infiniment la musique
    }



    int niv; //le niveau choisi
    int nbjoueur; //nombre de joueurs
    int i,nb_click=0,score1=0,score2=0,score=0;
    int* choix;
    int positionx[2],positiony[2];
    unsigned int currentTime;

    choix=menu();  //pointeur des choix choisis par le joueur
    niv=choix[0];
    nbjoueur=choix[1];
    int tab[niv];

    //Réaliser un tableau selon les niveaux
    tab_niv(niv,tab);

    printf("     \n       *******************************************************     \n\n");
    printf("Nombre de cartes : %d \nNombre de joueurs: %d",niv,nbjoueur);
    printf("\n");

    //initialiser sdl et sdl_ttf
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    //creer une fenetre
    SDL_Window* window = SDL_CreateWindow("jeu de memoire ",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,1000, 667,SDL_WINDOW_SHOWN );

    //Get window surface //The surface contained by the window
    SDL_Surface* screen =SDL_GetWindowSurface( window );


    // creer un renderer
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // creer les rectangles des images
    SDL_Rect backgrect= {0,0,1000,667};
    SDL_Rect rectstart= {450,400,200,84};
    SDL_Rect rectquitter= {877,0,133,86};
    SDL_Rect rectdos[niv];

    affecter_pos(niv,rectdos); //Positionner les cartes du jeu sur l'interface graphique

    // charger l'image dans la memoire en utilisant les fonctions de SDL_image
    SDL_Surface* surface  = IMG_Load("images/memogame.jpg");
    SDL_Surface* button   = IMG_Load("images/play.jpg");
    SDL_Surface* quitter  = IMG_Load("images/quitter.png");
    SDL_Surface* backg    = IMG_Load("images/backg.jpg");
    SDL_Surface* dos      = IMG_Load("images/back.jpg");
    SDL_Surface* endbackg = IMG_Load("images/end.jpg");

    SDL_Surface* rand_cards[niv];
    SDL_Surface* imageretourne;
    SDL_Surface* imagert[2];


    //creer un array qui contient les cartes
    SDL_Surface* cards[8];
    cards[0]=IMG_Load("images/1cat.jpg");
    cards[1]=IMG_Load("images/2lion.jpg");
    cards[2]=IMG_Load("images/3ping.jpg");
    cards[3]=IMG_Load("images/4dog.jpg");
    cards[4]=IMG_Load("images/5rabbit.jpg");
    cards[5]=IMG_Load("images/6monk.jpg");
    cards[6]=IMG_Load("images/7donk.jpg");
    cards[7]=IMG_Load("images/8fish.jpg");




    //Creer les textures en utilisant SDL_Texture
    SDL_Texture* texsurface = SDL_CreateTextureFromSurface(rend, surface);
    SDL_Texture* texstart   = SDL_CreateTextureFromSurface(rend, button);
    SDL_Texture* texbackg   = SDL_CreateTextureFromSurface(rend, backg);
    SDL_Texture* texquit    = SDL_CreateTextureFromSurface(rend, quitter);
    SDL_Texture* texdos[16] ;
    for (i=0; i<niv ; i++)
        {
            texdos[i]= SDL_CreateTextureFromSurface(rend, dos);
        }
    SDL_Texture* texend    = SDL_CreateTextureFromSurface(rend, endbackg);

    int quit=0;
    int start = 0;
    int butt=0;

    //Creer des evenements
    SDL_Event event;
    SDL_Event event2;
    SDL_Event event3;


     //Clear screen
    SDL_RenderClear( rend );

    //Render texture to screen
    SDL_RenderCopy( rend, texsurface, NULL, &backgrect );
    SDL_RenderCopy(rend, texstart, NULL, &rectstart);

    //Update screen
    SDL_RenderPresent( rend);

    //Melanger les cartes et les stocker dans le tableau rand_cards
    random_image(niv,tab,cards,rand_cards);

    printf("     \n       *******************************************************     \n\n");

    char* tour_joueur="joueur1";  //initialiser le tour du joueur
    if (nbjoueur==2)
    {
        printf("\n C'est le tour du %s \n",tour_joueur);
    }


    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            //L'interface se ferme si le joueur clique sur le boutton "Quit" ou qand il ferme la fenetre
            if ((event.type==SDL_QUIT)||(event.button.x >=877 && event.button.x<=1000 && event.button.y>=0 && event.button.y <=80 && event.type == SDL_MOUSEBUTTONDOWN))
            {
                quit = 1;
            }

        }

        while(!start)
        {
            currentTime = SDL_GetTicks();
            while(SDL_PollEvent(&event2))
            {

                if(event2.type == SDL_QUIT)
                {
                    quit= 1;
                    start=1;
                }

                //Le jeu commence lorsque le joueur clique sur le boutton "Start"
                if (event2.button.x>=450 && event2.button.x<=650 && event2.button.y>=400 && event2.button.y<= 484 && event2.type==SDL_MOUSEBUTTONDOWN)
                {
                    start = 1;

                 //Clear screen
                SDL_RenderClear( rend );

                //Render texture to screen
                SDL_RenderCopy(rend, texbackg, NULL, &backgrect);
                SDL_RenderCopy(rend, texquit, NULL, &rectquitter);

                for (i=0; i<niv; i++)
                    {
                        SDL_RenderCopy(rend, texdos[i], NULL, &rectdos[i]);
                    }

                //Update screen
                SDL_RenderPresent( rend);
                }

            }

        }

       while(!butt)
        {
            while(SDL_PollEvent(&event3))
            {
                if ((score1+score2)== niv/2 || score==niv/2)
                {
                    gagnant(nbjoueur,niv, score1, score2,  score ); //Annonce le gagnant et son score
                    chrono(currentTime); // Affiche la durée de la partie

                    while(SDL_WaitEventTimeout(&event3,50)) {}
                    SDL_RenderClear( rend );
                    SDL_RenderCopy(rend, texend , NULL, &backgrect);
                    SDL_RenderPresent(rend);
                    butt=1;
                    break;
                }



                if (nb_click==2)
                {
                    if ((imagert[1]==imagert[2]) && ((positionx[1]!=positionx[2])||(positiony[1]!=positiony[2])))
                        //Si le joueur retourne une paire
                    {
                        printf("vous avez retournez une paire\n\n");
                        nb_click=0;
                        if(nbjoueur==2)
                        {
                            if (strcmp(tour_joueur,"joueur1")==0)
                            {
                                score1++;
                                tour_joueur="joueur2";

                            }
                            else
                            {
                                score2++;
                                tour_joueur="joueur1";
                            }
                            printf("c'est le tour du %s \n  ",tour_joueur);
                            printf("        ********* score1=%d  score2=%d *********\n", score1, score2);
                        }
                        else {
                            score++;
                            printf("        ********* score = %d *********\n",score);
                          }

                        while(SDL_WaitEventTimeout(&event3,50)) {}

                        supp_img(1,positionx,positiony,screen,rend);  //couvrir les cartes retournées qui sont identiques
                        supp_img(2,positionx,positiony,screen,rend);
                    }


                    else  //Si les 2 cartes ne sont pas identiques
                    {
                        printf("vous n'avez pas trouvez une paire\n\n");
                        if(nbjoueur==2)
                        {
                            if (strcmp(tour_joueur,"joueur1")==0)
                            {
                                tour_joueur="joueur2";
                            }
                            else
                            {
                                tour_joueur="joueur1";
                            }
                            printf("c'est le tour du %s \n",tour_joueur);
                        }

                        nb_click=0;
                        while(SDL_WaitEventTimeout(&event3,300)) {}

                        renv_img(dos,1,positionx,positiony,rend);  //renverser les cartes retournées qui ne sont pas identiques
                        renv_img(dos,2,positionx,positiony,rend);
                    }
                }

                if(event3.type==SDL_MOUSEBUTTONDOWN) // Si le joueur clique
                {
                    int x = event3.button.x;  // la coordonnée x du click
                    int y = event3.button.y;  // la coordonnée x du click


                    for (i=0; i<niv; i++)
                    {
                        switch(i)
                        {
                        case 0:
                            imageretourne=rand_cards[0];
                            break;
                        case 1:
                            imageretourne=rand_cards[1];
                            break;
                        case 2:
                            imageretourne=rand_cards[2];
                            break;
                        case 3:
                            imageretourne=rand_cards[3];
                            break;
                        case 4:
                            imageretourne=rand_cards[4];
                            break;
                        case 5:
                            imageretourne=rand_cards[5];
                            break;
                        case 6:
                            imageretourne=rand_cards[6];
                            break;
                        case 7:
                            imageretourne=rand_cards[7];
                            break;
                        case 8:
                            imageretourne=rand_cards[8];
                            break;
                        case 9:
                            imageretourne=rand_cards[9];
                            break;
                        case 10:
                            imageretourne=rand_cards[10];
                            break;
                        case 11:
                            imageretourne=rand_cards[11];
                            break;
                        case 12:
                            imageretourne=rand_cards[12];
                            break;
                        case 13:
                            imageretourne=rand_cards[13];
                            break;
                        case 14:
                            imageretourne=rand_cards[14];
                            break;
                        case 15:
                            imageretourne=rand_cards[15];
                            break;
                        }

                        x=event3.button.x;
                        y=event3.button.y;

                        if ((x>rectdos[i].x) && (x<rectdos[i].x + 130) && (y>rectdos[i].y) && (y<rectdos[i].y + 130))
                        {
                            nb_click=nb_click+1;
                            retourn_imag(i,nb_click,imageretourne,screen,rectdos,imagert,rend); //Retourne les cartes du jeu

                            //Memorise les coordonnes des cartes retournées
                            positionx[nb_click]=rectdos[i].x;
                            positiony[nb_click]=rectdos[i].y;
                        }

                        if (nb_click==2)
                        {
                            break;
                        }
                    }

                }


            }

            if ((event3.type==SDL_QUIT)||(event3.button.x >=877 && event3.button.x<=1000 && event3.button.y>=0 && event3.button.y <=80 && event3.type == SDL_MOUSEBUTTONDOWN))
            {
                quit= 1;
                start=1;
                butt=1;
            }

        }
}



    //Free resources and close SDL
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(backg);
    SDL_Quit();
    return 0;

}







