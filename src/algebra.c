#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    if (a.rows != b.rows || a.cols != b.cols) {
        fprintf(stderr, "Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    if (a.rows != b.rows || a.cols != b.cols) {
        fprintf(stderr, "Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return result;
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    if (a.cols != b.rows) {
        fprintf(stderr, "Error: Matrix a's column count must match matrix b's row count.\n");
        return create_matrix(0, 0);
    }
    
    Matrix result = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < a.cols; k++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

Matrix scale_matrix(Matrix a, double k)
{
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] * k;
        }
    }
    return result;
}

Matrix transpose_matrix(Matrix a)
{
    Matrix result = create_matrix(a.cols, a.rows);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[j][i] = a.data[i][j];
        }
    }
    return result;
}

double det_matrix(Matrix a)
{
    if (a.rows != a.cols) {
     printf("Error: Matrix must be square.\n");
     return 0;
    }
    if (a.rows == 1) {
    return a.data[0][0];
    }
    if (a.rows == 2) {
    return a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];
    }
    double det = 0;
    Matrix submatrix = create_matrix(a.rows - 1, a.cols - 1);
    int i; int j;
    for (i = 0; i < a.cols; i++) {
    int subi = 0;
    for (j = 1; j < a.rows; j++) {
    int subj = 0;
    int k;
    for (k = 0; k < a.cols; k++) {
    if (k == i) continue;
    submatrix.data[subi][subj] = a.data[j][k];
    subj++;
    }
    subi++;
    }
    double sign = (i % 2 == 0) ? 1 : -1;
    det += sign * a.data[0][i] * det_matrix(submatrix);
    }
    return det;
}

Matrix inv_matrix(Matrix a)
{
    if (a.rows != a.cols) {
        fprintf(stderr, "Error: Matrix must be square to calculate inverse.\n");
        return create_matrix(0, 0);
    }
    
    int n = a.rows;
    double det = det_matrix(a);
    
    if (fabs(det) < 1e-10) {
        fprintf(stderr, "Error: Matrix is singular and does not have an inverse.\n");
        return create_matrix(0, 0);
    }
    
    Matrix result = create_matrix(n, n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // 创建代数余子式矩阵
            Matrix sub = create_matrix(n-1, n-1);
            int sub_i = 0;
            for (int row = 0; row < n; row++) {
                if (row == i) continue;
                int sub_j = 0;
                for (int col = 0; col < n; col++) {
                    if (col == j) continue;
                    sub.data[sub_i][sub_j++] = a.data[row][col];
                }
                sub_i++;
            }
            
            double cofactor = det_matrix(sub);
            int sign = ((i+j) % 2 == 0) ? 1 : -1;
            result.data[j][i] = sign * cofactor / det; 
        }
    }
    
    return result;
}

int rank_matrix(Matrix a)
{

    if (a.rows != a.cols) {
    printf("Error: This simple rank calculation only supports square matrices.\n");
    return 0;
    }
    double det = det_matrix(a);
    if (det != 0) {
    return a.rows;
    }
    return 0;
}


double trace_matrix(Matrix a)
{
    if (a.rows != a.cols) {
        fprintf(stderr, "Error: Matrix must be square to calculate trace.\n");
        return 0;
    }
    
    double trace = 0;
    for (int i = 0; i < a.rows; i++) {
        trace += a.data[i][i];
    }
    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}