/**
 * Laritza Cabrera Alba
 *
 */

    #include <stdio.h>
	#include <stddef.h>
	#include <stdlib.h>
	#include <math.h>
	#include "matrix.h"


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
struct matrix * matrix_init(unsigned int nlines, unsigned int ncols){
	if (((int)(nlines)) <= 0  ||  ((int)(ncols)) <= 0 ) return NULL;
	
	 struct matrix *newMatrix= (struct matrix *) malloc( sizeof (struct matrix));
	 if (newMatrix==NULL) return NULL; // if erreur (malloc)

	 newMatrix->elems= malloc(sizeof (double)*nlines);
	 if ((newMatrix->elems)==NULL) return NULL; // if erreur (malloc)
	 unsigned int i;
	 for (i=0; i<nlines; i++){
       ((newMatrix->elems)[i])=calloc(ncols, sizeof(double));
	   if (((newMatrix->elems)[i])==NULL) return NULL; // if erreur (calloc)
	 }

	 newMatrix->nlines= nlines;
	 newMatrix->ncols=ncols;    

return newMatrix;
}


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
struct sp_matrix *sp_matrix_init (double precision, unsigned int nlines, unsigned int ncols){
    if (((int)(nlines)) <=0  ||  ((int)(ncols)) <=0 ) return NULL;
	struct sp_matrix *m = (struct sp_matrix *) malloc(sizeof(struct sp_matrix));
	if (m == NULL) return NULL; // si malloc echoue
	m->nlines = nlines;
	m->ncols = ncols;
	m->precision= fabs(precision);
	m->lines = NULL;
return m;

}

/* matrix_free
 * Libère la mémoire allouée à une matrice tableau.
 *
 * @matrix: Matrice à libérer.
 *
 * Préconditions: /
 * Postconditions: La mémoire de @matrix est libérée.
 */
void matrix_free(struct matrix *matrix){
	if (matrix!=NULL){
		unsigned int i ;
		for (i=0; i<matrix->nlines; i++){
		free((matrix->elems)[i]);
		}
		free(matrix->elems);
		free(matrix);
	}
}

/*
 *@pre : @this_element!=NULL
 *@pre: @this_element a ete liberee
*/
void elements_free( struct elem *this_element ) {
    if (this_element->next != NULL) {
        elements_free( this_element->next );
    }
    free(this_element);
}

/*
 *@pre : @this_line!=NULL
 *@pre: @this_line a ete liberee
*/
void lines_free( struct line *this_line ) {
    if (this_line->next != NULL) {
        lines_free( this_line->next );
    }
    if (this_line->elems != NULL) {
        elements_free( this_line->elems );
    }
    free(this_line);
}

/* sp_matrix_free
 * Libère la mémoire allouée à une matrice creuse.
 *
 * @matrix: Matrice à libérer.
 *
 * Préconditions: /
 * Postconditions: La mémoire de @matrix est libérée.
 */
void sp_matrix_free(struct sp_matrix *matrix){
    if (matrix!= NULL && matrix->lines != NULL) {
		lines_free(matrix->lines );
	}
    free(matrix);
}

//------------------------------------------------------
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
int matrix_set(struct matrix *matrix, unsigned int i, unsigned int j, double val){
    if (matrix !=NULL &&  0 <= ((int)(i))  &&  0 <=((int)(j))  && i<(matrix->nlines) && j<(matrix->ncols) ){
		(matrix->elems)[i][j]=val;
		return 0;
	}else
        return -1;
}

// ***************************  SP ****************************
// ********************** Elements list ***********************

/*
 *@pre : @j >=0,
 *@pre: Retourne un nouvel element qui sera ajoute a la colnne @j
*/
struct elem *init_elem(unsigned int j) {
    struct elem *this_elem= malloc(sizeof(struct elem));
    if (this_elem==NULL) return NULL; // if malloc echoue
    this_elem->next = NULL;
    this_elem->j=j;
return this_elem;
}

