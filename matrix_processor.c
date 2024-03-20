#include <stdio.h>
#include <stdlib.h>

void showOptions();
double** inputMatrix();
void printMatrix(double** matrix, int rows, int cols);
void addMatrices();
void multiplyConst();
void multiplyMatrices();
void transposeMatrix();
double** transposeMainDiagonal(double** matrix, int rows, int cols);
double** transposeSideDiagonal(double** matrix, int rows, int cols);
double** transposeVerticalLine(double** matrix, int rows, int cols);
double** transposeHorizontalLine(double** matrix, int rows, int cols);
void calcDeterminant();
double determinant(double** matrix, int size);
double** copyMatrix(double** matrix, int rows, int cols);
double** removeColumn(double** matrix, int rows, int cols, int columnIndex);
void inverseMatrix();

int main() {
    while (1) {
        showOptions();
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                exit(0);
                break;
            case 1:
                addMatrices();
                break;
            case 2:
                multiplyConst();
                break;
            case 3:
                multiplyMatrices();
                break;
            case 4:
                transposeMatrix();
                break;
            case 5:
                calcDeterminant();
                break;
            case 6:
                inverseMatrix();
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
    return 0;
}

void showOptions() {
    printf("\n");
    printf("1. Add matrices\n");
    printf("2. Multiply matrix by a constant\n");
    printf("3. Multiply matrices\n");
    printf("4. Transpose matrix\n");
    printf("5. Calculate a determinant\n");
    printf("6. Inverse matrix\n");
    printf("0. Exit\n");
}

double** inputMatrix() {
    printf("Enter number of rows and columns: ");
    int rows, cols;
    scanf("%d %d", &rows, &cols);
    double** matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
        printf("Enter elements for row %d: ", i + 1);
        for (int j = 0; j < cols; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }
    return matrix;
}

void printMatrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.2lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

void addMatrices() {
    printf("Enter the first matrix:\n");
    double** matrix1 = inputMatrix();
    printf("Enter the second matrix:\n");
    double** matrix2 = inputMatrix();

    int rows1 = sizeof(matrix1) / sizeof(matrix1[0]);
    int cols1 = sizeof(matrix1[0]) / sizeof(matrix1[0][0]);
    int rows2 = sizeof(matrix2) / sizeof(matrix2[0]);
    int cols2 = sizeof(matrix2[0]) / sizeof(matrix2[0][0]);

    if (rows1 != rows2 || cols1 != cols2) {
        printf("ERROR: Matrices must have the same dimensions for addition.\n");
        return;
    }

    double** result = (double**)malloc(rows1 * sizeof(double*));
    for (int i = 0; i < rows1; i++) {
        result[i] = (double*)malloc(cols1 * sizeof(double));
        for (int j = 0; j < cols1; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    printf("The result is:\n");
    printMatrix(result, rows1, cols1);
}

void multiplyConst() {
    double** matrix = inputMatrix();
    int rows = sizeof(matrix) / sizeof(matrix[0]);
    int cols = sizeof(matrix[0]) / sizeof(matrix[0][0]);

    printf("Enter the constant: ");
    double constant;
    scanf("%lf", &constant);

    printf("The result is:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.2lf ", matrix[i][j] * constant);
        }
        printf("\n");
    }

}

void multiplyMatrices() {
    printf("Enter the first matrix:\n");
    double** matrix1 = inputMatrix();
    printf("Enter the second matrix:\n");
    double** matrix2 = inputMatrix();

    int rows1 = sizeof(matrix1) / sizeof(matrix1[0]);
    int cols1 = sizeof(matrix1[0]) / sizeof(matrix1[0][0]);
    int rows2 = sizeof(matrix2) / sizeof(matrix2[0]);
    int cols2 = sizeof(matrix2[0]) / sizeof(matrix2[0][0]);

    if (cols1 != rows2) {
        printf("ERROR: Matrix multiplication not possible due to incompatible dimensions.\n");
        return;
    }

    double** result = (double**)malloc(rows1 * sizeof(double*));
    for (int i = 0; i < rows1; i++) {
        result[i] = (double*)calloc(cols2, sizeof(double));
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < rows2; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    printf("The result is:\n");
    printMatrix(result, rows1, cols2);
}

void transposeMatrix() {
    printf("Enter the matrix:\n");
    double** matrix = inputMatrix();
    int rows = sizeof(matrix) / sizeof(matrix[0]);
    int cols = sizeof(matrix[0]) / sizeof(matrix[0][0]);

    printf("1. Main diagonal\n");
    printf("2. Side diagonal\n");
    printf("3. Vertical line\n");
    printf("4. Horizontal line\n");
    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);

    double** result;
    switch (choice) {
        case 1:
            result = transposeMainDiagonal(matrix, rows, cols);
            break;
        case 2:
            result = transposeSideDiagonal(matrix, rows, cols);
            break;
        case 3:
            result = transposeVerticalLine(matrix, rows, cols);
            break;
        case 4:
            result = transposeHorizontalLine(matrix, rows, cols);
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }

    printf("The result is:\n");
    printMatrix(result, rows, cols);
}

double** transposeMainDiagonal(double** matrix, int rows, int cols) {
    double** result = (double**)malloc(cols * sizeof(double*));
    for (int i = 0; i < cols; i++) {
        result[i] = (double*)malloc(rows * sizeof(double));
        for (int j = 0; j < rows; j++) {
            result[i][j] = matrix[j][i];
        }
    }
    return result;
}

double** transposeSideDiagonal(double** matrix, int rows, int cols) {
    double** result = (double**)malloc(cols * sizeof(double*));
    for (int i = 0; i < cols; i++) {
        result[i] = (double*)malloc(rows * sizeof(double));
        for (int j = 0; j < rows; j++) {
            result[i][j] = matrix[rows - 1 - j][cols - 1 - i];
        }
    }
    return result;
}

double** transposeVerticalLine(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        int j = 0, k = cols - 1;
        while (j < k) {
            double temp = matrix[i][j];
            matrix[i][j] = matrix[i][k];
            matrix[i][k] = temp;
            j++;
            k--;
        }
    }
    return matrix;
}

