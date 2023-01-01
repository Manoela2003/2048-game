#include <stdlib.h>
#include <iostream>
//#include <iomanip>

int const NICKNAME_MAX_LETTERS = 50;
int const SPACE_BETWEEN_NUMBERS = 6;

int** InitializeMatrix(int** matrix, int dimension) {
	matrix = new int* [dimension];
	for (int col = 0; col < dimension; col++) {
		matrix[col] = new int[dimension];
	}
	return matrix;
}

int LengthOfNumber(int number) {
	int length = 0;
	while (number > 9) {
		number /= 10;
		length++;
	}
	return length;
}

void PrintMatrix(int** matrix, int dimension) {
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			std::cout << matrix[row][col];
			int length = LengthOfNumber(matrix[row][col]);
			for (int space = 0; space < SPACE_BETWEEN_NUMBERS - length; space++) {
				std::cout << " ";
			}
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
	int row, col, randomNumber;
	do {
		randomNumber = rand() % (dimension * dimension);
		row = randomNumber / dimension;
		col = randomNumber % 4;
	} while (matrix[row][col] != 0);
	matrix[row][col] = DetermineTheRandomNumInMatrix();
}

void CalculatingScore(int** matrix, int dimension) {
	int score = 0;
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			score += matrix[row][col];
		}
	}
	std::cout << score << '\n';
}

bool CheckForColumnWithZeros(int** matrix, int dimension, int col) {
	for (int row = 0; row < dimension; row++) {
		if (matrix[row][col] != 0)
			return false;
	}
	return true;
}

bool CheckForRowWithZeros(int** matrix, int dimension, int row) {
	for (int col = 0; col < dimension; col++)
		if (matrix[row][col] != 0)
			return false;
	return true;
}

void MovingNumbersUp(int** matrix, int dimension, int col) {
	for (int counter = 0; counter < dimension - 1; counter++) {
		for (int row = counter + 1; row > 0; row--) {
			if (matrix[row - 1][col] == matrix[row][col] || matrix[row - 1][col] == 0) {
				matrix[row - 1][col] += matrix[row][col];
				matrix[row][col] = 0;
			}
			else {
				break;
			}
		}
	}
}

void MovingNumbersDown(int** matrix, int dimension, int col) {
	for (int counter = dimension - 1; counter > 0; counter--) {
		for (int row = counter - 1; row < dimension - 1; row++) {
			if (matrix[row + 1][col] == matrix[row][col] || matrix[row + 1][col] == 0) {
				matrix[row + 1][col] += matrix[row][col];
				matrix[row][col] = 0;
			}
			else {
				break;
			}
		}
	}
}

void MovingNumbersLeft(int** matrix, int dimension, int row) {
	for (int counter = 0; counter < dimension - 1; counter++) {
		for (int col = counter + 1; col > 0; col--) {
			if (matrix[row][col - 1] == matrix[row][col] || matrix[row][col - 1] == 0) {
				matrix[row][col - 1] += matrix[row][col];
				matrix[row][col] = 0;
			}
			else
				break;
		}
	}
}

void MovingNumbersRight(int** matrix, int dimension, int row) {
	for (int counter = dimension - 1; counter > 0; counter--) {
		for (int col = counter - 1; col < dimension - 1; col++) {
			if (matrix[row][col + 1] == matrix[row][col] || matrix[row][col + 1] == 0) {
				matrix[row][col + 1] += matrix[row][col];
				matrix[row][col] = 0;
			}
			else {
				break;
			}
		}
	}
}

void MovingNumbers(int** matrix, int dimension, char direction) {
	if (direction == 'w') {
		for (int col = 0; col < dimension; col++) {
			if (CheckForColumnWithZeros(matrix, dimension, col))
				continue;
			MovingNumbersUp(matrix, dimension, col);
		}
	}
	else if (direction == 's') {
		for (int col = 0; col < dimension; col++) {
			if (CheckForColumnWithZeros(matrix, dimension, col))
				continue;
			MovingNumbersDown(matrix, dimension, col);
		}
	}
	else if (direction == 'a') {
		for (int row = 0; row < dimension; row++) {
			if (CheckForRowWithZeros(matrix, dimension, row))
				continue;
			MovingNumbersLeft(matrix, dimension, row);
		}
	}
	else if (direction == 'd') {
		for (int row = 0; row < dimension; row++) {
			if (CheckForRowWithZeros(matrix, dimension, row))
				continue;
			MovingNumbersRight(matrix, dimension, row);
		}
	}
	else {
		std::cout << "Please enter a valid direction!\n";
		std::cout << "Type one of the following - 'w' 'a' 's' 'd': ";
		std::cin >> direction;
		MovingNumbers(matrix, dimension, direction);
	}
}

bool AreThereZerosInMatrix(int** matrix, int dimension) {
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			if (matrix[row][col] == 0)
				return true;
		}
	}
	return false;
}

bool AreTherePossibleMoves(int** matrix, int dimension) {
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			if (col == dimension - 1 && row != dimension - 1) {
				if (matrix[row][col] == matrix[row + 1][col])
					return true;
				continue;
			}
			else if (row == dimension - 1 && col != dimension - 1) {
				if (matrix[row][col] == matrix[row][col + 1])
					return true;
				continue;
			}
			if (row == dimension - 1 && col == dimension - 1)
				break;
			if (matrix[row][col] == matrix[row][col + 1] || matrix[row][col] == matrix[row + 1][col])
				return true;
		}
	}
	return false;
}

int IsChosenOptionValid(int chosenOption) {
	while (!(chosenOption == 1 || chosenOption == 2 || chosenOption == 3)) {
		std::cout << "That is not a valid option! Please choose again: ";
		std::cin >> chosenOption;
	}
	return chosenOption;
}

int main()
{
	int chosenOption;
	do {
		std::cout << "      MENU\n";
		std::cout << "1. Start game\n" << "2. Leaderboard\n" << "3. Quit\n";
		std::cout << "\nPlease enter a number to choose one of the options: ";
		char nickname[NICKNAME_MAX_LETTERS];
		std::cin >> chosenOption;
		chosenOption = IsChosenOptionValid(chosenOption);
		int matrixDimension;
		if (chosenOption == 1) {
			std::cout << "Please enter your nickname: ";
			std::cin.ignore();
			std::cin.getline(nickname, NICKNAME_MAX_LETTERS);
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
			while (true) {
				if (AreThereZerosInMatrix(matrix, matrixDimension))
					SetARandomNumberInMatrix(matrix, matrixDimension);
				else if (!AreTherePossibleMoves(matrix, matrixDimension)) {
					std::cout << "There are no more possible moves!\n";
					std::cout << "Your result is: ";
					CalculatingScore(matrix, matrixDimension);
				}
				PrintMatrix(matrix, matrixDimension);
				std::cout << "Score: ";
				CalculatingScore(matrix, matrixDimension);
				std::cout << "Enter direction: ";
				char direction;
				std::cin >> direction;
				MovingNumbers(matrix, matrixDimension, direction);
			}
		}
		else if (chosenOption == 2) {

		}
	} while (chosenOption != 3);
}
