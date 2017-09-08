/**
 * Laritza Cabrera Alba
 *
 *  CUnit test seulement dans le cas ou la function malloc functionne correctement.
 */



#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "matrix.h"

// Test matrix

//test lines
void matrix_init_test_lines(void) {
    struct matrix* newMatrix = matrix_init(3,7);
    if (newMatrix!=NULL){
        CU_ASSERT_EQUAL(newMatrix->nlines,3);
        CU_ASSERT_EQUAL(newMatrix->elems[0][0],0);
        matrix_free(newMatrix);
    }
    struct matrix* newMatrixNULL1 = matrix_init(0,0);
    CU_ASSERT_PTR_NULL(newMatrixNULL1);
    
    struct matrix* newMatrixNULL2 = matrix_init(1,0);
    CU_ASSERT_PTR_NULL(newMatrixNULL2);
    
    struct matrix* newMatrixNULL3 = matrix_init(0,8);
    CU_ASSERT_PTR_NULL(newMatrixNULL3);
    
    struct matrix* newMatrixNULL = matrix_init(-3,-7);
    CU_ASSERT_PTR_NULL(newMatrixNULL);
    
}
//test  colum
void matrix_init_test_cols(void) {
    struct matrix* newMatrix = matrix_init(3,7);
    if (newMatrix!=NULL){
        CU_ASSERT_EQUAL(newMatrix->elems[0][0],0);
        CU_ASSERT_EQUAL(newMatrix->ncols,7);
        matrix_free(newMatrix);
    }
}
// test  matrix init zero
void matrix_init_zero(void) {
    struct matrix* newMatrix = matrix_init(2,2);
    if (newMatrix!=NULL){
        CU_ASSERT_EQUAL(newMatrix->elems[0][0],0);
        CU_ASSERT_EQUAL(newMatrix->elems[0][1],0);
        CU_ASSERT_EQUAL(newMatrix->elems[1][0],0);
        CU_ASSERT_EQUAL(newMatrix->elems[1][1],0);
        matrix_free(newMatrix);
    }
}
// Test  matrix_get
void matrix_test_get(void){
    struct matrix *newMatrix = matrix_init(5,6);
    if (newMatrix!=NULL){
        int value1 = matrix_get(newMatrix,2,3);
        int value2 = matrix_get(newMatrix,4,5);
        int value3 = matrix_get(newMatrix,0,0);
        CU_ASSERT_EQUAL(value1,0);
        CU_ASSERT_EQUAL(value2,0);
        CU_ASSERT_EQUAL(value3,0);
        matrix_free(newMatrix);
    }
}
//Test  matrix_set
void matrix_check_set(void){
    struct matrix *newMatrix = matrix_init(11,12);
    if (newMatrix!=NULL){
        CU_ASSERT_EQUAL(matrix_get(newMatrix,5,6),0);
        CU_ASSERT_EQUAL(matrix_set(newMatrix,5,6,8),0);
        CU_ASSERT_EQUAL(matrix_get(newMatrix,5,6),8);
        
        CU_ASSERT_EQUAL(matrix_get(newMatrix,1,1),0);
        CU_ASSERT_EQUAL(matrix_set(newMatrix,1,1,8),0);
        CU_ASSERT_EQUAL(matrix_get(newMatrix,1,1),8);
        
        // Add elemnt, inadmissible dimention, reurn -1
        CU_ASSERT_EQUAL(matrix_set(newMatrix,13,14,12),-1);
        CU_ASSERT_EQUAL(matrix_set(newMatrix,11,12,12),-1);
        CU_ASSERT_EQUAL(matrix_set(newMatrix,-11,-12,12),-1);
        matrix_free(newMatrix);
    }
    // if matrix is NULL return -1
    CU_ASSERT_EQUAL(matrix_set(NULL,1,3,17),-1);
}

//Test matrix_add
void matrix_add_test(void){
    
    struct matrix* matrixA= matrix_init(4,4);
    struct matrix* matrixB= matrix_init(4,4);
    if (matrixA !=NULL && matrixB!= NULL){ // if malloc echoue
        CU_ASSERT_EQUAL(matrix_set(matrixA,0,0,1),0);
        CU_ASSERT_EQUAL(matrix_set(matrixA,1,0,1),0);
        CU_ASSERT_EQUAL(matrix_set(matrixA,2,0,2),0);
        CU_ASSERT_EQUAL(matrix_set(matrixA,3,0,8),0);
        
        CU_ASSERT_EQUAL(matrix_set(matrixB,0,0,1),0);
        CU_ASSERT_EQUAL(matrix_set(matrixB,1,0,2),0);
        CU_ASSERT_EQUAL(matrix_set(matrixB,2,0,3),0);
        CU_ASSERT_EQUAL(matrix_set(matrixB,3,0,4),0);
        
        //A+B
        struct matrix* matrixSumm= matrix_add(matrixA,matrixB);
        if (matrixSumm !=NULL ){
            CU_ASSERT_EQUAL(matrix_get(matrixSumm,0,0),2);
            CU_ASSERT_EQUAL(matrix_get(matrixSumm,1,0),3);
            CU_ASSERT_EQUAL(matrix_get(matrixSumm,2,0),5);
            CU_ASSERT_EQUAL(matrix_get(matrixSumm,3,0),12);
            matrix_free(matrixSumm);
        }
        //A+B = B+A
        struct matrix* matrixSummBA= matrix_add(matrixB,matrixA);
        if (matrixSummBA !=NULL ){
            CU_ASSERT_EQUAL(matrix_get(matrixSummBA,0,0),2);
            CU_ASSERT_EQUAL(matrix_get(matrixSummBA,1,0),3);
            CU_ASSERT_EQUAL(matrix_get(matrixSummBA,2,0),5);
            CU_ASSERT_EQUAL(matrix_get(matrixSummBA,3,0),12);
            matrix_free(matrixSummBA);
        }
        // A+ 0= A
        struct matrix* matrix_zero= matrix_init(4,4);
        struct matrix* matrixAoA= matrix_add(matrixA,matrix_zero);
        if (matrixAoA !=NULL ){
            CU_ASSERT_EQUAL(matrix_get(matrixAoA,0,0),1);
            CU_ASSERT_EQUAL(matrix_get(matrixAoA,1,0),1);
            CU_ASSERT_EQUAL(matrix_get(matrixAoA,2,0),2);
            CU_ASSERT_EQUAL(matrix_get(matrixAoA,3,0),8);
            matrix_free(matrixAoA);
        }
        matrix_free(matrix_zero);
        matrix_free(matrixA);
        matrix_free(matrixB);
    }
}

//********************************************************************
//Test matrix_add NULL
void matrix_add_test_null(void){
    
    // add deux matrices NULL + non NULL return NULL
    struct matrix *matrixA1= NULL;
    struct matrix *matrixB1= matrix_init(4,8);
    struct matrix *matrixSumm1= matrix_add(matrixA1,matrixB1);
    CU_ASSERT_PTR_NULL(matrixSumm1);
    
    // add deux matrices non NULL + NULL return NULL
    struct matrix *matrixC1= matrix_init(3,4);
    struct matrix *matrixD1= NULL;
    struct matrix *matrixSumm2= matrix_add(matrixC1,matrixD1);
    CU_ASSERT_PTR_NULL(matrixSumm2);
    
    // add deux matrices NULL + NULL return NULL
    struct matrix *matrixSumm3= matrix_add(matrixA1,matrixD1);
    CU_ASSERT_PTR_NULL(matrixSumm3);
    
    // add different size return NULL
    struct matrix *matrixSumm4= matrix_add(matrixB1,matrixC1);
    CU_ASSERT_PTR_NULL(matrixSumm4);
    
    // add different size return NULL
    struct matrix *matrixSumm5= matrix_add(matrixC1,matrixB1);
    CU_ASSERT_PTR_NULL(matrixSumm5);
    
    matrix_free(matrixA1);
    matrix_free(matrixB1);
    matrix_free(matrixC1);
    matrix_free(matrixD1);
    
}

