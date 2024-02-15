import java.util.Scanner;

public class MatrixProcessor {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            showOptions();
            String choice = scanner.nextLine();
            switch (choice) {
                case "0":
                    System.exit(0);
                    break;
                case "1":
                    addMatrices(scanner);
                    break;
                case "2":
                    multiplyConst(scanner);
                    break;
                case "3":
                    multiplyMatrices(scanner);
                    break;
                case "4":
                    transposeMatrix(scanner);
                    break;
                case "5":
                    calcDeterminant(scanner);
                    break;
                case "6":
                    inverseMatrix();
                    break;
                default:
                    System.out.println("Invalid choice.");
                    break;
            }
        }
    }

    public static void showOptions() {
        System.out.println();
        System.out.println("1. Add matrices");
        System.out.println("2. Multiply matrix by a constant");
        System.out.println("3. Multiply matrices");
        System.out.println("4. Transpose matrix");
        System.out.println("5. Calculate a determinant");
        System.out.println("6. Inverse matrix");
        System.out.println("0. Exit");
    }

    public static double[][] inputMatrix(Scanner scanner) {
        System.out.print("Enter number of rows and columns: ");
        int rows = scanner.nextInt();
        int cols = scanner.nextInt();
        double[][] matrix = new double[rows][cols];
        System.out.println("Enter the matrix elements:");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = scanner.nextDouble();
            }
        }
        return matrix;
    }

    public static void printMatrix(double[][] matrix) {
        for (double[] row : matrix) {
            for (double val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
    }

    public static void addMatrices(Scanner scanner) {
        System.out.println("Enter the first matrix:");
        double[][] matrix1 = inputMatrix(scanner);
        System.out.println("Enter the second matrix:");
        double[][] matrix2 = inputMatrix(scanner);

        if (matrix1.length != matrix2.length || matrix1[0].length != matrix2[0].length) {
            System.out.println("ERROR: Matrices must have the same dimensions for addition.");
            return;
        }

        double[][] result = new double[matrix1.length][matrix1[0].length];
        for (int i = 0; i < matrix1.length; i++) {
            for (int j = 0; j < matrix1[0].length; j++) {
                result[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }

        System.out.println("The result is:");
        printMatrix(result);
    }

    public static void multiplyConst(Scanner scanner) {
        double[][] matrix = inputMatrix(scanner);
        System.out.print("Enter the constant: ");
        double constant = scanner.nextDouble();

        System.out.println("The result is:");
        for (double[] row : matrix) {
            for (double val : row) {
                System.out.print(val * constant + " ");
            }
            System.out.println();
        }
    }

    public static void multiplyMatrices(Scanner scanner) {
        System.out.println("Enter the first matrix:");
        double[][] matrix1 = inputMatrix(scanner);
        System.out.println("Enter the second matrix:");
        double[][] matrix2 = inputMatrix(scanner);

        if (matrix1[0].length != matrix2.length) {
            System.out.println("ERROR: Matrix multiplication not possible due to incompatible dimensions.");
            return;
        }

        double[][] result = new double[matrix1.length][matrix2[0].length];

        for (int i = 0; i < matrix1.length; i++) {
            for (int j = 0; j < matrix2[0].length; j++) {
                for (int k = 0; k < matrix2.length; k++) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }

        System.out.println("The result is:");
        printMatrix(result);
    }

    public static void transposeMatrix(Scanner scanner) {
        double[][] matrix = inputMatrix(scanner);

        System.out.println("1. Main diagonal");
        System.out.println("2. Side diagonal");
        System.out.println("3. Vertical line");
        System.out.println("4. Horizontal line");
        System.out.print("Your choice: ");
        int choice = scanner.nextInt();

        double[][] result;
        switch (choice) {
            case 1:
                result = transposeMainDiagonal(matrix);
                break;
            case 2:
                result = transposeSideDiagonal(matrix);
                break;
            case 3:
                result = transposeVerticalLine(matrix);
                break;
            case 4:
                result = transposeHorizontalLine(matrix);
                break;
            default:
                System.out.println("Invalid choice.");
                return;
        }

        System.out.println("The result is:");
        printMatrix(result);
    }

    public static double[][] transposeMainDiagonal(double[][] matrix) {
        int rows = matrix.length;
        int cols = matrix[0].length;
        double[][] result = new double[cols][rows];
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                result[i][j] = matrix[j][i];
            }
        }
        return result;
    }

    public static double[][] transposeSideDiagonal(double[][] matrix) {
        int rows = matrix.length;
        int cols = matrix[0].length;
        double[][] result = new double[cols][rows];
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                result[i][j] = matrix[rows - 1 - j][cols - 1 - i];
            }
        }
        return result;
    }

    public static double[][] transposeVerticalLine(double[][] matrix) {
        for (double[] row : matrix) {
            int i = 0, j = row.length - 1;
            while (i < j) {
                double temp = row[i];
                row[i] = row[j];
                row[j] = temp;
                i++;
                j--;
            }
        }
        return matrix;
    }

    public static double[][] transposeHorizontalLine(double[][] matrix) {
        int rows = matrix.length;
        int i = 0, j = rows - 1;
        while (i < j) {
            double[] temp = matrix[i];
            matrix[i] = matrix[j];
            matrix[j] = temp;
            i++;
            j--;
        }
        return matrix;
    }

    public static void calcDeterminant(Scanner scanner) {
        double[][] matrix = inputMatrix(scanner);
        if (matrix.length != matrix[0].length) {
            System.out.println("Error! Use square matrices only!");
            return;
        }
        double determinant = determinant(matrix);
        System.out.println("The result is:");
        System.out.println(determinant);
    }

    public static double determinant(double[][] a) {
        int n = a.length;
        if (n == 2 && a[0].length == 2) {
            return a[0][0] * a[1][1] - a[1][0] * a[0][1];
        }
        double total = 0.0;
        for (int fc = 0; fc < n; fc++) {
            double[][] ac = copyMatrix(a);
            ac = removeColumn(ac, fc);
            double sign = (fc % 2 == 1) ? -1.0 : 1.0;
            double subDet = determinant(ac);
            total += sign * a[0][fc] * subDet;
        }
        return total;
    }

    public static double[][] copyMatrix(double[][] m) {
        int rows = m.length;
        int cols = m[0].length;
        double[][] mc = new double[rows][cols];
        for (int i = 0; i < rows; i++) {
            System.arraycopy(m[i], 0, mc[i], 0, cols);
        }
        return mc;
    }

    public static double[][] removeColumn(double[][] matrix, int columnIndex) {
        int rows = matrix.length;
        int cols = matrix[0].length - 1;
        double[][] result = new double[rows][cols];
        for (int i = 0; i < rows; i++) {
            System.arraycopy(matrix[i], 0, result[i], 0, columnIndex);
            System.arraycopy(matrix[i], columnIndex + 1, result[i], columnIndex, cols - columnIndex);
        }
        return result;
    }

    public static void inverseMatrix() {
        // Not implemented
        System.out.println("Inverse matrix functionality is not implemented.");
    }
}
