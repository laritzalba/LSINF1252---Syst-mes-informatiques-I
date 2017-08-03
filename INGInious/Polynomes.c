#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
[Beta] Polynômes
On souhaite gérer des polynômes réels de degré inférieur ou égal à 10 en utilisant la structure suivante :

typedef struct { double coeff[10]; } poly;

qui servira à représenter le polynôme où coeff[0] est le coefficient du terme indépendant, coeff[1] le
coefficient du terme en x, etc.
Écrivez une fonction double eval(poly *P, double x) qui calcule la valeur du polynôme P au point x. 
On pourra se servir de la formule de Horner : P(x) = ((...(a_9*x + a_8)*x + a_7)*x + ...)x + a_1)*x + a_0 où a_i est coeff[i].

Écrivez une fonction void derivee(poly *P, poly *Pderiv) qui inscrit dans Pderiv la dérivée du polynôme P.

Écrivez une fonction double racine(poly *P, double x0) qui calcule via la méthode de Newton la racine du 
polynôme P. La méthode est la suivante : on part d'un point initial, et on construit une suite de points qui
 se rapprochent de la racine en calculant à chaque étape un nouveau point à partir de la valeur du polynôme 
 et de sa dérivée : x_n+1 = x_n - P(x_n)/P'(x_n). La fonction s'arrête lorsque abs(P(x_n)) < 0.0001. 
 On suppose que le calcul converge toujours vers une racine.
*/

typedef struct { 
    double coeff[10]; 
} poly;

double eval(poly *P, double x) {
    double value=0;
    int i;
    double temp=x;
    value= ((P->coeff)[0])+ x * ((P->coeff)[1]);
    for(i=2; i<10; i++){
      temp = temp*x;
      value =value+ (temp*((P->coeff)[i]));
    }
    return value;
}

void derivee(poly *P, poly *Pderiv);

double racine(poly *P, double x0);




//main
int main(int argc, char **argv){
printf("tests Main\n");

poly *polynome= (poly *) malloc (sizeof(poly));
(polynome->coeff)[0]=8;
(polynome->coeff)[1]=74;
(polynome->coeff)[2]=56;
(polynome->coeff)[3]=13;
(polynome->coeff)[4]=10;
(polynome->coeff)[5]=2;
(polynome->coeff)[6]=6;
(polynome->coeff)[7]=3;
(polynome->coeff)[8]=8.9;
(polynome->coeff)[9]=9.3;

printf("eval polinome %f\n", eval(polynome, 1.01));

free(polynome);
printf("\n END MAIN \n");
return 0;
}