//Test Transpose
void matrix_check_transpose(void){
    struct matrix *matrixAA = matrix_init(2,3);
    CU_ASSERT_PTR_NOT_NULL(matrixAA);
    //line 1
    CU_ASSERT_EQUAL(matrix_set(matrixAA,0,0,1),0);
    CU_ASSERT_EQUAL(matrix_set(matrixAA,0,1,2),0);
    CU_ASSERT_EQUAL(matrix_set(matrixAA,0,2,3),0);
    //line 2
    CU_ASSERT_EQUAL(matrix_set(matrixAA,1,0,4),0);
    CU_ASSERT_EQUAL(matrix_set(matrixAA,1,1,5),0);
    CU_ASSERT_EQUAL(matrix_set(matrixAA,1,2,6),0);
    
    struct matrix *matrixT = matrix_transpose(matrixAA);
    CU_ASSERT_PTR_NOT_NULL(matrixT);
    // line 1
    CU_ASSERT_EQUAL(matrix_get(matrixT,0,0),1);
    CU_ASSERT_EQUAL(matrix_get(matrixT,0,1),4);
    // line 2
    CU_ASSERT_EQUAL(matrix_get(matrixT,1,0),2);
    CU_ASSERT_EQUAL(matrix_get(matrixT,1,1),5);
    // line 3
    CU_ASSERT_EQUAL(matrix_get(matrixT,2,0),3);
    CU_ASSERT_EQUAL(matrix_get(matrixT,2,1),6);
    
    // transpose de une matrix 1x1
    struct matrix *m1x1 = matrix_init(1,1);
    CU_ASSERT_EQUAL(matrix_set(m1x1,0,0,1),0);
    struct matrix *Tm1x1 = matrix_transpose(m1x1);
    CU_ASSERT_PTR_NOT_NULL(matrixT);
    CU_ASSERT_EQUAL(matrix_get(Tm1x1,0,0),1);
    
    matrix_free(Tm1x1);
    matrix_free(matrixT);
    
    //transpose d'une matrice NULL
    // CU_ASSERT_PTR_NULL(matrix_transpose(NULL));
    
    // --------------------matrix to sp_marix------------------------
    struct sp_matrix *matrix_sp = matrix_to_sp_matrix(matrixAA, 0.01);
    CU_ASSERT_PTR_NOT_NULL(matrix_sp->lines);
    
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_sp,0,0), 1);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_sp,0,1), 2);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_sp,0,2), 3);
    
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_sp,1,0), 4);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_sp,1,1), 5);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_sp,1,2), 6);
    
    // convert matrix 1x1
    struct sp_matrix *matrix_sp1x1 = matrix_to_sp_matrix(m1x1, 0.01);
    CU_ASSERT_PTR_NOT_NULL(matrix_sp1x1->lines);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_sp1x1,0,0), 1);
    
    sp_matrix_free(matrix_sp1x1);
    matrix_free(m1x1);
    sp_matrix_free(matrix_sp);
    matrix_free(matrixAA);
    
}

// test multiplication (nxn) * (nxn)
void matrix_mult_nxn_test(void){
    struct matrix *matrixA= matrix_init(3, 3);
    (matrixA->elems)[0][0] = 3;
    (matrixA->elems)[0][1] = 4;
    (matrixA->elems)[0][2] = 5;
    
    (matrixA->elems)[1][0] = 1;
    (matrixA->elems)[1][1] = 5;
    (matrixA->elems)[1][2] = 7;
    
    (matrixA->elems)[2][0] = 9;
    (matrixA->elems)[2][1] = 1;
    (matrixA->elems)[2][2] = 7;
    
    
    
    struct matrix *matrixB= matrix_init(3, 3);
    (matrixB->elems)[0][0] = 5;
    (matrixB->elems)[0][1] = 9;
    (matrixB->elems)[0][2] = 7;
    
    (matrixB->elems)[1][0] = 3;
    (matrixB->elems)[1][1] = 1;
    (matrixB->elems)[1][2] = 7;
    
    (matrixB->elems)[2][0] = 9;
    (matrixB->elems)[2][1] = 0;
    (matrixB->elems)[2][2] = 0;
    // MUlt une multiplication non-nulle doit être correcte
    struct matrix* matrixMult= matrix_mult(matrixA,matrixB);
    
    CU_ASSERT_EQUAL(matrix_get(matrixMult,0,0),72);
    CU_ASSERT_EQUAL(matrix_get(matrixMult,1,0),83);
    CU_ASSERT_EQUAL(matrix_get(matrixMult,2,0),111);
    
    matrix_free(matrixA);
    matrix_free(matrixB);
    matrix_free(matrixMult);
}

// test multiplication (nxm) * (mxn)
void matrix_mult_nxm_test(void){
    struct matrix *matrix1= matrix_init(4, 3);
    (matrix1->elems)[0][0] = 6;
    (matrix1->elems)[0][1] = 46;
    (matrix1->elems)[0][2] = 56;
    
    (matrix1->elems)[1][0] = 13;
    (matrix1->elems)[1][1] = 35;
    (matrix1->elems)[1][2] = 7;
    
    (matrix1->elems)[2][0] = 49;
    (matrix1->elems)[2][1] = 14;
    (matrix1->elems)[2][2] = 75;
    
    (matrix1->elems)[3][0] = 0;
    (matrix1->elems)[3][1] = 99;
    (matrix1->elems)[3][2] = 71;
    
    struct matrix *matrix2= matrix_init(3, 2);
    (matrix2->elems)[0][0] = 51;
    (matrix2->elems)[0][1] = 9;
    
    (matrix2->elems)[1][0] = 31;
    (matrix2->elems)[1][1] = 15;
    
    (matrix2->elems)[2][0] = 9;
    (matrix2->elems)[2][1] = 55;
    
    struct matrix* matrixMult= matrix_mult(matrix1,matrix2);
    //	Matrix result of multiplication
    //2236	3824
    //1811	1027
    //3608	4776
    //3708	5390
    
    CU_ASSERT_EQUAL(matrix_get(matrixMult,0,0),2236);
    CU_ASSERT_EQUAL(matrix_get(matrixMult,1,0),1811);
    CU_ASSERT_EQUAL(matrix_get(matrixMult,2,0),3608);
    CU_ASSERT_EQUAL(matrix_get(matrixMult,3,0),3708);
    
    //test matrix save
    CU_ASSERT_EQUAL(matrix_save(matrix1, "matrix_4x3.data"),0);
    CU_ASSERT_EQUAL(matrix_save(matrix2, "matrix_3x2.data"),0);
    CU_ASSERT_EQUAL(matrix_save(matrixMult, "matrix_4x2.data"),0);
    
    // test sp_marix_save
    struct sp_matrix *sp_newMatrix_4x3 = matrix_to_sp_matrix(matrix1, 0.01);
    CU_ASSERT_PTR_NOT_NULL(sp_newMatrix_4x3->lines);
    CU_ASSERT_EQUAL(sp_matrix_save(sp_newMatrix_4x3, "matrix_4x3.sp"),0);
    sp_matrix_free(sp_newMatrix_4x3);
    
    struct sp_matrix *sp_newMatrix_3x2 = matrix_to_sp_matrix(matrix2, 0.01);
    CU_ASSERT_PTR_NOT_NULL(sp_newMatrix_3x2->lines);
    CU_ASSERT_EQUAL(sp_matrix_save(sp_newMatrix_3x2, "matrix_3x2.sp"),0);
    sp_matrix_free(sp_newMatrix_3x2);
    
    struct sp_matrix *sp_newMatrix_4x2 = matrix_to_sp_matrix(matrixMult, 0.01);
    CU_ASSERT_PTR_NOT_NULL(sp_newMatrix_4x2->lines);
    CU_ASSERT_EQUAL(sp_matrix_save(sp_newMatrix_4x2, "matrix_4x2.sp"),0);
    sp_matrix_free(sp_newMatrix_4x2);
    
    matrix_free(matrix1);
    matrix_free(matrix2);
    matrix_free(matrixMult);
}

// test multiplication (nxm) * (mxn)
void matrix_mult_mxn_test(void){
    struct matrix *matrix1= matrix_init(2,3);
    (matrix1->elems)[0][0] = 16;
    (matrix1->elems)[0][1] = 9;
    (matrix1->elems)[0][2] = 3;
    
    (matrix1->elems)[1][0] = 0;
    (matrix1->elems)[1][1] = 1;
    (matrix1->elems)[1][2] = 73;
    
    struct matrix *matrix2= matrix_init(3, 1);
    (matrix2->elems)[0][0] = 6;
    (matrix2->elems)[1][0] = 11;
    (matrix2->elems)[2][0] = 23;
    
    struct matrix* matrixMult= matrix_mult(matrix1,matrix2);
    
    CU_ASSERT_EQUAL(matrix_get(matrixMult,0,0),264);
    CU_ASSERT_EQUAL(matrix_get(matrixMult,1,0),1690);
    
    // multiplication dimention pas correctes
    struct matrix *matrix1x5= matrix_init(1,5);
    struct matrix* matrixMult_NULL= matrix_mult(matrix1,matrix1x5);
    CU_ASSERT_PTR_NULL(matrixMult_NULL);
    
    matrix_free(matrix1x5);
    matrix_free(matrix1);
    matrix_free(matrix2);
    matrix_free(matrixMult);
}

