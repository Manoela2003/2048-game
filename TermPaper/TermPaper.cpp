#include <stdlib.h>
#include <iostream>
#include <iomanip>

int const NICKNAME_MAX_LETTERS = 50;

int** InitializeMatrix(int** matrix, int dimension) {
	matrix = new int* [dimension];
	for (int col = 0; col < dimension; col++) {
		matrix[col] = new int[dimension];
	}
	return matrix;
}

void PrintMatrix(int** matrix, int dimension) {
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			std::cout << matrix[row][col] << std::setw(7);
		}
		std::cout << "\n\n";
	}
}
void FillMatrixWithZeros(int** matrix, int dimension) {
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			matrix[i][j] = 0;
		}
	}
}

int DetermineTheRandomNumInMatrix() {
	int randomNum = rand() % 2;
	if (randomNum == 0)
		return 2;
	else
		return 4;
}

void SetARandomNumberInMatrix(int** matrix, int dimension) {
	int rowAndColOfNum = rand() % (dimension * dimension) + 1;
	rowAndColOfNum /= dimension;
	matrix[rowAndColOfNum][rowAndColOfNum] = DetermineTheRandomNumInMatrix();
}

void CalculatingScore(int** matrix, int dimension) {
	int score = 0;
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			score += matrix[row][col];
		}
	}
	std::cout << "Score: " << score;
}

int main()
{
	std::cout << "      MENU\n";
	std::cout << "1. Start game\n" << "2. Leaderboard\n" << "3. Quit\n";
	std::cout << "\nPlease enter a number to choose one of the options: ";
	char nickname[50];
	int chosenOption;
	std::cin >> chosenOption;
	int matrixDimension;
	if (chosenOption == 1) {
		std::cout << "Please enter your nickname: ";
		std::cin.ignore();
		std::cin.getline(nickname, 50);
		std::cout << "Enter a number for the dimension of the matrix: ";
		std::cin >> matrixDimension;
		while (matrixDimension < 4 || matrixDimension > 10) {
			std::cout << "The dimension should be between 4 and 10!\n" << "Please enter new number: ";
			std::cin >> matrixDimension;
		}
		system("cls");
		int** matrix{};
		srand((unsigned)time(NULL));
		matrix = InitializeMatrix(matrix, matrixDimension);
		FillMatrixWithZeros(matrix, matrixDimension);
		SetARandomNumberInMatrix(matrix, matrixDimension);
		PrintMatrix(matrix, matrixDimension);
		CalculatingScore(matrix, matrixDimension);
	}
}