/*
 *@pre : @j >=0, @this_element!=NULL
 *@pre: Retourne l'element de la colnne @j a ete trouve dans cette line ou NULL dans le cas contraire
 */
struct elem *find_elem( struct elem *this_element, unsigned int j ) {
    while (this_element != NULL) {
        if (this_element->j == j) {
            return this_element;
        }
        this_element = this_element->next;
    }
return NULL;
}

/*
 *@pre : @j >=0, @this_line!=NULL
 *@pre: Un nouvel elem a la colonne @j de @this_line a ete ajoute
*/
struct elem *add_elem( struct line *this_line, unsigned int j ) {
	struct elem *this_elem;
    // case 1: empty line
    if (this_line->elems == NULL) {
        this_elem = init_elem( j );
    	if (this_elem == NULL) return NULL; // if malloc echoue
        this_line->elems = this_elem;
        return this_elem;
    }

    // case 2: ALL
    this_elem = this_line->elems;
    struct elem *prev_elem = NULL ;
    while (this_elem != NULL) {
        if (this_elem->j < j) {
            prev_elem = this_elem;
            this_elem = this_elem->next;
        } else break;
    }

    // case 2: at the begining
    if (prev_elem == NULL) {
        prev_elem = init_elem( j );
		if (prev_elem == NULL) return NULL; // if malloc echoue
        prev_elem->next = this_elem;
        this_line->elems = prev_elem;

        return prev_elem;
    }

    // case 2: in the last col
    if (this_elem == NULL) {
        this_elem = init_elem( j );
		if (this_elem == NULL) return NULL; // if malloc echoue
        prev_elem->next = this_elem;

        return this_elem;
    }

    // case 2: elsewhere (i.e. in the middle)
     prev_elem->next = init_elem( j );
	if (prev_elem == NULL) return NULL; // if malloc echoue
    prev_elem->next->next = this_elem;

return prev_elem->next;
}


/*
@pre : this_line!=NULL, this_elem !=NULL
@return: 1 si il y a plus d'un elem dans @this_line apres avoir free  @del_elem"
         et 0 si @this_line n'a plus de elem apres avoir free @del_elem
*/
int del_elem( struct line *this_line,struct elem *del_elem) {
	struct elem *this_elem;
    // case 1: ALL
    this_elem = this_line->elems;
    struct elem *prev_elem = NULL ;
    while (this_elem != NULL) {
        if (this_elem != del_elem) {
            prev_elem = this_elem;
            this_elem = this_elem->next;
        } else break;
    }

    // case 1.2: at the begining
    if (prev_elem == NULL) {
        if (del_elem->next == NULL){ // unique elem
            this_line->elems= NULL;
			free(del_elem);
			return 0;
		}else {  // more than one elem
			this_line->elems = this_elem->next;
			this_elem->next= NULL;
			free(this_elem);
			return 1;
		}
    }

    // case 1.3: in the last col
    if (this_elem == NULL) {
		prev_elem->next = NULL;
        free(this_elem);
		return 1;
    }

    // case 1.4: elsewhere (i.e. in the middle)
    prev_elem->next = this_elem->next;
	this_elem->next=NULL;
    free (this_elem);
return 1;
}

// ********************** Lines list ***********************
/*
 *@pre : @i >=0, @this_line!=NULL
 *@pre: Return la ligne i de la liste de lignes d'une matrice
*/
struct line *find_line( struct line *this_line, unsigned int i ) {
    while (this_line != NULL) {
        if (this_line->i == i) {
            return this_line;
        }
        this_line = this_line->next;
    }

return NULL;
}

/*
 *@pre : @i >=0
 *@pre: return une nouvelle ligne i
*/
struct line *init_line(unsigned int i) {
    struct line *this_line= (struct line *) malloc(sizeof(struct line));
	if (this_line == NULL) return NULL;