// test save
void test_save(void){
    
    struct matrix *matrix_3x3= matrix_init(3, 3);
    (matrix_3x3->elems)[0][0] = 3;
    (matrix_3x3->elems)[0][1] = 4;
    (matrix_3x3->elems)[0][2] = 5;
    
    (matrix_3x3->elems)[1][0] = 1;
    (matrix_3x3->elems)[1][1] = 5;
    (matrix_3x3->elems)[1][2] = 7;
    
    (matrix_3x3->elems)[2][0] = 9;
    (matrix_3x3->elems)[2][1] = 1;
    (matrix_3x3->elems)[2][2] = 17;
    // save  matrix	 3x3
    CU_ASSERT_EQUAL(matrix_save(matrix_3x3, "matrix_3x3.data"),0);
    
    // convert matrix 3x3 to sp_matrix and save sp_matrix
    struct sp_matrix *sp_newMatrix_3x3 = matrix_to_sp_matrix(matrix_3x3, 0.01);
    CU_ASSERT_PTR_NOT_NULL(sp_newMatrix_3x3->lines);
    CU_ASSERT_EQUAL(sp_matrix_save(sp_newMatrix_3x3, "matrix_3x3.sp"),0);
    sp_matrix_free(sp_newMatrix_3x3);
    
    // save  matrix 2x1
    struct matrix *matrix_2x1= matrix_init(2, 1);
    (matrix_2x1->elems)[0][0] = 973;
    (matrix_2x1->elems)[1][0] = 78;
    CU_ASSERT_EQUAL(matrix_save(matrix_2x1, "matrix_2x1.data"),0);
    
    // convert matrix 2x1 to sp_matrix and save sp_matrix
    struct sp_matrix *sp_newMatrix_2x1 = matrix_to_sp_matrix(matrix_2x1, 0.01);
    CU_ASSERT_PTR_NOT_NULL(sp_newMatrix_2x1->lines);
    CU_ASSERT_EQUAL(sp_matrix_save(sp_newMatrix_2x1, "matrix_2x1.sp"),0);
   	sp_matrix_free(sp_newMatrix_2x1);
    
    // save  matrix 2x3
   	struct matrix *matrix_2x3= matrix_init(2, 3);
    (matrix_2x3->elems)[0][0] = 53;
    (matrix_2x3->elems)[0][1] = 46;
    (matrix_2x3->elems)[0][2] = 5;
    
    (matrix_2x3->elems)[1][0] = 1;
    (matrix_2x3->elems)[1][1] = 75;
    (matrix_2x3->elems)[1][2] = 67;
   	CU_ASSERT_EQUAL(matrix_save(matrix_2x3, "matrix_2x3.data"),0);
    
    // convert matrix 2x3 to sp_matrix and save sp_matrix
    struct sp_matrix *sp_newMatrix_2x3 = matrix_to_sp_matrix(matrix_2x3, 0.01);
    CU_ASSERT_PTR_NOT_NULL(sp_newMatrix_2x3->lines);
    CU_ASSERT_EQUAL(sp_matrix_save(sp_newMatrix_2x3, "matrix_2x3.sp"),0);
    sp_matrix_free(sp_newMatrix_2x3);
    
    //save a zero sp_matrix  dim(4x9)
    struct sp_matrix *zeroMatrix_4x9_save = sp_matrix_init(0.01, 4, 9);
    CU_ASSERT_PTR_NOT_NULL(zeroMatrix_4x9_save);
    CU_ASSERT_EQUAL(sp_matrix_save(zeroMatrix_4x9_save, "matrix_4x9.sp"),0);
    sp_matrix_free(zeroMatrix_4x9_save);
    
   	matrix_free(matrix_3x3);
   	matrix_free(matrix_2x1);
   	matrix_free(matrix_2x3);
    
}

// matrix and sp_matrix test load
void matrix_test_load(void){
    // test matrix load dim(2x1) voir  test superieur
    struct matrix *matrix_2x1_load= matrix_load("matrix_2x1.data");
	   CU_ASSERT_PTR_NOT_NULL(matrix_2x1_load);
	   CU_ASSERT_EQUAL(matrix_get(matrix_2x1_load,0,0),973);
	   CU_ASSERT_EQUAL(matrix_get(matrix_2x1_load,1,0),78);
    matrix_free(matrix_2x1_load);
    
    // test matrix load dim(2x3) voir test superieur
    struct matrix *matrix_2x3_load= matrix_load("matrix_2x3.data");
    CU_ASSERT_PTR_NOT_NULL(matrix_2x3_load);
    CU_ASSERT_EQUAL(matrix_get(matrix_2x3_load,0,0),53);
    CU_ASSERT_EQUAL(matrix_get(matrix_2x3_load,1,1),75);
    matrix_free(matrix_2x3_load);
    
    // test matrix load dim(3x2) voir test superieur
    struct matrix *matrix_3x2_load= matrix_load("matrix_3x2.data");
    CU_ASSERT_PTR_NOT_NULL(matrix_3x2_load);
    CU_ASSERT_EQUAL(matrix_get(matrix_3x2_load,0,0),51);
    CU_ASSERT_EQUAL(matrix_get(matrix_3x2_load,2,1),55);
    matrix_free(matrix_3x2_load);
    
    // test matrix load dim(3x3) voir test superieur
    struct matrix *matrix_3x3_load= matrix_load("matrix_3x3.data");
    CU_ASSERT_PTR_NOT_NULL(matrix_3x3_load);
    CU_ASSERT_EQUAL(matrix_get(matrix_3x3_load,0,0),3);
    CU_ASSERT_EQUAL(matrix_get(matrix_3x3_load,1,1),5);
    CU_ASSERT_EQUAL(matrix_get(matrix_3x3_load,2,2),17);
    CU_ASSERT_EQUAL(matrix_get(matrix_3x3_load,2,1),1);
    matrix_free(matrix_3x3_load);
    
    // test matrix load dim(4x2) voir  test superieur
    struct matrix *matrix_4x2_load= matrix_load("matrix_4x2.data");
    CU_ASSERT_PTR_NOT_NULL(matrix_4x2_load);
    CU_ASSERT_EQUAL(matrix_get(matrix_4x2_load,0,0),2236);
    CU_ASSERT_EQUAL(matrix_get(matrix_4x2_load,1,1),1027);
    CU_ASSERT_EQUAL(matrix_get(matrix_4x2_load,2,1),4776);
    CU_ASSERT_EQUAL(matrix_get(matrix_4x2_load,3,1),5390);
    matrix_free(matrix_4x2_load);
    
    // test matrix load dim(4x3) voir  test superieur
    struct matrix *matrix_4x3_load= matrix_load("matrix_4x3.data");
    CU_ASSERT_PTR_NOT_NULL(matrix_4x3_load);
    CU_ASSERT_EQUAL(matrix_get(matrix_4x3_load,0,0),6);
    CU_ASSERT_EQUAL(matrix_get(matrix_4x3_load,1,1),35);
    CU_ASSERT_EQUAL(matrix_get(matrix_4x3_load,2,2),75);
    CU_ASSERT_EQUAL(matrix_get(matrix_4x3_load,0,2),56);
    matrix_free(matrix_4x3_load);
    
    // test avec file pas corrects
    CU_ASSERT_PTR_NULL(matrix_load("./file/IncorrectFile.data"));
    CU_ASSERT_PTR_NULL(matrix_load("IncorrectFile.data"));
}

// sp_matrix and sp_matrix test load
void sp_matrix_test_load(void){
    
    // test sp_matrix load dim(2x1) voir  test superieur
    struct sp_matrix *matrix_2x1_load= sp_matrix_load("matrix_2x1.sp");
    CU_ASSERT_PTR_NOT_NULL(matrix_2x1_load);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_2x1_load,0,0),973);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_2x1_load,1,0),78);
    sp_matrix_free(matrix_2x1_load);
    
    // test sp_matrix load dim(2x3) voir  test superieur
    struct sp_matrix *matrix_2x3_load= sp_matrix_load("matrix_2x3.sp");
		  CU_ASSERT_PTR_NOT_NULL(matrix_2x3_load);
		  CU_ASSERT_EQUAL(sp_matrix_get(matrix_2x3_load,0,0),53);
		  CU_ASSERT_EQUAL(sp_matrix_get(matrix_2x3_load,1,1),75);
    sp_matrix_free(matrix_2x3_load);
    
    // test sp_matrix load dim(3x3) voir  test superieur
    struct sp_matrix *matrix_3x3_load= sp_matrix_load("matrix_3x3.sp");
    CU_ASSERT_PTR_NOT_NULL(matrix_3x3_load);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_3x3_load,0,0),3);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_3x3_load,1,1),5);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_3x3_load,2,2),17);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_3x3_load,2,1),1);
    sp_matrix_free(matrix_3x3_load);
    
    // test matrix load dim(3x2) voir test superieur
    struct sp_matrix *matrix_3x2_load= sp_matrix_load("matrix_3x2.sp");
    CU_ASSERT_PTR_NOT_NULL(matrix_3x2_load);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_3x2_load,0,0),51);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_3x2_load,2,1),55);
    sp_matrix_free(matrix_3x2_load);
    
    // test matrix load dim(4x2) voir  test superieur
    struct sp_matrix *matrix_4x2_load= sp_matrix_load("matrix_4x2.sp");
    CU_ASSERT_PTR_NOT_NULL(matrix_4x2_load);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_4x2_load,0,0),2236);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_4x2_load,1,1),1027);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_4x2_load,2,1),4776);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_4x2_load,3,1),5390);
    sp_matrix_free(matrix_4x2_load);
    
    // test matrix load dim(4x3) voir  test superieur
    struct sp_matrix *matrix_4x3_load= sp_matrix_load("matrix_4x3.sp");
    CU_ASSERT_PTR_NOT_NULL(matrix_4x3_load);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_4x3_load,0,0),6);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_4x3_load,1,1),35);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_4x3_load,2,2),75);
    CU_ASSERT_EQUAL(sp_matrix_get(matrix_4x3_load,0,2),56);
    sp_matrix_free(matrix_4x3_load);
    
    // test matrix load zero matrix dim(4x9)
    
    struct sp_matrix *zeroMatrix_4x9_load= sp_matrix_load("matrix_4x9.sp");
    CU_ASSERT_PTR_NOT_NULL(zeroMatrix_4x9_load);
    CU_ASSERT_EQUAL(sp_matrix_get(zeroMatrix_4x9_load,0,0),0);
    CU_ASSERT_EQUAL(sp_matrix_get(zeroMatrix_4x9_load,3,8),0);
    CU_ASSERT_EQUAL(sp_matrix_get(zeroMatrix_4x9_load,1,7),0);
    CU_ASSERT_EQUAL(sp_matrix_get(zeroMatrix_4x9_load,2,4),0);
    sp_matrix_free(zeroMatrix_4x9_load);
    
    
    
    // test avec file pas corrects
    CU_ASSERT_PTR_NULL(sp_matrix_load("./file/IncorrectFile.data"));
    CU_ASSERT_PTR_NULL(sp_matrix_load("IncorrectFile.data"));
    
}

