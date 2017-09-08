#ifndef _MATRIX_H
#define _MATRIX_H

/* struct matrix
 * Structure représentant une matrice tableau.
 *
 * @elems tableau à deux dimensions représentant la matrice.
 * @nlines contient le nombre de lignes de la matrice.
 * @ncols contient le nombre de colonnes de la matrice.
 *
 * Le nombre de lignes @elems doit être égal à @nlines.
 * Le nombre de colonnes de @elems doit être égal à @ncols.
 * La valeur @elems[i][j] correspond à l'élément a(i,j) de la matrice.
 */
struct matrix {
	double** elems;
	unsigned int nlines;
	unsigned int ncols;
};

/* struct elem
 * Structure représentant une valeur de la matrice, faisant partie d'une liste
 * simplement chaînée.
 *
 * @next pointe vers l'élément suivant de la liste. NULL si dernier élément.
 * @j contient le numéro de colonne de l'élément (>= 0).
 * @value contient la valeur courante.
 */
struct elem {
	struct elem *next;
	unsigned int j;
	double value;
};

/* struct line
 * Structure représentant une ligne d'une matrice creuse, faisant partie d'une
 * liste simplement chaînée.
 *
 * @next pointe vers l'élément suivant de la liste. NULL si dernier élément.
 * @elems pointe vers la tête d'une liste simplement chaînée contenant les
 *	  valeurs de la ligne, dans un ordre d'indices croissant.
 * @i contient le numéro de ligne courant (>= 0).
 *
 * Comme nous sommes dans une matrice creuse, @elems ne contient pas forcément
 * autant d'éléments qu'il y a de colonnes. Les éléments manquants ont donc
 * une valeur de 0. @elems ne peut jamais valoir NULL (autrement dit, quand
 * une struct line existe, elle doit contenir au moins un élément différent
 * de 0).
 */
struct line {
	struct line *next;
	struct elem *elems;
	unsigned int i;
};

/* struct sp_matrix
 * Structure représentant une matrice creuse.
 *
 * @lines pointe vers la tête d'une liste simplement chaînée contenant les
 *	  lignes de la matrice dans un ordre d'indices croissant.
 * @precision contient la valeur absolue en dessous de laquelle un élément 
 *            doit être considéré comme nul (zéro)
 * @nlines contient le nombre de lignes de la matrice.
 * @ncols contient le nombre de colonnes de la matrice.
 *
 * Sachant que la matrice est creuse, le nombre d'éléments de la liste @lines
 * peut être inférieur à @nlines. Il ne peut bien entendu jamais être supérieur
 * à @nlines. Si une ligne n'est pas présente dans @lines, cela signifie que
 * tous ses éléments valent 0. Lorsque @lines vaut NULL, cela signifie que tous
 * les éléments de la matrice valent 0.
 */
struct sp_matrix {
	struct line *lines;
        double precision;
	unsigned int nlines;
	unsigned int ncols;
};

/* matrix_init
 * Créer une nouvelle matrice tableau.
 *
 * @nlines: nombre de lignes
 * @ncols: nombre de colonnes
 * @return: pointeur vers la matrice ou NULL si erreur
 *
 * Préconditions: @nlines > 0 && @ncols > 0
 * Postconditions: Les éléments de la nouvelle matrice sont initialisés à 0.
 *		   @m->nlines > 0 && @m->ncols > 0
 */
struct matrix *matrix_init(unsigned int nlines, unsigned int ncols);

/* sp_matrix_init
 * Créer une nouvelle matrice creuse.
 *
 * @precision: précision des élements de la matrice
 * @nlines: nombre de lignes
 * @ncols: nombre de colonnes
 * @return: pointeur vers la matrice ou NULL si erreur
 *
 * Préconditions: @nlines > 0 && @ncols > 0
 * Postconditions: Les éléments de la nouvelle matrice sont initialisés à 0.
 *		   @m->nlines > 0 && @m->ncols > 0
 */
struct sp_matrix *sp_matrix_init (double precision, unsigned int nlines, unsigned int ncols);