    this_line->next = NULL;
    this_line->elems = NULL;
    this_line->i=i;

return this_line;
}

/*
 *@pre : @i >=0 , @m !=NULL
 *@pre: ligne i a ete ajoute a @m
*/
struct line *add_line( struct sp_matrix *m, unsigned int i ) {

	struct line *this_line;
    // case 1: empty matrix
    if (m->lines == NULL) {
        this_line = init_line( i );
		if (this_line == NULL) return NULL; // if malloc echoue
        m->lines = this_line;
        return this_line;
        }

    // case 2: ALL
    this_line = m->lines;
    struct line *prev_line = NULL;
     while (this_line != NULL) {
        if (this_line->i < i) {
            prev_line = this_line;
            this_line = this_line->next;
        } else break;
    }

    // case 2: at the begining
     if (prev_line == NULL) {
         prev_line = init_line( i );
		if (prev_line == NULL) return NULL; // if malloc echoue
        prev_line->next = this_line;
        m->lines = prev_line;

        return prev_line;
    }

    // case 2: in the last row
    if (this_line == NULL) {
        this_line = init_line( i );
		if (this_line == NULL) return NULL; // if malloc echoue
        prev_line->next = this_line;
        return this_line;
    }

    // case 2: elsewhere (i.e. in the middle)
    prev_line->next = init_line( i );
	if ( (prev_line->next) == NULL) return NULL; // if malloc echoue
    prev_line->next->next = this_line;

return prev_line->next;
}

/*
 *@pre : @del_line!=NULL, @m !=NULL
 *@pre: @del_line a ete elimine de @m
*/
int delete_line(struct sp_matrix *m, struct line *del_line) {

	struct line *this_line;
    // case 1: ALL
    this_line = m->lines;
    struct line *prev_line = NULL;
    while (this_line != NULL) {
        if (this_line != del_line) {
            prev_line = this_line;
            this_line = this_line->next;
        } else break;
    }

    // case 1.2: at the begining
    if (prev_line == NULL) {
        (m->lines)= (this_line->next);
        free(del_line);
        return 0;
    }

    // case 1.3: in the last row
    if (this_line == NULL) {
        prev_line->next= NULL;
		free(del_line);
        return 0;
    }

    // case 1.4: elsewhere (i.e. in the middle)
    prev_line->next = this_line->next;
	this_line->elems=NULL;
	free(this_line);
return 0;
}