//----------------- sp_matrix test-----------------------------

//line
void sp_matrix_init_test(void) {
    // creer une matrice de 6x4 avec precision 0.01
    struct sp_matrix* newMatrix_sp0 = sp_matrix_init(0.01, 6,4);
    CU_ASSERT_PTR_NOT_NULL(newMatrix_sp0);
    CU_ASSERT_EQUAL(newMatrix_sp0->nlines,6);
    CU_ASSERT_EQUAL(newMatrix_sp0->ncols,4);
    CU_ASSERT_EQUAL(newMatrix_sp0->precision,0.01);
    CU_ASSERT_PTR_NULL(newMatrix_sp0->lines);
    sp_matrix_free(newMatrix_sp0);
    
    // creer une matrice de 3x7 avec precision 0.01
    struct sp_matrix* newMatrix_sp1 = sp_matrix_init(0.01,3,7);
    CU_ASSERT_PTR_NOT_NULL(newMatrix_sp1);
    CU_ASSERT_EQUAL(newMatrix_sp1->nlines,3);
    CU_ASSERT_EQUAL(newMatrix_sp1->ncols,7);
    CU_ASSERT_EQUAL(newMatrix_sp1->precision,0.01);
    CU_ASSERT_PTR_NULL(newMatrix_sp1->lines);
    sp_matrix_free(newMatrix_sp1);
    
}

//Test  matrix_set
void sp_matrix_check_set(void){
    
    struct sp_matrix *newMatrix = sp_matrix_init(0.01,11,12);
    CU_ASSERT_PTR_NOT_NULL(newMatrix);
    CU_ASSERT_PTR_NULL(newMatrix->lines);
    // non-zero set sur première ligne vide doit créer ligne et élément
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix,5,6,8.0),   0);
    CU_ASSERT_PTR_NOT_NULL(newMatrix->lines);
    CU_ASSERT_PTR_NOT_NULL(newMatrix->lines->elems);
    
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix,1,1,8),     0);
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix,5,2,12),    0);
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix,13,14,12), -1);
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix,11,12,0),  -1);
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix,-1,12,0),  -1);
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix,9,-2,0),   -1);
    CU_ASSERT_EQUAL( sp_matrix_set(NULL,-1,12,0),       -1);
    CU_ASSERT_EQUAL( sp_matrix_set(NULL,1,2,0),         -1);
    
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix,5,6) ,      8);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix,1,1) ,      8);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix,5,2),       12);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix,1,0) ,      0);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix,0,0),       0);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix,10,11),     0);
    
    sp_matrix_free(newMatrix);
    
}

//Test  matrix_set
void sp_matrix_check_set1(void){
    
    struct sp_matrix *newMatrix = sp_matrix_init(0.01,11,12);
    CU_ASSERT_PTR_NOT_NULL(newMatrix);
    CU_ASSERT_PTR_NULL(newMatrix->lines);
    
    // non-zero set sur première ligne vide doit créer ligne et élément
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix,0,0,8),   0);
    CU_ASSERT_PTR_NOT_NULL(newMatrix->lines);
    CU_ASSERT_PTR_NOT_NULL(newMatrix->lines->elems);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix,0,0),       8);
    
    //non-zero set sur dernière ligne vide doit créer ligne et élément
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix,2,0,8),   0);
    CU_ASSERT_PTR_NOT_NULL(newMatrix->lines->next);
    CU_ASSERT_PTR_NOT_NULL(newMatrix->lines->next->elems);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix,2,0),       8);
    
    //non-zero set sur ligne au milieu vide doit créer ligne et élément
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix,1,5,84),   0);
    CU_ASSERT_PTR_NOT_NULL(newMatrix->lines->next->next);
    CU_ASSERT_EQUAL((newMatrix->lines->next->elems->value), 84);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix,1,5),       84);
    CU_ASSERT_EQUAL((newMatrix->lines->next->next->elems->value), 8);
    sp_matrix_free(newMatrix);
    
}


void sp_matrix_check_set1_1(void){
    
    struct sp_matrix *NMatrix = sp_matrix_init(0.01,11,12);
    CU_ASSERT_PTR_NOT_NULL(NMatrix);
    CU_ASSERT_PTR_NULL(NMatrix->lines);
    
    // non-zero set sur ligne existante et premier élément vide doit créer élément
    CU_ASSERT_EQUAL( sp_matrix_set(NMatrix,0,1,1),   0);
    CU_ASSERT_PTR_NOT_NULL(NMatrix->lines);
    CU_ASSERT_PTR_NOT_NULL(NMatrix->lines->elems);
    CU_ASSERT_EQUAL((NMatrix->lines->elems->value), 1);
    CU_ASSERT_EQUAL( sp_matrix_get(NMatrix,0,1),       1);
    
    //  non-zero set sur ligne existante et dernier élément vide doit créer élément
    CU_ASSERT_EQUAL( sp_matrix_set(NMatrix,0,3,3),   0);
    CU_ASSERT_PTR_NOT_NULL(NMatrix->lines->elems->next);
    CU_ASSERT_EQUAL((NMatrix->lines->elems->next->value), 3);
    CU_ASSERT_EQUAL( sp_matrix_get(NMatrix,0,3),       3);
    
    //  non-zero set sur ligne existante et élément milieu vide doit créer élément
    CU_ASSERT_EQUAL( sp_matrix_set(NMatrix,0,2,2),   0);
    CU_ASSERT_PTR_NOT_NULL(NMatrix->lines->elems->next);
    CU_ASSERT_EQUAL( sp_matrix_get(NMatrix,0,2),       2);
    CU_ASSERT_EQUAL((NMatrix->lines->elems->value), 1);
    CU_ASSERT_EQUAL((NMatrix->lines->elems->next->value), 2); // on a bien mis au milieu
    CU_ASSERT_EQUAL((NMatrix->lines->elems->next->next->value), 3);
    
    sp_matrix_free(NMatrix);
    
}
void sp_matrix_check_set2(void){
    
    // sp_matrix pas possible de creer un matrice de dimention 0x0
    struct sp_matrix *newMatrix = sp_matrix_init(0.01,0,0);
    CU_ASSERT_PTR_NULL(newMatrix);
    
    // sp_matrix pas possible de creer un matrice de dimention -7x-1
    struct sp_matrix *newMatrix1 = sp_matrix_init(0.01,-7,-1);
    CU_ASSERT_PTR_NULL(newMatrix1);
    
    // sp_matrix dimention 2x2 set, get , modifier elem
    struct sp_matrix *newMatrix_2x2 = sp_matrix_init(0.01,2,2);
    CU_ASSERT_PTR_NOT_NULL(newMatrix_2x2);
    // double set
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_2x2,0,0,891.4),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_2x2,0,1,2),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_2x2,1,0,14.6),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_2x2,1,1,(-36.2)),	0);
    // respecter imperativement les preconditions
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_2x2,0,0) ,    891.4);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_2x2,0,1) ,    2);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_2x2,1,0),     14.6);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_2x2,1,1) ,    -36.2);
    
    //non-zero set sur élément existant doit modifier l'élément
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix_2x2,1,0,521),	0);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_2x2,1,0) ,    521);
    
    // set zero dans le meme element
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix_2x2,1,0,0),	0);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_2x2,1,0) ,    0);
    
    sp_matrix_free(newMatrix_2x2);
    
    // zero set sur matrice vide ne doit rien faire
    struct sp_matrix *newMatrix_empty = sp_matrix_init(0.01,1,1);
    CU_ASSERT_PTR_NOT_NULL(newMatrix_empty);
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix_empty,0,0,0),	0);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_empty,0,0) ,    0);
    // verifie precision
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix_empty,0,0,0.001),	0);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_empty,0,0) ,    0);
    
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix_empty,0,0,-2.01),	0);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_empty,0,0) ,    -2.01);
    
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix_empty,0,0,-0.001),	0);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_empty,0,0) ,    0);
    
    // verifier que on a pas cree de lignes quand on ajoute zero
    CU_ASSERT_PTR_NULL(newMatrix_empty->lines);
    
    // ajouter un elemnt apres et verifier precision
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix_empty,0,0,0.01),	0);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_empty,0,0) ,    0.01);
    CU_ASSERT_PTR_NOT_NULL(newMatrix_empty->lines);
    CU_ASSERT_PTR_NULL(newMatrix_empty->lines->next);
    CU_ASSERT_PTR_NULL(newMatrix_empty->lines->elems->next);
    sp_matrix_free(newMatrix_empty);
    
    //zero set sur ligne vide ne doit pas créer de ligne
    struct sp_matrix *newMatrix_empty_line = sp_matrix_init(0.01,2,2);
    CU_ASSERT_PTR_NULL(newMatrix_empty_line->lines);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_empty_line,0,0,0.001),	0);
    CU_ASSERT_PTR_NULL(newMatrix_empty_line->lines);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_empty_line,0,0,1),	0);
    CU_ASSERT_PTR_NULL(newMatrix_empty_line->lines->next);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_empty_line,1,0,0.001),	0);
    CU_ASSERT_PTR_NULL(newMatrix_empty_line->lines->next);
    sp_matrix_free(newMatrix_empty_line);
    
}

