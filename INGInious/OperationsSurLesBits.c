
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


/*

[Beta] Opérations sur les bits
On souhaite effectuer des opérations spécifiques sur certains bits d'un entier non-signé de 32 bits. Lorsque l'on parle de position, l'indice 0 correspond au bit le plus faible, et 31 au bit le plus fort. Dans cet exercice, un unsigned char représente toujours un seul bit et ne pourra donc que prendre les valeurs numériques 0 ou 1 (et non '0' et '1')

Écrivez une fonction unsigned char get_bit(unsigned int x, unsigned int pos) qui renvoie le bit à la position pos de x.

Écrivez une fonction unsigned int set_bit(unsigned int x, unsigned int pos, unsigned char value) qui met le bit à la position pos de x à la valeur value.

Écrivez une fonction unsigned char get_3_leftmost_bits(unsigned int x) qui renvoie les 3 bits les plus à gauches de x. Par exemple, si on a la séquence 11011001, la fonction doit renvoyer la valeur correspondant à 00000110.

Écrivez une fonction unsigned char get_4_rightmost_bits(unsigned int x) qui renvoie les 4 bits les plus à droite de x.

Écrivez une fonction unsigned int unset_last_bit(unsigned int x) qui met à 0 le premier bit de poids fort à 1 qu'il trouve, et ne fait rien s'il n'y a pas de bit mis à 1.

Écrivez une fonction unsigned int cycle_bits(unsigned int x, unsigned int n) qui déplace tous les bits de n places vers la gauche selon la formule x[(i+n)%32] = x[i] où x[i] représente le ième bit de x.

Vous pouvez faire appel aux fonctions get_bit et set_bit dans les autres.
*/

unsigned int get_bit(unsigned int x, unsigned int pos) { 
if (x & (1u << pos)) 
  return 1;
 else 
  return 0;
}


unsigned int set_bit(unsigned int x, unsigned int pos, unsigned char value) {
unsigned char get= get_bit(x,pos);
if(get==1 && value!=1)// if bit dans la position pos est 1 et value !=1
    return (x & ~(1 << pos));
else // if bit dans la position pos est 0 et value !=0
    if(get==0 && value!=0)  
       return (x | (value << pos));
else return x;//  On ne dois pas modifier, c'est le meme valeur.  

}

// example: 11011001, la fonction doit renvoyer la valeur correspondant à 00000110.
unsigned char get_3_leftmost_bits(unsigned int x) {
    return x >> 29;
}

unsigned char get_4_rightmost_bits(unsigned int x) {
    return x & 0xF; // x& 0000 0000 0000 0000 0000 0000 0000 1111
}

unsigned int unset_last_bit(unsigned int x) {
int i;
unsigned int r=x;
for (i=31; i>=0; i--){
    if(get_bit(x,i)==1){        
     r=set_bit(x, i, 0); 
     break;  
    }
}
return r;
}


unsigned int cycle_bits(unsigned int x, unsigned int n) {
int i;
unsigned int r=x;
for (i=0; i<32; i++){
  //x[(i+n)%32] = x[i];
  unsigned char temp = get_bit(x,i);
  r=set_bit(r, (i+n)%32, temp);    
}
return r;
}


/*
Print unsigned int in binary
Pas demande
*/
void toBin(unsigned int byte){    
    int i;
    for(i = 31; 0 <= i; i --){
        printf("%i", get_bit(byte,i));
        if ((i % 4) == 0)
        printf("  ");
    } 
    printf("\n");
}

int main(int argc, char **argv){

printf("tests Main\n");
unsigned int n=10;
toBin(n);
toBin( cycle_bits(n, 25));

printf("\n END MAIN \n");
return 0;
}