package main

import (
	"fmt"
	"os"
	"strconv"
)

func zerosMatrix(rows, cols int) [][]float64 {
	m := make([][]float64, rows)
	for i := range m {
		m[i] = make([]float64, cols)
	}
	return m
}

func copyMatrix(m [][]float64) [][]float64 {
	rows, cols := len(m), len(m[0])
	mc := zerosMatrix(rows, cols)
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			mc[i][j] = m[i][j]
		}
	}
	return mc
}

func determinant(a [][]float64) float64 {
	n := len(a)
	if n == 2 && len(a[0]) == 2 {
		val := a[0][0]*a[1][1] - a[1][0]*a[0][1]
		return val
	}
	total := 0.0
	for fc := 0; fc < n; fc++ {
		ac := copyMatrix(a)
		ac = ac[1:]
		height := len(ac)
		for i := 0; i < height; i++ {
			ac[i] = append(ac[i][:fc], ac[i][fc+1:]...)
		}
		sign := 1.0
		if fc%2 == 1 {
			sign = -1.0
		}
		subDet := determinant(ac)
		total += sign * a[0][fc] * subDet
	}
	return total
}

func showOptions() {
	fmt.Println()
	fmt.Println("1. Add matrices")
	fmt.Println("2. Multiply matrix by a constant")
	fmt.Println("3. Multiply matrices")
	fmt.Println("4. Transpose matrix")
	fmt.Println("5. Calculate a determinant")
	fmt.Println("6. Inverse matrix")
	fmt.Println("0. Exit")
}

func addMatrices() {
	var raw1, col1, raw2, col2 string
	fmt.Print("Enter size of first matrix:")
	fmt.Scan(&raw1, &col1)
	fmt.Println("Enter first matrix:")
	matrix1 := inputMatrix(raw1, col1)
	fmt.Print("Enter size of second matrix:")
	fmt.Scan(&raw2, &col2)
	fmt.Println("Enter second matrix:")
	matrix2 := inputMatrix(raw2, col2)

	if raw1 != raw2 || col1 != col2 {
		fmt.Println("ERROR")
		return
	}

	result := make([][]float64, len(matrix1))
	for i := range matrix1 {
		result[i] = make([]float64, len(matrix1[i]))
		for j := range matrix1[i] {
			result[i][j] = matrix1[i][j] + matrix2[i][j]
		}
	}

	fmt.Println("The result is:")
	printMatrix(result)
}

func inputMatrix(raw, col string) [][]float64 {
	rows, _ := strconv.Atoi(raw)
	cols, _ := strconv.Atoi(col)
	matrix := make([][]float64, rows)
	for i := range matrix {
		matrix[i] = make([]float64, cols)
		for j := range matrix[i] {
			fmt.Scan(&matrix[i][j])
		}
	}
	return matrix
}

func printMatrix(matrix [][]float64) {
	for _, row := range matrix {
		for _, val := range row {
			fmt.Printf("%.2f ", val)
		}
		fmt.Println()
	}
}

func multiplyConst() {
	var raw, col, constantStr string
	fmt.Print("Enter size of matrix:")
	fmt.Scan(&raw, &col)
	fmt.Println("Enter matrix:")
	matrix := inputMatrix(raw, col)
	fmt.Print("Enter constant:")
	fmt.Scan(&constantStr)

	constant, _ := strconv.ParseFloat(constantStr, 64)

	fmt.Println("The result is:")
	for _, row := range matrix {
		for _, val := range row {
			fmt.Printf("%.2f ", val*constant)
		}
		fmt.Println()
	}
}

func multiplyMatrices() {
	var raw1, col1, raw2, col2 string
	fmt.Print("Enter size of first matrix:")
	fmt.Scan(&raw1, &col1)
	fmt.Println("Enter first matrix:")
	matrix1 := inputMatrix(raw1, col1)
	fmt.Print("Enter size of second matrix:")
	fmt.Scan(&raw2, &col2)
	fmt.Println("Enter second matrix:")
	matrix2 := inputMatrix(raw2, col2)

	if col1 != raw2 {
		fmt.Println("ERROR")
		return
	}

	result := make([][]float64, len(matrix1))
	for i := range result {
		result[i] = make([]float64, len(matrix2[0]))
	}

	for i := range matrix1 {
		for j := range matrix2[0] {
			for k := range matrix2 {
				result[i][j] += matrix1[i][k] * matrix2[k][j]
			}
		}
	}

	fmt.Println("The result is:")
	printMatrix(result)
}

func transposeMatrix(matrix [][]float64) {
	var choice string
	fmt.Println("1. Main diagonal")
	fmt.Println("2. Side diagonal")
	fmt.Println("3. Vertical line")
	fmt.Println("4. Horizontal line")
	fmt.Print("Your choice:")
	fmt.Scan(&choice)

	switch choice {
	case "1":
		transposeMainDiagonal(matrix)
	case "2":
		transposeSideDiagonal(matrix)
	case "3":
		transposeVerticalLine(matrix)
	case "4":
		transposeHorizontalLine(matrix)
	default:
		fmt.Println("Invalid choice.")
	}
}

func transposeMainDiagonal(matrix [][]float64) {
	rows, cols := len(matrix), len(matrix[0])
	result := make([][]float64, cols)
	for i := range result {
		result[i] = make([]float64, rows)
		for j := range result[i] {
			result[i][j] = matrix[j][i]
		}
	}
	fmt.Println("The result is:")
	printMatrix(result)
}

func transposeSideDiagonal(matrix [][]float64) {
	rows, cols := len(matrix), len(matrix[0])
	result := make([][]float64, cols)
	for i := range result {
		result[i] = make([]float64, rows)
		for j := range result[i] {
			result[i][j] = matrix[rows-1-j][cols-1-i]
		}
	}
	fmt.Println("The result is:")
	printMatrix(result)
}

func transposeVerticalLine(matrix [][]float64) {
	for _, row := range matrix {
		for i, j := 0, len(row)-1; i < j; i, j = i+1, j-1 {
			row[i], row[j] = row[j], row[i]
		}
	}
	fmt.Println("The result is:")
	printMatrix(matrix)
}

func transposeHorizontalLine(matrix [][]float64) {
	rows := len(matrix)
	for i, j := 0, rows-1; i < j; i, j = i+1, j-1 {
		matrix[i], matrix[j] = matrix[j], matrix[i]
	}
	fmt.Println("The result is:")
	printMatrix(matrix)
}

func calcDeterminant() {
	var raw, col string
	fmt.Print("Enter size of matrix:")
	fmt.Scan(&raw, &col)
	fmt.Println("Enter matrix:")
	matrix := inputMatrix(raw, col)

	if raw != col {
		fmt.Println("Error! Use square matrices only!")
		return
	}

	fmt.Println("The result is:")
	fmt.Println(determinant(matrix))
}

func inverseMatrix() {
	// I spent an entire day on the function, and still cannot find a proper way to invert the matrix in Go :c
}

func main() {
	for {
		showOptions()
		var choice string
		fmt.Print("Your choice:")
		fmt.Scan(&choice)
		switch choice {
		case "0":
			os.Exit(0)
		case "1":
			addMatrices()
		case "2":
			multiplyConst()
		case "3":
			multiplyMatrices()
		case "4":
			var raw, col string
			fmt.Print("Enter size of matrix:")
			fmt.Scan(&raw, &col)
			fmt.Println("Enter matrix:")
			matrix := inputMatrix(raw, col)
			transposeMatrix(matrix)
		case "5":
			calcDeterminant()
		case "6":
			inverseMatrix()
		default:
			fmt.Println("Invalid choice.")
		}
	}
}