/*
 * @pre : @matrix !=NULL, @this_elem!=NULL, @this_line !=NULL
 * @Postconditions elimine @this_elem de @matrix, si @this_elem est unique dans @this_line alors
 *                 @this_line est aussi elimine de @matrix.
 */
 int delete_element (struct sp_matrix * matrix, struct line *this_line, struct elem *this_elem){
	if ( ((matrix->lines->next)==NULL ) && ((matrix->lines->elems->next) == NULL) ){ // ligne unique , elem unique
		free(this_elem);
		free(this_line);
		matrix->lines= NULL;
		return 0;
	}
	int flag= del_elem(this_line, this_elem);
	if (flag == 0){
		int r= delete_line(matrix, this_line);
		return r;
	}
 return 0;
 }

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
int sp_matrix_set(struct sp_matrix *matrix, unsigned int i, unsigned int j, double val){
    if (matrix ==NULL ||  ((int)(i)) < 0  || ((int)(j)) < 0  || ((matrix->nlines) <= i) || ((matrix->ncols) <= j))
	 return -1;

	if ((fabs(val) < (matrix->precision)) && (matrix->lines)== NULL) return 0; // (fabs(val) < precision) set in empty matrix

    struct line *this_line = find_line(matrix->lines, i );
    if (this_line == NULL) { // The row doesn't exist
	    if (fabs(val) < (matrix->precision)) return 0; // val < precision set sur ligne vide ne doit pas créer de ligne

	    // Add row
        this_line = add_line( matrix, i );
		if (this_line == NULL) return -1; 				//if malloc echoue

        struct elem *this_elem = add_elem( this_line, j );
	    if (this_elem == NULL) return -1;  				//if malloc echoue

        this_elem->value = val;
        this_line->elems = this_elem;
        return 0;

	} else { // The row exist
        struct  elem *this_elem = find_elem( this_line->elems, j );
        if (this_elem == NULL) {  // The elem doesn't exist
			 if (fabs(val) < (matrix->precision)) return 0; // fabs(val) < precision set sur colonne qui n'exist pas, ne doit pas créer un colonne

            this_elem = add_elem( this_line, j ); // The col doesn't exist and isn't zero, add it
			if (this_elem == NULL) return -1; //if malloc echoue
			this_elem->value = val;
            return 0;
        }
		if (fabs(val) < (matrix->precision)){ // if elem exist and fabs(val) < precision
			 return delete_element (matrix, this_line, this_elem);
		}
		// if elem exist and fabs(val) >= precision
		this_elem->value = val;
		return 0;
    }
    return -1;
}


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
double matrix_get(const struct matrix *matrix, unsigned int i, unsigned int j){
	// si matrix == NULL il n'est pas dis quoi faire
	// l'utilisateur dois (imperativement) respecter les precoditions
	// on peux pas retourner -1 parce que ca peux etre un value de la matrix
	return (matrix->elems)[i][j];
}

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
double sp_matrix_get(const struct sp_matrix *matrix, unsigned int i, unsigned int j){
	// l'utilisateur dois (imperativement) respecter les precoditions,
	// il n'est pas dis quoi faire pour faire de la programation defensive
    struct line *this_line = find_line( matrix->lines, i );

    if (this_line != NULL) {
        struct elem *this_element = find_elem( this_line->elems, j );
        if (this_element != NULL) {
            return this_element->value;
        } else { // it is a zero value in this 'this_line' row
            return 0;
        }
    } else {  //It is a zero value in an empty row
        return 0;
    }
}

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
struct matrix *matrix_add(const struct matrix *m1, const struct matrix *m2){
	if (m1==NULL || m2==NULL) return NULL; //precodition
	if ((m1->nlines)!=(m2->nlines) ||(m1->ncols)!=(m2->ncols)) return NULL;

    struct matrix *MatrixSum=matrix_init(m1->nlines, m1->ncols);
    if (MatrixSum==NULL) return NULL;
    unsigned int i,j;
	for (i=0; i<m1->nlines; i++){
		for (j=0; j<m1->ncols; j++){
			(MatrixSum->elems)[i][j]=((m1->elems)[i][j]) + ((m2->elems)[i][j]); 
		}	 
	}
	return MatrixSum;

}

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
struct sp_matrix *sp_matrix_add(const struct sp_matrix *m1, const struct sp_matrix *m2){
    if (m1==NULL || m2==NULL) return NULL; //precodition
	if ((m1->nlines)!=(m2->nlines) ||(m1->ncols)!=(m2->ncols)) return NULL;
	// la plus mauvaise (precision) qui l'emporte.
   double precision;
   if ((m1->precision ) >= (m2->precision)){
   	 precision = (m1->precision);
   }else precision = (m2->precision);

	// init MatrixSum
    struct sp_matrix *MatrixSum=sp_matrix_init(precision, m1->nlines, m1->ncols);
	if (MatrixSum==NULL) return NULL; // if malloc echoue

	unsigned int i,j;
	int flag=0;
    for(i = 0; i < (m1->nlines); i++){
		for(j = 0; j < (m1->ncols); j++){
			double sum= sp_matrix_get(m1, i, j)+sp_matrix_get(m2, i, j);
			if (fabs(sum) >= precision){
				flag= sp_matrix_set(MatrixSum,i,j,sum);
				if (flag!=0) return NULL; // if malloc echoue
			}
		}
	}
	return MatrixSum;
}

