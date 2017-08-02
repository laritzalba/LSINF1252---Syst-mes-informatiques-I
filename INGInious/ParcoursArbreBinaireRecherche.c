
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
[Beta] Parcours d'un arbre binaire de recherche
On souhaite parcourir un arbre binaire de recherche. Un arbre de recherche binaire est une structure de 
données où chaque nœud possède une clé et une valeur. En outre, chaque nœud peut avoir 2 nœuds fils : 
un à gauche dont la clé est toujours inférieure à la sienne, et un à droite dont la clé est toujours 
supérieure à la sienne. Autrement dit si vous êtes à un nœud dont la clé vaut 10 et que vous cherchez un 
nœud dont la clé vaut 5, vous savez que vous devez descendre à gauche pour espérer trouver un éventuel nœud
 dont la clé vaut 5.

 Écrivez une fonction int has_key(Node root, int key) qui vérifie si l'arbre binaire dont le sommet est le 
 nœud root possède un nœud dont la clé vaut key et renvoie 1 si oui, renvoie 0 sinon.

Écrivez une fonction int compare(Node root_a, Node root_b) qui vérifie si les 2 arbres binaires passés en argument
sont identiques (ils ont la même structure et tous les nœuds possèdent la même paire clé/valeur). Renvoie 1 si les
arbres sont identiques, 0 sinon. Indice : pensez récursivement.
*/

typedef struct BSTreeNode {
    int key;
    int value;

    struct BSTreeNode *left;
    struct BSTreeNode *right;
} Node;



int has_key(Node root, int key) {
    if ((root.key) == key) return 1;
    if (root.left==NULL && root.right==NULL) return 0;
            if (key < root.key){
            Node TempLeft;
            TempLeft.key =   root.left->key;
            TempLeft.value = root.left->value;
            TempLeft.right = root.left->right;
            TempLeft.left =  root.left->left;
            return has_key( TempLeft, key);            
        } else {
            Node TempRight;
            TempRight.key =   root.right->key;
            TempRight.value = root.right->value;
            TempRight.right = root.right->right;
            TempRight.left =  root.right->left;
            return has_key( TempRight, key);
        }
}


int compare(Node root_a, Node root_b) {
if (root_a.key == root_b.key  && root_a.value == root_b.value ) {
    if (root_a.left== NULL  && root_a.right==NULL && root_b.left == NULL && root_b.right == NULL){
        return 1;
    } else if (root_a.left!=NULL && root_a.right!=NULL && root_b.left!=NULL && root_b.right!=NULL){ 
                Node TempLeftA;
                TempLeftA.key =   root_a.left->key;
                TempLeftA.value = root_a.left->value;
                TempLeftA.right = root_a.left->right;
                TempLeftA.left =  root_a.left->left;

                Node TempLeftB;
                TempLeftB.key =   root_b.left->key;
                TempLeftB.value = root_b.left->value;
                TempLeftB.right = root_b.left->right;
                TempLeftB.left =  root_b.left->left;
                
                Node TempRightA;
                TempRightA.key =   root_a.right->key;
                TempRightA.value = root_a.right->value;
                TempRightA.right = root_a.right->right;
                TempRightA.left =  root_a.right->left;

                Node TempRightB;
                TempRightB.key =   root_b.right->key;
                TempRightB.value = root_b.right->value;
                TempRightB.right = root_b.right->right;
                TempRightB.left =  root_b.right->left;
                return (compare( TempLeftA, TempLeftB) & compare( TempRightA, TempRightB)); 
            }else return 0;  
}else return 0;
}


int main(int argc, char **argv){

printf("tests Main\n");
Node root_a;
root_a.key= 3;
root_a.value=300;

root_a.right= (struct BSTreeNode *) malloc (sizeof(struct BSTreeNode));
root_a.right->key=4;
root_a.right->value=400;
root_a.right->right=NULL;
root_a.right->left=NULL;

root_a.left= (struct BSTreeNode *) malloc (sizeof(struct BSTreeNode));
root_a.left->key=2;
root_a.left->value=200;
root_a.left->right=NULL;
root_a.left->left=NULL;



Node root_b;
root_b.key= 3;
root_b.value=300;

root_b.right= (struct BSTreeNode *) malloc (sizeof(struct BSTreeNode));
root_b.right->key=4;
root_b.right->value=400;
root_b.right->right=NULL;
root_b.right->left=NULL;

root_b.left= (struct BSTreeNode *) malloc (sizeof(struct BSTreeNode));
root_b.left->key=2;
root_b.left->value=200;
root_b.left->right=NULL;
root_b.left->left=NULL;

int r= has_key( root_a, 4);
printf("Binary tree has_key ?  answer= %i\n", r);


int r2= compare( root_a, root_b);
printf("Are binary tree equals? answer= %i", r2);

printf("\n END MAIN \n");
return 0;
}