void sp_matrix_check_set3(void){
    
    struct sp_matrix *newMat = sp_matrix_init(0.01,1,2);
    CU_ASSERT_PTR_NOT_NULL(newMat);
    CU_ASSERT_EQUAL( sp_matrix_set(newMat,0,0,1),	0);
    CU_ASSERT_EQUAL( sp_matrix_get(newMat,0,0) ,    1);
    // change  val du newMat(0,0)
    CU_ASSERT_EQUAL( sp_matrix_set(newMat,0,0,2),	0);
    CU_ASSERT_EQUAL( sp_matrix_get(newMat,0,0) ,    2);
    // zero set sur élément existant doit supprimer l'élément
    CU_ASSERT_EQUAL( sp_matrix_set(newMat,0,1,3),	0);
    CU_ASSERT_EQUAL( sp_matrix_get(newMat,0,1) ,    3);
    CU_ASSERT_PTR_NOT_NULL(newMat->lines->elems->next);
    CU_ASSERT_EQUAL( sp_matrix_set(newMat,0,1,0.000000001),	0);
    CU_ASSERT_PTR_NULL(newMat->lines->elems->next);
    sp_matrix_free(newMat);
}

void sp_matrix_check_set4(void){
    // zero set sur un élément existant unique d'une ligne doit supprimer élément et ligne
    // cettte ligne est la prmier ligne
    struct sp_matrix *THMatrix = sp_matrix_init(0.01,2,2);
    CU_ASSERT_PTR_NOT_NULL(THMatrix);
    // double set
    CU_ASSERT_EQUAL(sp_matrix_set(THMatrix,0,0,5),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(THMatrix,1,0,34),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(THMatrix,1,1,9),	0);
    // respecter imperativement les preconditions
    CU_ASSERT_EQUAL( sp_matrix_get(THMatrix,0,0) ,    5);
    CU_ASSERT_EQUAL( sp_matrix_get(THMatrix,0,1) ,    0);
    CU_ASSERT_EQUAL( sp_matrix_get(THMatrix,1,0),     34);
    CU_ASSERT_EQUAL( sp_matrix_get(THMatrix,1,1) ,    9);
    
    CU_ASSERT_PTR_NULL(THMatrix->lines->next->next);
    CU_ASSERT_PTR_NOT_NULL(THMatrix->lines->next);
    CU_ASSERT_PTR_NULL(THMatrix->lines->elems->next);
    
    CU_ASSERT_EQUAL(sp_matrix_set(THMatrix,0,0,0),	0);
    
    // apres set 0 dans THMatrix(1.0) verifier si on a bien elimie la ligne
    CU_ASSERT_PTR_NOT_NULL(THMatrix->lines);
    CU_ASSERT_PTR_NULL(THMatrix->lines->next);
    CU_ASSERT_PTR_NOT_NULL(THMatrix->lines->elems->next);
    
    CU_ASSERT_EQUAL( sp_matrix_get(THMatrix,0,0) ,    0);
    CU_ASSERT_EQUAL( sp_matrix_get(THMatrix,0,1) ,    0);
    CU_ASSERT_EQUAL( sp_matrix_get(THMatrix,1,0),     34);
    CU_ASSERT_EQUAL( sp_matrix_get(THMatrix,1,1) ,    9);
    sp_matrix_free(THMatrix);
    
    // zero set sur un élément existant unique d'une ligne doit supprimer élément et ligne
    // cettte ligne est la dernier ligne
    struct sp_matrix *newMatrix_2 = sp_matrix_init(0.01,2,2);
    CU_ASSERT_PTR_NOT_NULL(newMatrix_2);
    // double set
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_2,0,0,91),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_2,0,1,2),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_2,1,0,14),	0);
    // respecter imperativement les preconditions
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_2,0,0) ,    91);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_2,0,1) ,    2);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_2,1,0),     14);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_2,1,1) ,    0);
    
    CU_ASSERT_PTR_NULL(newMatrix_2->lines->next->next);
    CU_ASSERT_PTR_NOT_NULL(newMatrix_2->lines->next);
    
    CU_ASSERT_EQUAL( sp_matrix_set(newMatrix_2,1,0,0) ,    0);
    // apres set 0 dans newMatrix_2(1.0)
    CU_ASSERT_PTR_NOT_NULL(newMatrix_2->lines);
    CU_ASSERT_PTR_NULL(newMatrix_2->lines->next);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_2,0,0) ,    91);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_2,0,1) ,    2);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_2,1,0),     0);
    CU_ASSERT_EQUAL( sp_matrix_get(newMatrix_2,1,1) ,    0);
    sp_matrix_free(newMatrix_2);
    
    // zero set sur un élément existant unique d'une ligne doit supprimer élément et ligne
    // cettte ligne est une au milieux de la matrix
    struct sp_matrix *Mtrix_Mid = sp_matrix_init(0.01,3,2);
    CU_ASSERT_PTR_NOT_NULL(Mtrix_Mid);
    // double set
    CU_ASSERT_EQUAL(sp_matrix_set(Mtrix_Mid,0,0,5),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(Mtrix_Mid,0,1,6),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(Mtrix_Mid,1,0,7),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(Mtrix_Mid,2,0,9),	0);
    
    // respecter imperativement les preconditions
    CU_ASSERT_EQUAL( sp_matrix_get(Mtrix_Mid,0,0) ,    5);
    CU_ASSERT_EQUAL( sp_matrix_get(Mtrix_Mid,0,1) ,    6);
    CU_ASSERT_EQUAL( sp_matrix_get(Mtrix_Mid,1,0),     7);
    CU_ASSERT_EQUAL( sp_matrix_get(Mtrix_Mid,2,0) ,    9);
    
    CU_ASSERT_PTR_NULL(Mtrix_Mid->lines->next->next->next);
    CU_ASSERT_PTR_NOT_NULL(Mtrix_Mid->lines->next->next);
    
    CU_ASSERT_EQUAL( sp_matrix_set(Mtrix_Mid,1,0,0) ,    0);
    // apres set 0 dans Mtrix_Mid(1.0)
    CU_ASSERT_PTR_NOT_NULL(Mtrix_Mid->lines);
    CU_ASSERT_PTR_NULL(Mtrix_Mid->lines->next->next);
    CU_ASSERT_EQUAL( sp_matrix_get(Mtrix_Mid,0,0) ,    5);
    CU_ASSERT_EQUAL( sp_matrix_get(Mtrix_Mid,0,1) ,    6);
    CU_ASSERT_EQUAL( sp_matrix_get(Mtrix_Mid,1,0),     0);
    CU_ASSERT_EQUAL( sp_matrix_get(Mtrix_Mid,1,1) ,    0);
    CU_ASSERT_EQUAL( sp_matrix_get(Mtrix_Mid,2,0) ,    9);
    CU_ASSERT_EQUAL( sp_matrix_get(Mtrix_Mid,2,1) ,    0);
    sp_matrix_free(Mtrix_Mid);
}


void sp_matrix_check_set5(void){
    // zero set sur un élément existant unique d'une ligne unique doit supprimer l'élément,
    // la ligne et mettre m->lines à NULL
    struct sp_matrix *Matrx_Line_Unique = sp_matrix_init(0.01,3,2);
    CU_ASSERT_PTR_NOT_NULL(Matrx_Line_Unique);
    // double set
    CU_ASSERT_EQUAL(sp_matrix_set(Matrx_Line_Unique,2,0,9),	0);
    
    // respecter imperativement les preconditions
    CU_ASSERT_EQUAL( sp_matrix_get(Matrx_Line_Unique,2,0) ,    9);
    
    CU_ASSERT_PTR_NOT_NULL(Matrx_Line_Unique->lines);
    CU_ASSERT_PTR_NULL(Matrx_Line_Unique->lines->next);
    CU_ASSERT_PTR_NOT_NULL(Matrx_Line_Unique->lines->elems);
    CU_ASSERT_PTR_NULL(Matrx_Line_Unique->lines->elems->next);
    
    CU_ASSERT_EQUAL( sp_matrix_set(Matrx_Line_Unique,2,0,0) ,    0);
    // apres set 0 dans Matrx_Line_Unique(1.0)
    CU_ASSERT_PTR_NULL(Matrx_Line_Unique->lines);
    CU_ASSERT_EQUAL( sp_matrix_get(Matrx_Line_Unique,1,1) ,    0);
    CU_ASSERT_EQUAL( sp_matrix_get(Matrx_Line_Unique,2,0) ,    0);
    CU_ASSERT_EQUAL( sp_matrix_get(Matrx_Line_Unique,2,1) ,    0);
    sp_matrix_free(Matrx_Line_Unique);
}