double** transposeHorizontalLine(double** matrix, int rows, int cols) {
    int i = 0, j = rows - 1;
    while (i < j) {
        double* temp = matrix[i];
        matrix[i] = matrix[j];
        matrix[j] = temp;
        i++;
        j--;
    }
    return matrix;
}

void calcDeterminant() {
    double** matrix = inputMatrix();
    int size = sizeof(matrix) / sizeof(matrix[0]);
    if (size != sizeof(matrix[0]) / sizeof(matrix[0][0])) {
        printf("Error! Use square matrices only!\n");
        return;
    }
    double determinant_result = determinant(matrix, size);
    printf("The result is:\n%.2lf\n", determinant_result);
}

double determinant(double** matrix, int size) {
    if (size == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    }
    double total = 0.0;
    for (int fc = 0; fc < size; fc++) {
        double** ac = copyMatrix(matrix, size - 1, size - 1);
        ac = removeColumn(ac, size - 1, size - 1, fc);
        double sign = (fc % 2 == 1) ? -1.0 : 1.0;
        double subDet = determinant(ac, size - 1);
        total += sign * matrix[0][fc] * subDet;
        free(ac);
    }
    return total;
}

double** copyMatrix(double** matrix, int rows, int cols) {
    double** copy = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        copy[i] = (double*)malloc(cols * sizeof(double));
        for (int j = 0; j < cols; j++) {
            copy[i][j] = matrix[i][j];
        }
    }
    return copy;
}

double** removeColumn(double** matrix, int rows, int cols, int columnIndex) {
    double** result = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        result[i] = (double*)malloc((cols - 1) * sizeof(double));
        int destCol = 0;
        for (int j = 0; j < cols; j++) {
            if (j != columnIndex) {
                result[i][destCol++] = matrix[i][j];
            }
        }
    }
    return result;
}

void inverseMatrix() {
    printf("Inverse matrix functionality is not implemented.\n");
}
