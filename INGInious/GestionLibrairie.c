#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*
[Beta] Gestion d'une librairie
On souhaite gérer le catalogue d'une librairie dans lequel chaque livre est identifié par son auteur 
et son titre. La structure de données choisie est la suivante : il y a une liste chaînée d'auteurs dont 
chaque élément pointe vers une liste chaînée d'ouvrages.

Écrivez une fonction cellAuteur *existe(cellAuteur *librairie, char *strAuteur) qui teste si un auteur 
existe dans la liste librairie et dans ce cas renvoie un pointeur sur sa cellule de la liste (et NULL sinon).

Écrivez une fonction int compteOuvrage(cellAuteur *librairie, char *strAuteur) qui compte le nombre de 
livres d'un auteur dans la liste librairie.

Écrivez une fonction void add(cellAuteur *librairie, char *strAuteur, char *strTitre) qui ajoute dans le 
catalogue un livre de l'auteur indiqué. L'auteur existe dans le catalogue. Un même livre ne peut pas être 
présent 2 fois dans la catalogue.

Écrivez une fonction void supprimer(cellAuteur **librairie, char *strAuteur) qui supprime du catalogue un 
auteur et tous ses livres. L'auteur existe dans le catalogue.

Vous avez accès aux fonctions de string.h.
*/



typedef struct cellAuteur {
    char *auteur;
    struct cellLivre *Livres;
    struct cellAuteur *next;
} cellAuteur;

typedef struct cellLivre {
    char *titre;
    struct cellLivre *suiv;
} cellLivre;


cellAuteur *existe(cellAuteur *librairie, char *strAuteur) {
      if (librairie == NULL) return NULL;
      cellAuteur *current= librairie;
      while(current!=NULL){
       if (strcmp(current->auteur, strAuteur)==0)
           return current;  
       current=current->next;
      } 
    return NULL;    
}

int compteOuvrage(cellAuteur *librairie, char *strAuteur){
    if (librairie == NULL) return 0;

    int count=0;
    cellAuteur *current= librairie;
    while(current!=NULL){

        if (strcmp(current->auteur, strAuteur)==0){
            cellLivre *currentBook=current->Livres;
            while(currentBook!=NULL){
             count++;
             currentBook= currentBook->suiv;
            }
        }            
       current=current->next;
    }
return count;
}

void add(cellAuteur *librairie, char *strAuteur, char *strTitre){
    if (librairie==NULL) {/* on fais rien */ }
    else {
    cellAuteur * thisAuteur= existe(librairie, strAuteur);
    if (thisAuteur!= NULL){
        cellLivre *currentBook= (thisAuteur->Livres);
        cellLivre * prevBook= NULL;
        while((currentBook)!=NULL){
            if (strcmp(currentBook->titre, strTitre)==0){
                return ;// le livre est deja dans le livrerie
            }
            prevBook= currentBook;
            currentBook= (currentBook->suiv);
        }

        // on ajoute le new livre
        cellLivre *newBook = (cellLivre *) malloc (sizeof(cellLivre));
        if (newBook == NULL) return ; // malloc a echoue
        newBook->titre = strTitre;
        newBook->suiv = NULL;
        if (prevBook==NULL){ // empty livres
            (thisAuteur->Livres)= newBook;
            return ;
        }else {
            prevBook->suiv= newBook;
        }
    }
    }
}


void supprimer(cellAuteur **librairie, char *strAuteur){
if (*librairie == NULL) { /* */ }
cellAuteur *current= (*librairie) ;
cellAuteur *prev= NULL;
while(current!=NULL){
    if (strcmp((current->auteur), strAuteur)==0){
        cellLivre *currentBook=(current->Livres);
        cellLivre *prevBook=NULL;
        while(currentBook!=NULL){
            if (prevBook !=NULL){
                (prevBook->suiv)= NULL;
                free(prevBook);
            }
            prevBook= currentBook;
            currentBook= currentBook->suiv;
        }
        if (prevBook !=NULL){
            free(prevBook);
        }
        if (prev==NULL){ // is head
            *librairie= (current->next);
            free(current);
            return ;
        }
        if((current->next)==NULL){ // is tail
            prev=NULL;
            free(current);
            return ;
        }
        // in the middle
        prev= current->next;
        current->next=NULL;
        free(current);
        return ;
    }            
    prev = current;
    current= current->next;       
    }
}


//main
int main(int argc, char **argv){
printf("tests Main\n");

cellAuteur *Math= (cellAuteur *) malloc (sizeof (cellAuteur));
Math->auteur= "Math";
Math->next=NULL;
Math->Livres=NULL;

cellAuteur *BSPO= (cellAuteur *) malloc (sizeof (cellAuteur));
BSPO->auteur= "Nancy";
BSPO->next=Math;
BSPO->Livres=NULL;

cellAuteur *BST= (cellAuteur *) malloc (sizeof (cellAuteur));
BST->auteur= "Laritza";
BST->next=BSPO;
BST->Livres=NULL;



cellAuteur *resulSearch;
resulSearch= existe(BST, "Laritza");
printf("%s\n", resulSearch->auteur);

add( BST, "Laritza", "CO");
printf("is NULL BST%i\n", BST->Livres ==NULL);
add( BST, "Laritza", "CO");
add( BST, "Laritza", "SI");
add( BST, "Laritza", "SO");
resulSearch= existe(BST, "Laritza");
if (resulSearch!=NULL)
printf("%s\n", resulSearch->auteur);

printf("cantidad de obras %i\n", compteOuvrage(BST, "Laritza"));
supprimer(&BST, "Laritza");

resulSearch= existe(BST, "Laritza");
if (resulSearch!=NULL)
printf("%s\n", resulSearch->auteur);


/////////

cellAuteur *resulSearchBSPO;
resulSearchBSPO= existe(BSPO, "Nancy");// lowercase ??/
if (resulSearchBSPO!=NULL)
printf("%s\n", resulSearchBSPO->auteur);

printf("is NULL BST%i\n", BSPO->Livres ==NULL);
add( BSPO, "Nancy", "CO");
printf("is NULL BST%i\n", BSPO->Livres ==NULL);
add( BSPO, "Nancy", "CO");
printf("is NULL BST%i\n", BSPO->Livres ==NULL);
add( BSPO, "Nancy", "SI");
add( BSPO, "Nancy", "SO");
//printf("%s\n", BST->Livres->suiv->suiv->titre);
resulSearchBSPO= existe(BSPO, "Nancy");
if (resulSearchBSPO!=NULL)
printf(" exist %s\n", resulSearchBSPO->auteur);

printf("cantidad de obras %i\n", compteOuvrage(BSPO, "Nancy"));
supprimer(&BSPO, "Nancy");

resulSearchBSPO= existe(BSPO, "Nancy");
if (resulSearchBSPO!=NULL)
printf("%s\n", resulSearchBSPO->auteur);



printf("\n END MAIN \n");
return 0;
}