// Test  matrix_get
void sp_matrix_check_get(void){
    struct sp_matrix *sp_newMatrix = sp_matrix_init(0.01, 5,6);
    // get  un element sur un matrice vide dois retourner 0
    CU_ASSERT_EQUAL(sp_matrix_get(sp_newMatrix,2,3),0);
    sp_matrix_free(sp_newMatrix);
    
    struct sp_matrix *sp_newMatrix_3x3 = sp_matrix_init(0.01,3,3);
    CU_ASSERT_PTR_NOT_NULL(sp_newMatrix_3x3);
    //ligne 1
    CU_ASSERT_EQUAL(sp_matrix_set(sp_newMatrix_3x3,0,0,1),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(sp_newMatrix_3x3,0,1,2),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(sp_newMatrix_3x3,0,2,3),	0);
    // ligne 2
    CU_ASSERT_EQUAL(sp_matrix_set(sp_newMatrix_3x3,1,0,4),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(sp_newMatrix_3x3,1,1,5),	0);
    // ligne 3 null
    
    // respecter imperativement les preconditions
    //GET 01: get sur un élément non-nul en début de ligne
    CU_ASSERT_EQUAL( sp_matrix_get(sp_newMatrix_3x3,0,0) ,    1);
    //GET 02: get sur un élément non-nul au milieu de ligne
    CU_ASSERT_EQUAL( sp_matrix_get(sp_newMatrix_3x3,0,1) ,    2);
    //GET 03: get sur un élément non-nul en fin de ligne
    CU_ASSERT_EQUAL( sp_matrix_get(sp_newMatrix_3x3,0,2),     3);
    //GET 04: get sur un élément nul doit retourner 0
    CU_ASSERT_EQUAL( sp_matrix_get(sp_newMatrix_3x3,1,2) ,    0);
    //GET 05: get sur un élément d'une ligne nulle doit retourner 0
    CU_ASSERT_EQUAL( sp_matrix_get(sp_newMatrix_3x3,2,1) ,    0);
    sp_matrix_free(sp_newMatrix_3x3);
}

//Test matrix_add
void sp_matrix_add_null_test(void){
    
    // ADD 01: additionner NULL
    struct sp_matrix* Mm1= NULL;
    struct sp_matrix* Mm2= sp_matrix_init(0.03, 3,4);
    struct sp_matrix* Mm12= sp_matrix_add(Mm1,Mm2);
    CU_ASSERT_PTR_NULL(Mm12);
    sp_matrix_free(Mm2);
    
    struct sp_matrix* Mv2= NULL;
    struct sp_matrix* Mv1= sp_matrix_init(0.03, 3,4);
    struct sp_matrix* Mv12= sp_matrix_add(Mv1,Mv2);
    CU_ASSERT_PTR_NULL(Mv12);
    sp_matrix_free(Mv1);
    
    struct sp_matrix* m1= NULL;
    struct sp_matrix* m2= NULL;
    struct sp_matrix* m12= sp_matrix_add(m1,m2);
    CU_ASSERT_PTR_NULL(m12);
}

void sp_matrix_add_test(void){
    
    // ADD 01: additionner deux sp_matrices vides doit donner une matrice vide
    struct sp_matrix* M1= sp_matrix_init(0.01, 4,4);
    struct sp_matrix* M2= sp_matrix_init(0.03, 4,4);
    struct sp_matrix* M12= sp_matrix_add(M1,M2);
    CU_ASSERT_PTR_NULL(M12->lines);
    sp_matrix_free(M1);
    sp_matrix_free(M2);
    sp_matrix_free(M12);
    // ADD 04: si M1 et M2 sont de tailles différentes, add doit retourner NULL
    struct sp_matrix* A_2x2= sp_matrix_init(0.01,2,2);
    struct sp_matrix* B_3x2= sp_matrix_init(0.001,3,2);
    struct sp_matrix* AB= sp_matrix_add(A_2x2,B_3x2);
    CU_ASSERT_PTR_NULL(AB);
    sp_matrix_free(A_2x2);
    sp_matrix_free(B_3x2);
    // ADD 04.1: si M1 et M2 sont de tailles différentes, add doit retourner NULL
    struct sp_matrix* A_1x1= sp_matrix_init(0.01,1,1);
    struct sp_matrix* B_1x24= sp_matrix_init(0.001,1,24);
    struct sp_matrix* AB1= sp_matrix_add(A_1x1,B_1x24);
    CU_ASSERT_PTR_NULL(AB1);
    sp_matrix_free(A_1x1);
    sp_matrix_free(B_1x24);
    
}

void sum_test_precision(void){
    // ADD 09: une addition non-nulle doit être correcte
    struct sp_matrix* matrixA= sp_matrix_init(1,2,2);
    struct sp_matrix* matrixB= sp_matrix_init(0.001, 2,2);
    
    CU_ASSERT_EQUAL(sp_matrix_set(matrixA,0,0,2),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixA,0,1,3),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixA,1,0,1),	0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,0,0,0.001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,0,1,0.001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,1,0,0.001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,1,1,0.001),	0);
    
    struct sp_matrix* matrixSummAB= sp_matrix_add(matrixA,matrixB);
    struct sp_matrix* matrixSummBA= sp_matrix_add(matrixB,matrixA);
    
    // ADD 03: commutativité (M1 + M2 == M2 + M1)
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB,0,0),2.001);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB,0,1),3.001);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB,1,0),1.001);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB,1,1),0);
    
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,0,0),2.001);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,0,1),3.001);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,1,0),1.001);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,1,1),0);
    
    sp_matrix_free(matrixA);
    sp_matrix_free(matrixB);
    sp_matrix_free(matrixSummAB);
    sp_matrix_free(matrixSummBA);
}


void sum_test_precision2(void){
    //A p=0.01
    // 0.01     -0.01
    // -3.01     3.01
    
    // B p=0.001
    // 0.001 	 0.001
    // 3.001 	-3.001
    
    // A+B p=0.01  // verifier precision apres la summ
    // 0.011   0
    // 0 	   0
    
    // ADD 09: une addition non-nulle doit être correcte
    struct sp_matrix* matrixA= sp_matrix_init(0.01,2,2);
    struct sp_matrix* matrixB= sp_matrix_init(0.001, 2,2);
    
    CU_ASSERT_EQUAL(sp_matrix_set(matrixA,0,0,0.01),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixA,0,1,-0.01),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixA,1,0,-3.01),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixA,1,1, 3.01),	0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,0,0,0.001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,0,1,0.001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,1,0,3.001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,1,1,-3.001),	0);
    
    struct sp_matrix* matrixSummAB= sp_matrix_add(matrixA,matrixB);
    struct sp_matrix* matrixSummBA= sp_matrix_add(matrixB,matrixA);
    
    // ADD 08: une addition non-nulle doit créer un élément
    CU_ASSERT_PTR_NOT_NULL(matrixSummAB->lines->elems); // prmier element a ete cree
    
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB,0,0),0.011);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB,0,1),0);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB,1,0),0);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB,1,1),0);
    
    // ADD 05: une addition nulle (a + b = 0) ne doit pas créer d'élément
    CU_ASSERT_PTR_NULL(matrixSummAB->lines->elems->next); // ne dois pas cree le deuxiem elem
    // ADD 06: une addition résultant à une ligne nulle ne doit pas créer de ligne
    CU_ASSERT_PTR_NULL(matrixSummAB->lines->next); // ne dois pas cree la deuxiem ligne
    
    // ADD 03: commutativité (M1 + M2 == M2 + M1)
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,0,0),0.011);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,0,1),0);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,1,0),0);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,1,1),0);
    
    // ADD 05: une addition nulle (a + b = 0) ne doit pas créer d'élément en dependnce du precision
    CU_ASSERT_PTR_NULL(matrixSummBA->lines->elems->next); // ne dois pas cree le deuxiem elem
    // ADD 06: une addition résultant à une ligne nulle ne doit pas créer de ligne
    CU_ASSERT_PTR_NULL(matrixSummBA->lines->next); // ne dois pas cree la deuxiem ligne
    
    sp_matrix_free(matrixA);
    sp_matrix_free(matrixB);
    sp_matrix_free(matrixSummAB);
    sp_matrix_free(matrixSummBA);
}