/* matrix_free
 * Libère la mémoire allouée à une matrice tableau.
 *
 * @matrix: Matrice à libérer.
 *
 * Préconditions: /
 * Postconditions: La mémoire de @matrix est libérée.
 */
void matrix_free(struct matrix *matrix);

/* sp_matrix_free
 * Libère la mémoire allouée à une matrice creuse.
 *
 * @matrix: Matrice à libérer.
 *
 * Préconditions: /
 * Postconditions: La mémoire de @matrix est libérée.
 */
void sp_matrix_free(struct sp_matrix *matrix);

/* matrix_set
 * Définit la valeur d'un élément de la matrice tableau.
 *
 * @matrix: Matrice
 * @i: numéro de ligne
 * @j: numéro de colonne
 * @val: valeur à définir
 * @return: -1 si erreur, 0 sinon
 *
 * Préconditions: 0 <= @i < @matrix->nlines && 0 <= @j < @matrix->ncols
 * Postconditions: L'élément (@i,@j) de la matrice @matrix vaut @val.
 */
int matrix_set(struct matrix *matrix, unsigned int i, unsigned int j, double val);

/* sp_matrix_set
 * Définit la valeur d'un élément de la matrice creuse.
 *
 * @matrix: Matrice
 * @i: numéro de ligne
 * @j: numéro de colonne
 * @val: valeur à définir
 * @return: -1 si erreur, 0 sinon
 *
 * Préconditions: 0 <= @i < @matrix->nlines && 0 <= @j < @matrix->ncols
 * Postconditions: L'élément (@i,@j) de la matrice @matrix vaut @val.
 */
int sp_matrix_set(struct sp_matrix *matrix, unsigned int i, unsigned int j, double val);

/* matrix_get
 * Récupère la valeur d'un élément de la matrice tableau.
 *
 * @matrix: Matrice
 * @i: numéro de ligne
 * @j: numéro de colonne
 * @return: valeur de l'élément (@i,@j) de la matrice
 *
 * Préconditions: 0 <= @i < @matrix->nlines && 0 <= @j < @matrix->ncols
 * Postconditions: @matrix est inchangé.
 */
double matrix_get(const struct matrix *matrix, unsigned int i, unsigned int j);

/* sp_matrix_get
 * Récupère la valeur d'un élément de la matrice creuse.
 *
 * @matrix: Matrice
 * @i: numéro de ligne
 * @j: numéro de colonne
 * @return: valeur de l'élément (@i,@j) de la matrice
 *
 * Préconditions: 0 <= @i < @matrix->nlines && 0 <= @j < @matrix->ncols
 * Postconditions: @matrix est inchangé.
 */
double sp_matrix_get(const struct sp_matrix *matrix, unsigned int i, unsigned int j);

/* matrix_add
 * Additionne deux matrices tableau.
 *
 * @m1: premier opérande
 * @m2: deuxième opérande
 * @return: Matrice tableau résultant de l'addition de @m1 et @m2,
 *	    ou NULL si erreur
 *
 * Préconditions: @m1 != NULL && @m2 != NULL
 * Postconditions: @m1 et @m2 inchangés.
 */
struct matrix *matrix_add(const struct matrix *m1, const struct matrix *m2);

/* sp_matrix_add
 * Additionne deux matrices creuses.
 *
 * @m1: premier opérande
 * @m2: deuxième opérande
 * @return: Matrice creuse résultant de l'addition de @m1 et @m2,
 *	    ou NULL si erreur
 *
 * Préconditions: @m1 != NULL && @m2 != NULL
 * Postconditions: @m1 et @m2 inchangés.
 */
struct sp_matrix *sp_matrix_add(const struct sp_matrix *m1, const struct sp_matrix *m2);

/* matrix_transpose
 * Calcule la transposée d'une matrice tableau.
 *
 * @matrix: opérande
 * @return: Matrice tableau étant la transposée de @matrix
 *
 * Préconditions: @matrix != NULL
 * Postconditions: @matrix est inchangé.
 */
