#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "fichier_feu.h"


#define LAMBDA
#define NBR_CYCLES






/*Fonction créant le nom du fichier pour les différencier*/

char *nom_fichier(int num_fich)
{
 static char nomfichier [30]; 
 sprintf(nomfichier,"indic_perf %d.txt",num_fich);
 return nomfichier;
}






 

//--------------------------------------

/*Fonction écrivant tous les temps d'1 voiture dans le fichier créé*/
void ecriture_voit_fichier(Voiture *Voit, FILE *fichier,char *nomfichier,int long_list)
{
 fichier=fopen(nomfichier,"a+");
    fprintf(fichier, "%d\n",long_list);
 //fprintf(fichier, "%d %d %d %d\n",Voit->Tps_arrivee,Voit->Duree_dattente,Voit->Tps_passage,long_list);
 fclose(fichier);
}

//---------------------------------------

/*Fonction calculant la moyenne de la duree d'attente des voitures une fois le fichier rempli*/
 void calcul_moy_fichier(FILE *fichier,char *nomfichier)
 {
  fichier =fopen(nomfichier,"a+");
 
  int TPS_ARR;
  int TPS_ATT;
  int TPS_PASS;
  int long_list;
  float sum_tps_att=0;
  float sum_long_list=0;
  float cmpt=0;

  while(fscanf(fichier,"%d %d %d %d\n",&TPS_ARR,&TPS_ATT,&TPS_PASS,&long_list)==4)
   {
    sum_long_list=sum_long_list+ long_list;
    sum_tps_att=sum_tps_att+TPS_ATT;
    cmpt++;
   } 
 
   float moy_att=(sum_tps_att/cmpt);
  float moy_list=(sum_long_list/cmpt);
   fprintf(fichier, "Le temps d'attente moyen de la file est :%.2f\n",moy_att);
     fprintf(fichier, "La longueur moyenne de la file est  :%.2f\n",moy_list);
     fclose(fichier);
 }



/*Fonction calculant le max de voiture dans la file dans un autre fichier*/
void calcul_max_file(FILE *fichier1,FILE *fichier2,char *nomfichier,char *nomfichier2)
{
    fichier1 =fopen(nomfichier,"a+");
    fichier2 =fopen(nomfichier2,"a+");

    int TPS_ARR;
    int TPS_ATT;
    int TPS_PASS;
    int Nb_voit_file;

    int max=0;

    while(fscanf(fichier2,"%d %d %d %d\n",&TPS_ARR,&TPS_ATT,&TPS_PASS,&Nb_voit_file)==4)
    {
        if (Nb_voit_file>max)
        {
            max=Nb_voit_file;
        }
    }

    fprintf(fichier2,"Nombre de voiture max dans la file : %d\n",max);
    fprintf(fichier1,"Nombre de voiture max dans la file : %d\n",max);//inscription du max dans le 1er fichier également
    fclose(fichier2);
    fclose(fichier1);
}


// ATTENTION ! : une fois le fichier ouvert on peut faire qu'un type d'action à la fois !
		  // on ouvre donc une fois le fichier pour écrire PUIS on le ferme PUIS on le réouvre pour lire