void sum_test_precision3(void){
    //A p=0.01
    // 0.01  -0.013
    // 0     -3.01
    
    // B p=0.001
    // donc ici ==> B=0 pour la precision
    // 0.0001 	0.0001
    // 0.0001 	0.0001
    
    // A+B p=0.01  // verifier precision apres la summ
    // 0.01  -0.013
    // 0     -3.01
    // A+B= A parce que B=0 pour la precision
    
    // ADD 02: additionner une matrice B vide et une A non-vide (p(B) < p(A) ) doit donner A
    struct sp_matrix* matrixA= sp_matrix_init(0.01,2,2);
    struct sp_matrix* matrixB= sp_matrix_init(0.001, 2,2);
    
    CU_ASSERT_EQUAL(sp_matrix_set(matrixA,0,0, 0.01),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixA,0,1, -0.013),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixA,1,1, -3.01),	0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,0,0, 0.0001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,0,1, 0.0001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,1,0, 0.0001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,1,1, 0.0001),	0);
    
    struct sp_matrix* matrixSummAB= sp_matrix_add(matrixA,matrixB);
    struct sp_matrix* matrixSummBA= sp_matrix_add(matrixB,matrixA);
    
    // ADD 03: commutativité (M1 + M2 == M2 + M1)
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB, 0,0),0.01);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB, 0,1),-0.013);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB, 1,0),0);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB, 1,1),-3.01);
    
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,0,0),0.01);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,0,1),-0.013);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,1,0),0);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,1,1),-3.01);
    
    sp_matrix_free(matrixA);
    sp_matrix_free(matrixB);
    sp_matrix_free(matrixSummAB);
    sp_matrix_free(matrixSummBA);
}

void sum_test_precision4(void){
    //A p=0.01
    // 0    0
    // 0    0
    
    // B p=0.0001
    // 0.0001 	-0.0001
    // 0.0001 	0.0001
    
    // A+B p=0.01  // verifier precision apres la summ
    // 0   0
    // 0 	0
    
    // ADD 02: additionner une matrice M1 vide et une M2 non-vide (p(M1) > p(M2) ) doit donner M1 (vide)
    struct sp_matrix* matrixA= sp_matrix_init(0.01,2,2);
    struct sp_matrix* matrixB= sp_matrix_init(0.001, 2,2);
    
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,0,0,0.0001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,0,1,-0.0001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,1,0,0.0001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,1,1,0.0001),	0);
    
    struct sp_matrix* matrixSummAB= sp_matrix_add(matrixA,matrixB);
    struct sp_matrix* matrixSummBA= sp_matrix_add(matrixB,matrixA);
    
    // ADD 03: commutativité (M1 + M2 == M2 + M1)
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB,0,0),0);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB,0,1),0);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB,1,0),0);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummAB,1,1),0);
    
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,0,0),0);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,0,1),0);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,1,0),0);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixSummBA,1,1),0);
    
    // ADD 07: une addition résultat à une matrice nulle doit avoir m->lines = NULL
    CU_ASSERT_PTR_NULL(matrixSummAB->lines);
    CU_ASSERT_PTR_NULL(matrixSummBA->lines);
    
    sp_matrix_free(matrixA);
    sp_matrix_free(matrixB);
    sp_matrix_free(matrixSummAB);
    sp_matrix_free(matrixSummBA);
}

//Test Transpose
void sp_matrix_check_transpose(void){
    // TRANSPOSE 01: la transposée d'une matrice vide doit être vide
    struct sp_matrix* MA= sp_matrix_init(0.01,2,2);
    CU_ASSERT_PTR_NULL(MA->lines);
    struct sp_matrix* matrixT_A= sp_matrix_transpose(MA);
    CU_ASSERT_PTR_NULL(matrixT_A->lines);
    sp_matrix_free(MA);
    sp_matrix_free(matrixT_A);
    
    // TRANSPOSE 02: la transposée doit avoir des valeurs correctes
    struct sp_matrix *matrixAA = sp_matrix_init(0.01,2,3);
    
    CU_ASSERT_PTR_NOT_NULL(matrixAA);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixAA,0,0,1),0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixAA,0,1,2),0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixAA,0,2,3),0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(matrixAA,1,0,4),0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixAA,1,1,5),0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixAA,1,2,6),0);
    
    struct sp_matrix *matrixT = sp_matrix_transpose(matrixAA);
    CU_ASSERT_PTR_NOT_NULL(matrixT);
    
    CU_ASSERT_EQUAL(sp_matrix_get(matrixT,0,0),1);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixT,0,1),4);
    
    CU_ASSERT_EQUAL(sp_matrix_get(matrixT,1,0),2);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixT,1,1),5);
    
    CU_ASSERT_EQUAL(sp_matrix_get(matrixT,2,0),3);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixT,2,1),6);
    sp_matrix_free(matrixT);
    //transpose d'une matrice NULL
    //CU_ASSERT_PTR_NULL(matrix_transpose(NULL));
    sp_matrix_free(matrixAA);
    
    
    //TRANSPOSE 03: la transposée d'une colonne nulle doit donner une ligne non-existante
    struct sp_matrix* matrixB= sp_matrix_init(0.001, 2,2);
    
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,0,0,1),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixB,1,0,4),	0);
    
    CU_ASSERT_EQUAL(sp_matrix_get(matrixB,0,0),1);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixB,0,1),0);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixB,1,0),4);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixB,1,1),0);
    CU_ASSERT_PTR_NOT_NULL(matrixB->lines->next);
    
    struct sp_matrix* TB= sp_matrix_transpose(matrixB);
    
    CU_ASSERT_EQUAL(sp_matrix_get(TB,0,0),1);
    CU_ASSERT_EQUAL(sp_matrix_get(TB,0,1),4);
    CU_ASSERT_EQUAL(sp_matrix_get(TB,1,0),0);
    CU_ASSERT_EQUAL(sp_matrix_get(TB,1,1),0);
    
    CU_ASSERT_PTR_NULL(TB->lines->next);
    
    sp_matrix_free(matrixB);
    sp_matrix_free(TB);
}


void sp_matrix_check_transpose2(void){
    // TRANSPOSE 02.1: la transposée doit avoir des valeurs correctes
    struct sp_matrix *matrixAA = sp_matrix_init(0.001,3,3);
    
    CU_ASSERT_PTR_NOT_NULL(matrixAA);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixAA,0,0,0.001),0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixAA,0,1,4),0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixAA,0,2,-0.01),0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(matrixAA,1,0,6),0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixAA,1,2,7),0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(matrixAA,2,0,-37.9),0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixAA,2,1,3),0);
    
    struct sp_matrix *matrixT = sp_matrix_transpose(matrixAA);
    
    CU_ASSERT_EQUAL(sp_matrix_set(matrixT,0,0,0.001),0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixT,1,0,4),0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixT,2,0,-0.01),0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(matrixT,0,1,6),0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixT,2,1,7),0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(matrixT,0,2,-37.9),0);
    CU_ASSERT_EQUAL(sp_matrix_set(matrixT,1,2,3),0);
    
    //transpose d'une matrice NULL
    // CU_ASSERT_PTR_NULL(matrix_transpose(NULL));
    sp_matrix_free(matrixT);
    sp_matrix_free(matrixAA);
}


//---------------------MUlT SP-----------------------------
//Test matrix_mult
void sp_matrix_mult_nxn_test(void){
    struct sp_matrix *newMatrixA_3x3= sp_matrix_init(0.001, 3, 3);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixA_3x3,0,0,3),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixA_3x3,0,1,4),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixA_3x3,0,2,5),	0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixA_3x3,1,0,1),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixA_3x3,1,1,5),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixA_3x3,1,2,7),	0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixA_3x3,2,0,9),   0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixA_3x3,2,1,1),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixA_3x3,2,2,7),	0);
    
    struct sp_matrix *newMatrixB_3x3= sp_matrix_init(0.01,3, 3);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixB_3x3,0,0,5),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixB_3x3,0,1,9),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixB_3x3,0,2,7),	0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixB_3x3,1,0,3),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixB_3x3,1,1,1),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixB_3x3,1,2,7),	0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrixB_3x3,2,0,9),   0);
    
    struct sp_matrix* matrixMult= sp_matrix_mult(newMatrixA_3x3,newMatrixB_3x3);
    
    CU_ASSERT_EQUAL(sp_matrix_get(matrixMult,0,0),72);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixMult,1,0),83);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixMult,2,0),111);
    
    sp_matrix_free(newMatrixA_3x3);
    sp_matrix_free(newMatrixB_3x3);
    sp_matrix_free(matrixMult);
}

void sp_matrix_mult_nxm_test(void){
    struct sp_matrix *newMatrix_4x3 = sp_matrix_init(0.01,4,3);
    // double set
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_4x3,0,0,6),		0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_4x3,0,1,46),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_4x3,0,2,56),	0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_4x3,1,0,13),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_4x3,1,1,35),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_4x3,1,2,7),		0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_4x3,2,0,49),    0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_4x3,2,1,14),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_4x3,2,2,75),	0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_4x3,3,0,0),		0); // pas necesaire
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_4x3,3,1,99),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_4x3,3,2,71),	0);
    
    struct sp_matrix *newMatrix_3x2 = sp_matrix_init(0.01,3,2);
    // double set
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x2,0,0,51),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x2,0,1,9),	0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x2,1,0,31),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x2,1,1,15),	0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x2,2,0,9),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x2,2,1,55),	0);
    
    struct sp_matrix* matrixMult= sp_matrix_mult(newMatrix_4x3,newMatrix_3x2);
    //Matrix result of multiplication
    //2236	3824
    //1811	1027
    //3608	4776
    //3708	5390
    
    CU_ASSERT_EQUAL(sp_matrix_get(matrixMult,0,0),2236);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixMult,1,0),1811);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixMult,2,0),3608);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixMult,3,0),3708);
    
    sp_matrix_free(newMatrix_4x3);
    sp_matrix_free(newMatrix_3x2);
    sp_matrix_free(matrixMult);
}


