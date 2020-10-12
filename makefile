main.o : simulation.c fichier_feu.h
	gcc -c simulation.c 
fichier_feu.o : fichier_feu.c fichier_feu.h
	gcc -c fichier_feu.c
simulation : simulation.o fichier_feu.o
	gcc simulation.o fichier_feu.o -o simulation -lm
