
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fichier_feu.h"
#define LAMBDA 13

// REMARQUES POUR LA PROCHAINE FOIS


//RAN EXPO NE RENVOIE PAS DES NOMBRES ENTIERS !!!!!!!!!!!!!!!!!!
// CALCUL DU TPS D ATT FAIT DES SOMMES DE INT ET FLOAT IL FAUT REGLER L ERREUR

//************************************STRUCTURES*************************************************************



/* Structure de voiture*/



// Structure de liste de voiture //

typedef struct {    // il y a une liste par direction
    Voiture *tete;
}ListeVoitures;



// Structure feu de circulation

typedef struct{
    int val; // prend [0,10] si c'est vert et [10,13] si c'est jaune si c est rouge [13,33] pour pouvoir savoir on on est dans les feux
}feu;




//******************************************************FONCTIONS*************************************************



// fonction qui cree une voiture et lui assigne son numero

void creation_voiture(int *n,Voiture *voit){  // n est le numero de voiture
    voit->Id=(*n)+1;
}


//_________________________________________________________________________________________________________



// Loi exponentielle

double ran_expo(double lambda){ // génère un nombre aléatoire de distribution exponentielle
    double u;
    srand((unsigned)time(NULL));
    u = rand() / ( RAND_MAX + 1.0);
    return floor(-log(1- u) / lambda*100);
}

int ran_expo_1(float lambda){ // génère un nombre aléatoire de distribution exponentielle
    float u;
    srand((unsigned)time(NULL));
    u = (float) rand() /(float) (RAND_MAX + 1.0);
    return (int)( -logf(1- u) / lambda*100);
}



//___________________________________________________________________________________________________________-


// Calcul du temps d'arrivee (il doit y avoir une variable externe qui nous permet de lancer la fct ou nn

int calcul_tps_arrivee(Voiture *voit,float lambda,int temps){ // calcule le tps d'arrivee d une voiture
    int a;
    a= ran_expo_1(lambda);
    (*voit).Tps_arrivee=a+ temps;
}

//__________________________________________________________________________________________________________

// Fonction qui change la lumière du feu

void change_feu(feu *feu){
    feu->val=(1-feu->val==1);
}



//________________________________________________________________________________________________________________



// fonction qui calcule la longueur d'une liste chainee

int longueur_liste_voitures(ListeVoitures list) {
    int i = 0;
    Voiture *curseur=list.tete;
    while (curseur!=0){
        curseur=(*curseur).suiv;
        i++;
    }
    return i;
}


//________________________________________________________________________________________________________________



// fonction qui prend en compte le feu

int prise_en_compte_du_feu(int feu,int long_list){
    int ajout=0;
    if (feu>13)
        ajout=33-feu;
    else if ((feu<=13)&&(feu+long_list>13))
        ajout=20;
    else if ((feu<=13)&&(feu+long_list<=13))
        ajout=0;
    return ajout;
}



//________________________________________________________________________________________________________________


// fonction qui calcule le temps d'attente AU TEMPS D ARRIVEE DE LA VOITURE

int calcul_tps_attente(ListeVoitures *list,int *feu){
    int long_list=longueur_liste_voitures(*list);
    return long_list+prise_en_compte_du_feu(*feu,long_list);

}



//____________________________________________________________________________________________________________________



// Fonction pour enlever une voiture (celle juste devant le feu)

void enleve_voiture(ListeVoitures *LV){
    Voiture *courante;
    courante=(Voiture *) malloc(sizeof(Voiture));
    courante=LV->tete;
    LV->tete=courante->suiv;

}


//___________________________________________________________________________________________________________________


void ajoute_voiture(ListeVoitures *LV,Voiture *voit){
    Voiture *courant;
    courant = (Voiture *) malloc(sizeof(Voiture));
    courant=LV->tete;
    if (courant !=NULL) {
        while (courant->suiv != NULL) {
            courant = courant->suiv;
        }
        courant->suiv = voit;
        voit->suiv = NULL;
    }
    else{
        LV->tete=voit;
        voit->suiv=NULL;
    }
}

//___________________________________________________________________________________________________________________

void calcul_tps_passage(Voiture *voit) {
    voit->Duree_dattente = voit->Tps_arrivee + voit->Duree_dattente;
}




void simulation_traffic_1(int nb_tours,FILE *fichier) {
    printf("**********ALGORITHME DE SIMULATION D'UN CROISEMENT DE TRAFFIC***************\n\n");
    float lambda = 100.9;
    int numero = 0;   // numero est le numero que l'on va attribuer a chaque voiture, c est inutile
    int voiture_cree_ou_pas = 0; // elle permet de savoir si l'on peut creer une voiture ou pas elle prend
    ListeVoitures *list;
    list = (ListeVoitures *) malloc(sizeof(ListeVoitures));
    Voiture *voit;
    voit = (Voiture *) malloc(sizeof(Voiture));
    Voiture tout_voitures[nb_tours];
    list->tete = NULL; // au debut la liste est vide
    int x;
    int tps_spawn = 0;  // cette variable est explique quand on l'utilise
    int feu = 0; // le feu commence au vert
    int numero1;
    for (int t = 0; t < nb_tours; t++) { // la boucle decrit le temps en tours
        printf("************************TOUR %d***********************\n\n", t);
        if (voiture_cree_ou_pas == 0) {   // on cree une voiture si uniquement y en a pas deja une qui est cree
            creation_voiture(&numero, &(tout_voitures[t]));
            numero++;
            voiture_cree_ou_pas = 1; // si une voiture est cree cette variable prend la valeur 1
            calcul_tps_arrivee(&(tout_voitures[t]), lambda, t + 1);
            printf(" VOITURE CREE \n NOMBRE DE VOITURES CREES:\n : %d,\n tps d'arrivee de la voiture ajoutée= %d \n\n",
                   tout_voitures[t].Id, (tout_voitures[t]).Tps_arrivee);
            tps_spawn = tout_voitures[t].Tps_arrivee; // tps_spawn est une varibale qui a juste une utilité pratique

        }
        if (t == tps_spawn) {  // dans le cas ou on arrive au tour ou l'on doit poser la voiture que l'on a cree
            tout_voitures[t].Duree_dattente = calcul_tps_attente(list, &feu); // on ajoute son tps d attente
            tout_voitures[t].Tps_arrivee=tps_spawn;
            tout_voitures[t].Tps_passage=tout_voitures[t].Duree_dattente +tps_spawn;
            ajoute_voiture(list, &(tout_voitures[t]));// on ajoute la voiture dans le circuit
            printf("VOITURE AJOUTEE AU CIRCUIT:\n numero de voiture = %d \n\n", tout_voitures[t].Id);
            x = longueur_liste_voitures((*list));
            ecriture_voit_fichier(&(tout_voitures[t]), fichier, "statistiques.txt", x);
            printf("LONGUEUR LISTE %d \n", x);


            voiture_cree_ou_pas = 0; // on peut de nv creer des voitures
        }
        if ((feu < 14) && (list->tete != NULL)) {  // les voitures avancent dans le feu vert
            printf("VOITURE ENLEVEE AU CIRCUIT \n numero de voiture= %d \n\n", list->tete->Id);
            enleve_voiture(list);
        }
        feu++; // le feu s incremente a chaque tour
        feu = feu % 33;

    }
}




int main() {
    FILE *fichier;
    FILE *fichier2;
    simulation_traffic_1(300,fichier);
    calcul_moy_fichier(fichier,"statistiques.txt");
    calcul_max_file(fichier2,fichier,"maximum_file.txt","statistiques.txt");
  return 0;
}