/* matrix_transpose
 * Calcule la transposée d'une matrice tableau.
 *
 * @matrix: opérande
 * @return: Matrice tableau étant la transposée de @matrix
 *
 * Préconditions: @matrix != NULL
 * Postconditions: @matrix est inchangé.
 */
struct matrix *matrix_transpose(const struct matrix *matrix){
    if (matrix==NULL) return NULL; // l'utilisateur dois respecter les precoditions programation defensive
    struct matrix *TrpsMatrix= matrix_init(matrix->ncols, matrix->nlines);
    if (TrpsMatrix==NULL) return NULL; // if init echec
    unsigned int i, j;
    for (j = 0; j < (matrix->nlines); ++j){
        for (i = 0; i < (matrix->ncols); ++i){
            (TrpsMatrix->elems)[i][j]= ((matrix->elems)[j][i]);
        }        
    }
	return TrpsMatrix;
}

/* sp_matrix_transpose
 * Calcule la transposée d'une matrice creuse.
 *
 * @matrix: opérande
 * @return: Matrice creuse étant la transposée de @matrix
 *
 * Préconditions: @matrix != NULL
 * Postconditions: @matrix est inchangé.
 */
struct sp_matrix *sp_matrix_transpose(const struct sp_matrix *matrix){
    if (matrix==NULL) return NULL; // l'utilisateur dois respecter les precoditions, programation defensive

	struct sp_matrix *TrpsMatrix= sp_matrix_init(matrix->precision, matrix->ncols, matrix->nlines);
    if (TrpsMatrix==NULL) return NULL; // if init echec
	if ((matrix->lines)== NULL) return TrpsMatrix; //transposée d'une matrice vide doit être vide
    unsigned int i,j;
    int flag=0;
	struct line *currentLine= matrix->lines;
	while(currentLine!=NULL){
		i = currentLine->i;
		struct elem *currentElement= currentLine->elems;
		while(currentElement!=NULL){
			j = currentElement->j;			
            flag = sp_matrix_set(TrpsMatrix,j,i,currentElement->value);
			if (flag!=0){
                return NULL; // if malloc echoue
			}
	     	currentElement= currentElement->next;
		}
		currentLine= currentLine->next;
	}
	return TrpsMatrix;
}

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
struct matrix *matrix_mult(const struct matrix *m1, const struct matrix *m2){
   if (m1==NULL || m2==NULL || (m1->ncols)!=(m2->nlines)) return NULL; //precodition

   struct matrix *MulMatrix= matrix_init(m1->nlines, m2->ncols); // m1 dim(nXm),  m2 dim(mXp);  m1*m2 ==> dim(nXp)
   if (MulMatrix==NULL) return NULL; // if malloc echoue
    unsigned int i, j, k;
    for (i = 0; i < (m1->nlines); i++){
        for (j = 0; j < (m2->ncols); j++){
			for(k = 0; k < m1->ncols; k++){
				((MulMatrix->elems)[i][j])+= ((m1->elems)[i][k])*((m2->elems)[k][j]);			}
        }        
    }
	return MulMatrix;
}

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
struct sp_matrix *sp_matrix_mult(const struct sp_matrix *m1, const struct sp_matrix *m2){
   if (m1==NULL || m2==NULL || (m1->ncols)!=(m2->nlines)) return NULL; //precodition
  // la plus mauvaise qui l'emporte.
   double precision;
   if ((m1->precision ) >= (m2->precision)){
   	 precision = (m1->precision);
   }else precision = (m2->precision);

   struct sp_matrix *MulMatrix= sp_matrix_init(precision, m1->nlines, m2->ncols); // m1 dim(nXm),  m2 dim(mXp);  m1*m2 ==> dim(nXp)
   if (MulMatrix==NULL) return NULL; // if malloc echoue
   // mult deux matrices vides donne une matrice vide
   // si M1 vide ou M2 vide donne une matrice vide
	if (((m1->lines) == NULL) || ((m2->lines) == NULL) ) return MulMatrix;

