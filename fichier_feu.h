typedef struct _Voiture {int Id; int Tps_arrivee; int Duree_dattente;
	                 int Tps_passage; struct _Voiture *suiv;} Voiture;
char *nom_fichier(int num_fich);
void ecriture_voit_fichier(Voiture *Voit, FILE *fichier,char *nomfichier,int long_list);
void calcul_moy_fichier(FILE *fichier,char *nomfichier);
void calcul_max_file(FILE *fichier1,FILE *fichier2,char *nomfichier,char *nomfichier2);