struct matrix *matrix_transpose(const struct matrix *matrix);

/* sp_matrix_transpose
 * Calcule la transposée d'une matrice creuse.
 *
 * @matrix: opérande
 * @return: Matrice creuse étant la transposée de @matrix
 *
 * Préconditions: @matrix != NULL
 * Postconditions: @matrix est inchangé.
 */
struct sp_matrix *sp_matrix_transpose(const struct sp_matrix *matrix);


/* matrix_mult
 * Multiplie deux matrices tableau.
 *
 * @m1: premier opérande
 * @m2: deuxième opérande
 * @return: Matrice tableau résultant de la multiplication de @m1 et @m2,
 *	    ou NULL si erreur
 *
 * Préconditions: @m1 != NULL && @m2 != NULL
 * Postconditions: @m1 et @m2 inchangés.
 */
struct matrix *matrix_mult(const struct matrix *m1, const struct matrix *m2);

/* sp_matrix_mult
 * Multiplie deux matrices creuses.
 *
 * @m1: premier opérande
 * @m2: deuxième opérande
 * @return: Matrice creuse résultant de la multiplication de @m1 et @m2,
 *	    ou NULL si erreur
 *
 * Préconditions: @m1 != NULL && @m2 != NULL
 * Postconditions: @m1 et @m2 inchangés.
 */
struct sp_matrix *sp_matrix_mult(const struct sp_matrix *m1, const struct sp_matrix *m2);

/* matrix_to_sp_matrix
 * Transforme une matrice tableau en une matrice creuse.
 *
 * @matrix: matrice tableau à transformer
 * @precision: précision des éléments de la nouvelle matrice creuse
 * @return: matrice creuse correspondante à @matrix ou NULL si erreur
 *
 * Préconditions: matrix != NULL
 * Postconditions: matrix est inchangée && 0 < @precision
 */
struct sp_matrix *matrix_to_sp_matrix (const struct matrix *matrix, double precision);

/* sp_matrix_to_matrix
 * Transforme une matrice creuse en une matrice tableau.
 *
 * @matrix: matrice creuse à transformer
 * @return: matrice tableau correspondante à @matrix ou NULL si erreur
 *
 * Préconditions: matrix != NULL
 * Postconditions: matrix est inchangée
 */
struct matrix *sp_matrix_to_matrix (const struct sp_matrix *matrix);

/* matrix_save
 * Sauvegarde une matrice tableau dans un fichier
 *
 * @matrix: matrice tableau à sauvegarder
 * @path: chemin du fichier vers lequel sauvegarder la matrice
 * @return: -1 si erreur, 0 sinon
 *
 * Préconditions: matrix != NULL
 * Postconditions: Le fichier @path contient la matrice tableau sauvegardée
 */
int matrix_save (const struct matrix *matrix, char *path);

/* sp_matrix_save
 * Sauvegarde une matrice creuse dans un fichier
 *
 * @matrix: matrice creuse à sauvegarder
 * @path: chemin du fichier vers lequel sauvegarder la matrice
 * @return: -1 si erreur, 0 sinon
 *
 * Préconditions: matrix != NULL
 * Postconditions: Le fichier @path contient la matrice creuse sauvegardée
 */
int sp_matrix_save (const struct sp_matrix *matrix, char *path);

/* matrix_load
 * Charge une matrice tableau à partir d'un fichier
 *
 * @path: chemin du fichier à partir duquel charger la matrice
 * @return: matrice tableau contenue dans le fichier @path, NULL en cas d'erreur
 *
 * Préconditions: path != NULL
 * Postconditions: @path est inchangée
 */
struct matrix *matrix_load (char *path);

/* sp_matrix_load
 * Charge une matrice creuse à partir d'un fichier
 *
 * @path: chemin du fichier à partir duquel charger la matrice
 * @return: matrice creuse contenue dans le fichier @path, NULL en cas d'erreur
 *
 * Préconditions: path != NULL
 * Postconditions: @path est inchangée
 */
struct sp_matrix *sp_matrix_load (char *path);

#endif