	unsigned int i, j, k;
	int flag=0;
    for (i = 0; i < (m1->nlines); i++){
        for (j = 0; j < (m2->ncols); j++){
			for(k = 0; k < m1->ncols; k++){
				double resMul= sp_matrix_get(m1,i,k) * sp_matrix_get(m2,k,j);
                double this = sp_matrix_get(MulMatrix,i,j);
				double final= this+resMul;
				if (fabs(final) >= precision){
					flag= sp_matrix_set(MulMatrix, i,j, (this + resMul) );
					if (flag!=0) return NULL; // if malloc echoue
				}
			}
        }
    }
	return MulMatrix;
}


/* matrix_to_sp_matrix
 * Transforme une matrice tableau en une matrice creuse.
 *
 * @matrix: matrice tableau à transformer
 * @precision: précision des éléments de la nouvelle matrice creuse
 * @return: matrice creuse correspondante à @matrix ou NULL si erreur
 *
 * Préconditions: matrix != NULL && 0 < @precision
 * Postconditions: matrix est inchangée
 */
struct sp_matrix *matrix_to_sp_matrix (const struct matrix *matrix, double precision){
	if (matrix == NULL ) return NULL;
    struct sp_matrix *sp_m = sp_matrix_init(precision, matrix->nlines, matrix->ncols );
	if (sp_m == NULL) return NULL;// if malloc echoue

    unsigned int i, j;
	int flag = 0;
    for ( i=0; i < (matrix->nlines); i++){
        for ( j=0; j < (matrix->ncols); j++){
            if( fabs(((matrix->elems)[i][j])) >= fabs(precision)){
             	flag = sp_matrix_set( sp_m, i,j, (matrix->elems)[i][j]);
                if (flag!=0) return NULL; // if malloc echoue
			}
		}
	}
    return sp_m;
}



/* sp_matrix_to_matrix
 * Transforme une matrice creuse en une matrice tableau.
 *
 * @matrix: matrice creuse à transformer
 * @return: matrice tableau correspondante à @matrix ou NULL si erreur
 *
 * Préconditions: matrix != NULL
 * Postconditions: matrix est inchangée
 */
struct matrix *sp_matrix_to_matrix (const struct sp_matrix *matrix){
	if (matrix ==NULL) return NULL;
    struct matrix *m = matrix_init(matrix->nlines, matrix->ncols );
	if (m == NULL) return NULL;// if malloc echoue
    if ((matrix->lines) == NULL) return m;

    unsigned int i,j;
    struct line *currentLine= matrix->lines;
    while(currentLine!=NULL){
        i = currentLine->i;
        struct elem *currentElement= currentLine->elems;
        while(currentElement!=NULL){
            j = currentElement->j;
            (m->elems)[i][j]= (currentElement->value);
            currentElement= currentElement->next;
        }
        currentLine= currentLine->next;
    }
return m;
}

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
int matrix_save(const struct matrix *matrix, char *path){
    FILE *file = fopen(path, "wb");
	if (file == NULL) return -1;
		if (fwrite(&(matrix->nlines), sizeof(const unsigned int), 1, file) != 1) return -1;
		if (fwrite(&(matrix->ncols), sizeof(const unsigned int), 1, file)  != 1) return -1;
		unsigned int i,j;
		for(i = 0; i < matrix->nlines; i++){
		    for(j = 0; j < matrix->ncols; j++){
		     	if (fwrite(&((matrix->elems)[i][j]), sizeof(double), 1, file)!= 1) return -1;
		    }
		}    
    if (fclose(file)!=0) return -1; // error fclose
	return 0;
}


/* matrix_load
 * Charge une matrice tableau à partir d'un fichier
 *
 * @path: chemin du fichier à partir duquel charger la matrice
 * @return: matrice tableau contenue dans le fichier @path, NULL en cas d'erreur
 *
 * Préconditions: path != NULL
 * Postconditions: @path est inchangée
 */