void sp_matrix_mult_mxn_test(void){
    // une matrice non sero
   	struct sp_matrix *newMatrix_3x3= sp_matrix_init(0.001, 3,3);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x3,0,0,0.001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x3,0,1,0.001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x3,0,2,0.001),	0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x3,1,0,6),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x3,1,1,0.0001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x3,1,2,7),	0);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x3,2,0,-37.9),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x3,2,1,3),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x3,2,2,-0.0001),	0);
    
    // une matrice presque egale 0
   	struct sp_matrix *newMatrix_3x1= sp_matrix_init(0.00001, 3, 1);
    // convert a zero matrix
   	struct matrix *zeroMatrix= sp_matrix_to_matrix(newMatrix_3x1);
    CU_ASSERT_EQUAL(matrix_get(zeroMatrix,0,0), 0);
    CU_ASSERT_EQUAL(matrix_get(zeroMatrix,1,0), 0);
    CU_ASSERT_EQUAL(matrix_get(zeroMatrix,2,0), 0);
   	matrix_free(zeroMatrix);
    
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x1,0,0,-0.00001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x1,1,0,-0.00001),	0);
    CU_ASSERT_EQUAL(sp_matrix_set(newMatrix_3x1,2,0,-0.00001),	0);
    
    // M1* M2(presque zero)= zero
    struct sp_matrix* matrixMult= sp_matrix_mult(newMatrix_3x3,newMatrix_3x1);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixMult,0,0),0);
    CU_ASSERT_EQUAL(sp_matrix_get(matrixMult,1,0),0);
    
    //_________________________CONVERT TEST______________________________________
    //CONVERT 01: la matrice résultante doit avoir des valeurs correctes
    struct matrix *matrix= sp_matrix_to_matrix(newMatrix_3x3);
    CU_ASSERT_PTR_NOT_NULL(matrix);
    CU_ASSERT_EQUAL(matrix_get(matrix,0,0), 0.001);
    CU_ASSERT_EQUAL(matrix_get(matrix,0,1), 0.001);
    CU_ASSERT_EQUAL(matrix_get(matrix,0,2), 0.001);
    
    CU_ASSERT_EQUAL(matrix_get(matrix,1,0), 6);
    CU_ASSERT_EQUAL(matrix_get(matrix,1,1), 0);
    CU_ASSERT_EQUAL(matrix_get(matrix,1,2), 7);
    
    CU_ASSERT_EQUAL(matrix_get(matrix,2,0), -37.9);
    CU_ASSERT_EQUAL(matrix_get(matrix,2,1), 3);
    CU_ASSERT_EQUAL(matrix_get(matrix,2,2), 0);
    
    matrix_free(matrix);
    sp_matrix_free(newMatrix_3x3);
    sp_matrix_free(newMatrix_3x1);
    sp_matrix_free(matrixMult);
    
    
    // convert matrix NULL;
    struct matrix *matrix_NULL= sp_matrix_to_matrix(NULL);
    CU_ASSERT_PTR_NULL(matrix_NULL);
    
    struct sp_matrix *sp_matrix_NULL= matrix_to_sp_matrix(NULL,0.01);
    CU_ASSERT_PTR_NULL(sp_matrix_NULL);
    
    struct sp_matrix *sp_matrix_empty= matrix_to_sp_matrix(NULL,0.01);
    CU_ASSERT_PTR_NULL(sp_matrix_empty);
    //CONVERT 02: convert doit retourner NULL si malloc échoue
}

///Test Convert
void convert(void){
    // convert empty matrix
    struct sp_matrix *newMatrix_3x3= sp_matrix_init(0.001, 3,3);
    //sp_matrix to matrix
    struct matrix *matrix_empty= sp_matrix_to_matrix(newMatrix_3x3);
    CU_ASSERT_EQUAL(matrix_get(matrix_empty,0,0), 0);
    
    // matrix to sp_marix
    struct sp_matrix *sp_newMatrix_empty = matrix_to_sp_matrix(matrix_empty, 0.01);
    CU_ASSERT_PTR_NULL(sp_newMatrix_empty->lines);   
    
    sp_matrix_free(newMatrix_3x3);
    sp_matrix_free(sp_newMatrix_empty);
    matrix_free(matrix_empty);
}

//main executer TEST
int main(void){
    CU_pSuite pSuite = NULL;
    
    if (CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }
    
    pSuite = CU_add_suite("test_creuses_matrix",NULL,NULL);
    if (pSuite == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (
        /* Test pour struct matrix */
        (NULL == CU_add_test(pSuite, "matrix_init_lines", matrix_init_test_lines))  ||
        (NULL == CU_add_test(pSuite, "matrix_init_cols", matrix_init_test_cols))    ||
        (NULL == CU_add_test(pSuite, "matrix_init_zero", matrix_init_zero))         ||
        (NULL == CU_add_test(pSuite, "matrix_get", matrix_test_get))                ||
        (NULL == CU_add_test(pSuite, "matrix_set", matrix_check_set))               ||
        (NULL == CU_add_test(pSuite, "matrix_add", matrix_add_test))                ||
        (NULL == CU_add_test(pSuite, "matrix_add_null", matrix_add_test_null))      ||
        (NULL == CU_add_test(pSuite, "matrix_tranpose", matrix_check_transpose))    ||
        (NULL == CU_add_test(pSuite, "matrix_mult_nxn_test", matrix_mult_nxn_test)) ||
        (NULL == CU_add_test(pSuite, "matrix_mult_nxm_test", matrix_mult_nxm_test)) ||
        (NULL == CU_add_test(pSuite, "matrix_mult_mxn", matrix_mult_mxn_test))      ||
        
        /* Test pour struct sp_matrix */
        (NULL == CU_add_test(pSuite, "sp_matrix_init_test", sp_matrix_init_test))    			 ||
        (NULL == CU_add_test(pSuite, "sp_matrix_check_test", sp_matrix_check_set))	 			 ||
        (NULL == CU_add_test(pSuite, "sp_matrix_check_set1", sp_matrix_check_set1))		 		 ||
        (NULL == CU_add_test(pSuite, "sp_matrix_check_set1_1", sp_matrix_check_set1_1))	 		 ||
        (NULL == CU_add_test(pSuite, "sp_matrix_check_set2", sp_matrix_check_set2))		 		 ||
        (NULL == CU_add_test(pSuite, "sp_matrix_check_set3", sp_matrix_check_set3))		 		 ||
        (NULL == CU_add_test(pSuite, "sp_matrix_check_set4", sp_matrix_check_set4))		 		 ||
        (NULL == CU_add_test(pSuite, "sp_matrix_check_set5", sp_matrix_check_set5))		 		 ||
        (NULL == CU_add_test(pSuite, "sp_matrix_check_get", sp_matrix_check_get)) 			 	 ||
        (NULL == CU_add_test(pSuite, "sp_matrix_add_null_test", sp_matrix_add_null_test))        ||
        (NULL == CU_add_test(pSuite, "sum_test_precision", sum_test_precision))					 ||
        (NULL == CU_add_test(pSuite, "sum_test_precision2", sum_test_precision2))				 ||
        (NULL == CU_add_test(pSuite, "sum_test_precision3", sum_test_precision3)) 				 ||
        (NULL == CU_add_test(pSuite, "sum_test_precision4", sum_test_precision4))				 ||
        (NULL == CU_add_test(pSuite, "sp_matrix_add_test", sp_matrix_add_test))              	 ||
        (NULL == CU_add_test(pSuite, "sp_matrix_check_transpose", sp_matrix_check_transpose))    ||
        (NULL == CU_add_test(pSuite, "sp_matrix_check_transpose2", sp_matrix_check_transpose2))  ||
        (NULL == CU_add_test(pSuite, "sp_matrix_mult_nxn_test", sp_matrix_mult_nxn_test))   	 ||
        (NULL == CU_add_test(pSuite, "sp_matrix_mult_nxm_test", sp_matrix_mult_nxm_test))   	 ||
        (NULL == CU_add_test(pSuite, "sp_matrix_mult_mxn_test", sp_matrix_mult_mxn_test))		 ||
        (NULL == CU_add_test(pSuite, "convert", convert))				     					 ||
        
        (NULL == CU_add_test(pSuite, "test_save", test_save))        							 ||
        (NULL == CU_add_test(pSuite, "matrix_test_load", matrix_test_load))        				 ||
        (NULL == CU_add_test(pSuite, "sp_matrix_test_load", sp_matrix_test_load))
        ){
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    CU_basic_run_tests();
    CU_basic_show_failures(CU_get_failure_list());
    CU_cleanup_registry();
    return CU_get_error();
    
}

