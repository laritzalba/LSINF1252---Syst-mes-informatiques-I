#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
[Beta] Tri par insertion
On désire implémenter un algorithme de tri par insertion sur un tableau de N entiers,
 le tableau et sa taille étant passés en argument.

L'algorithme de tri est le suivant : Pour chaque élément d'indice i (i variant de 1 à N-1)

cet élément devient la clé
on la compare avec l'élément d'indice i-1
si la clé est plus petite, on les échange et on recommence la comparaison avec l'élément 
précédent (d'indice i-2) et ainsi de suite, tant que la clé est plus petite que l'élément 
qui lui précède (ou qu'on est revenu au début du tableau)
quand la clé est à sa place (c'est-à-dire qu'elle est plus grande que ou égale à l'élément
 qui lui précède), la boucle intérieure est finie et on passe à l'élément d'indice i+1.
*/


void tri(int T[], int taille) {
  int i;
  int key;
    for (i=0; i<taille; i++){
        key= T[i];
        int j=i-1;
        while( (j>=0) && T[j]>key){
            T[j+1]=T[j];
            j=j-1;
        }
        T[j+1]=key;
    }
}