struct matrix *matrix_load (char *path){
    FILE * file= fopen(path, "r");
    if (file == NULL) return NULL;
	unsigned int lines;
    unsigned int cols;
	if (fread(&(lines), sizeof(const unsigned int), 1, file)!= 1) return NULL;
	if (fread(&(cols),  sizeof(const unsigned int), 1, file)!= 1) return NULL;

	struct matrix *newMatrix= matrix_init(lines, cols);
	if (newMatrix == NULL) return NULL; // if malloc echoue

	unsigned int i,j;
    for(i = 0; i < newMatrix->nlines; i++){
	    for(j = 0; j < newMatrix->ncols; j++){
	     	if (fread(&((newMatrix->elems)[i][j]), sizeof(double), 1, file)!= 1) return NULL;
	    }
	}
	// close file
    if (fclose(file)!=0) return NULL; // error fclose
return newMatrix;
}



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
int sp_matrix_save (const struct sp_matrix *matrix, char *path){
    FILE *file = fopen(path, "wb");
	if (file == NULL) return -1;

	if (fwrite(&(matrix->nlines), sizeof(const unsigned int), 1, file)!= 1) return -1;
	if (fwrite(&(matrix->ncols), sizeof(const unsigned int), 1, file)!= 1) return -1;
	if (fwrite(&(matrix->precision), sizeof(double), 1, file)!= 1) return -1;
	unsigned int i,j;
	struct line *currentLine= matrix->lines;
	while(currentLine!=NULL){
		i = currentLine->i;
		struct elem *currentElement= currentLine->elems;
		while(currentElement!=NULL){
			j = currentElement->j;
			if (fwrite(&(i), sizeof(unsigned int), 1, file)!= 1) return -1;// write line of  value in M(i,j)
			if (fwrite(&(j), sizeof(unsigned int), 1, file)!= 1) return -1; // write colon of value in M(i,j)
	     	if (fwrite(&(currentElement->value), sizeof(double), 1, file)!= 1) return -1; // write value
	     	currentElement= currentElement->next;
		}
		currentLine= currentLine->next;
	}
    if (fclose(file)!=0) return -1; // error fclose
return 0;
}


/* sp_matrix_load
 * Charge une matrice creuse à partir d'un fichier
 *
 * @path: chemin du fichier à partir duquel charger la matrice
 * @return: matrice creuse contenue dans le fichier @path, NULL en cas d'erreur
 *
 * Préconditions: path != NULL
 * Postconditions: @path est inchangée
 */
struct sp_matrix *sp_matrix_load (char *path){
    FILE * file= fopen(path, "r");
    if (file == NULL) return NULL;
	unsigned int lines;
    unsigned int cols;
	double precision;

	if (fread(&(lines), sizeof(const unsigned int), 1, file)!= 1) return NULL;
	if (fread(&(cols),  sizeof(const unsigned int), 1, file)!= 1) return NULL;
	if (fread(&(precision), sizeof(double), 1, file)!= 1) return NULL;

	struct sp_matrix *newMatrix= sp_matrix_init(precision, lines, cols);
	if (newMatrix == NULL) return NULL; // if malloc echoue

	unsigned int i,j;
	double val_temporal;
	int flag=0;
    while( (fread(&(i), sizeof(const unsigned int), 1, file))==1 ) {
     	if (fread(&(j), sizeof(const unsigned int), 1, file)!= 1) return NULL; // read colonne of this value
		if (fread(&(val_temporal), sizeof(double), 1, file)!= 1) return NULL; // read this value
        flag= sp_matrix_set(newMatrix,i,j,val_temporal);
		if (flag!=0) return NULL;
	}
    if (!feof(file)) return NULL;
    if (fclose(file)!=0) return NULL; // error fclose
return newMatrix;
}





