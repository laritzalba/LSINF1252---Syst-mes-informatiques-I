
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
            return has_key( *(root.left), key);            
        } else {            
            return has_key( *(root.right), key);
        }
}


int compare(Node root_a, Node root_b) {
if (root_a.key == root_b.key  && root_a.value == root_b.value ) {
    if (root_a.left== NULL  && root_a.right==NULL && root_b.left == NULL && root_b.right == NULL){
        return 1;
    } else if (root_a.left!=NULL && root_a.right!=NULL && root_b.left!=NULL && root_b.right!=NULL){ 
                return (compare( *(root_a.left), *(root_b.left)) && compare( *(root_a.right), *(root_b.right))); 
            }else return 0;  
}else return 0;
}

int main(int argc, char **argv){

printf("tests Main\n");

Node *tree_a= (Node *) malloc (sizeof(Node));
tree_a->key=3;
tree_a->value=300;
tree_a->right= (struct BSTreeNode *) malloc (sizeof(struct BSTreeNode));
tree_a->right->key=4;
tree_a->right->value=400;
tree_a->right->right=NULL;
tree_a->right->left=NULL;
tree_a->left= (struct BSTreeNode *) malloc (sizeof(struct BSTreeNode));
tree_a->left->key=2;
tree_a->left->value=200;
tree_a->left->right=NULL;
tree_a->left->left=NULL;

Node *tree_b= (Node *) malloc (sizeof(Node));
tree_b->key= 37;
tree_b->value=300;
tree_b->right= (struct BSTreeNode *) malloc (sizeof(struct BSTreeNode));
tree_b->right->key=4;
tree_b->right->value=400;
tree_b->right->right=NULL;
tree_b->right->left=NULL;
tree_b->left= (struct BSTreeNode *) malloc (sizeof(struct BSTreeNode));
tree_b->left->key=2;
tree_b->left->value=200;
tree_b->left->right=NULL;
tree_b->left->left=NULL;

int t= has_key( *tree_a, 4);
printf("Binary tree has_key ?  answer= %i\n", t);

int t2= compare( *tree_a, *tree_b);
printf("Are binary tree equals? answer= %i", t2);

printf("\n END MAIN \n");
return 0;
}