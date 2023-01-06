#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits>

int const NICKNAME_MAX_LETTERS = 51;
int const SPACE_BETWEEN_NUMBERS = 6;
int const FILENAME_MAX_SIZE = 10;
int const FILE_LINE_MAX_SIZE = 70;

char** InitializeCharMatrix(char** matrix, int rows, int cols) {
	matrix = new char* [cols];
	for (int col = 0; col < cols; col++) {
		matrix[col] = new char[rows];
	}
	return matrix;
}

int** InitializeIntMatrix(int** matrix, int dimension) {
	matrix = new int* [dimension];
	for (int col = 0; col < dimension; col++) {
		matrix[col] = new int[dimension];
	}
	return matrix;
}

int LengthOfSymbolsInNumber(int number) {
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
			int length = LengthOfSymbolsInNumber(matrix[row][col]);
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

int CalculatingScore(int** matrix, int dimension) {
	int score = 0;
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			score += matrix[row][col];
		}
	}
	return score;
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
			if (matrix[row][col] == 0)
				return true;
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

void IsMatrixDimensionValid(int& dimension) {
	while (dimension < 4 || dimension > 10) {
		std::cout << "The dimension should be between 4 and 10!\n" << "Please enter new number: ";
		std::cin >> dimension;
	}
}

void DeletingDynamicMemory(int** matrix, int dimension) {
	for (int col = 0; col < dimension; col++) {
		delete matrix[col];
	}
	delete[] matrix;
}

void CreateFileName(char* fileName, int dimension) {
	int index = 0;
	if (dimension == 10) {
		fileName[index++] = '1';
		fileName[index++] = '0';
		fileName[index++] = 'x';
		fileName[index++] = '1';
		fileName[index++] = '0';
	}
	else {
		fileName[index++] = dimension + '0';
		fileName[index++] = 'x';
		fileName[index++] = dimension + '0';
	}
	char txt[5] = ".txt";
	for (int i = 0; i < 4; i++) {
		fileName[index++] = txt[i];
	}
	fileName[index] = '\0';
}

bool HasLeaderboardFivePeople(int dimension) {
	std::fstream leaderboard;
	char fileName[10];
	CreateFileName(fileName, dimension);
	leaderboard.open(fileName, std::ios::in);
	if (leaderboard.is_open() == false) {
		std::cout << "Failed to open the file.\n";
		return false;
	}
	int placeOfRanking = 0;
	char line[FILE_LINE_MAX_SIZE];
	while (leaderboard.getline(line, FILE_LINE_MAX_SIZE)) {
		placeOfRanking = line[0] - '0';
	}
	leaderboard.close();
	if (placeOfRanking == 5)
		return true;
	return false;
}

void CopyFileLine(char** oldLeaderboard, char* line, int rowIndex) {
	for (int index = 0; line[index] != '\0' && line[index] >= 0; index++) {
		oldLeaderboard[rowIndex][index] = line[index];
	}
}

char* NumberToChar(int number) {
	char score[10];
	int lengthOfNum = LengthOfSymbolsInNumber(number);
	for (int index = lengthOfNum; index >= 0; index--) {
		score[index] = number % 10 + '0';
		number /= 10;
	}
	return score;
}

void AddNewScoreToTheLeaderboard(char** leaderboard, int score, char* nickname, int position) {
	int index = 0;
	leaderboard[position][index++] = position + 1 + '0';
	leaderboard[position][index++] = ' ';
	for (int i = 0; nickname[i] != '\0'; i++) {
		leaderboard[position][index++] = nickname[i];
	}
	leaderboard[position][index++] = ' ';
	char* charScore = NumberToChar(score);
	for (int i = 0; charScore[i] != '0' && charScore[i] >= '0'; i++) {
		leaderboard[position][index++] = charScore[i];
	}
}

int LengthOfChar(char score[10]) {
	int length = 0;
	for (int i = 0; score[i] >= '0'; i++) {
		length++;
	}
	return length;
}

int Pow(int base, int power) {
	int result = 1;
	if (power == 0)
		return 1;
	for (int i = 0; i < power; i++) {
		result *= base;
	}
	return result;
}

int TransformCharToNumber(char score[10]) {
	int scoreToNum = 0;
	int lengthOfChar = LengthOfChar(score);
	for (int i = 0; score[i] >= '0'; i++) {
		scoreToNum += (score[i] - '0') * Pow(10, lengthOfChar-- - 1);
	}
	return scoreToNum;
}

int CountOfSpacesInNickname(char* nickname) {
	int spaces = 0;
	for (int i = 0; nickname[i] != '\0'; i++) {
		if (nickname[i] == ' ')
			spaces++;
	}
	return spaces;
}

int ReadHighScoreFromFile(char* line, char * nickname) {
	char highScore[10];
	int scoreIndex = 0;
	int nicknameSpaces = CountOfSpacesInNickname(nickname);
	int currCountOfSpaces = 0;
	int index = 2; // skips the ranking and the space after it
	for (index; line[index] != '\0' && line[index] >= 0; index++) {
		if (line[index] == ' ')
			currCountOfSpaces++;
		if (currCountOfSpaces == nicknameSpaces)
		{
			index++;
			break;
		}
	}
	for (index; line[index] != ' '; index++);
	index++;
	for (index; line[index] != '\0' && line[index] >= 0; index++) {
		highScore[scoreIndex++] = line[index];
	}
	return TransformCharToNumber(highScore);
}

char* EmptyChar(char* line) {
	for (int i = 0; line[i] != '\0' && line[i] > 0; i++)
		line[i] = '\0';
	return line;
}

void AddingLineToFile(std::fstream& leaderboard, char* lineToBeAdded) {
	for (int i = 0; lineToBeAdded[i] != '\0' && lineToBeAdded[i] >= 0; i++) {
		leaderboard << lineToBeAdded[i];
	}
	leaderboard << '\n';
}

void CheckingIfScoreIsHigherThanThoseInLeaderboard(int currScore, char* nickname, int dimension) {
	std::fstream leaderboard;
	char fileName[10];
	CreateFileName(fileName, dimension);
	if (HasLeaderboardFivePeople(dimension)) {
		int positionInRanking, highScore;
		char currNickname[NICKNAME_MAX_LETTERS];
		leaderboard.open(fileName, std::ifstream::in);
		if (leaderboard.is_open() == false) {
			std::cout << "Failed to open the file.\n";
			return;
		}
		char** oldLeaderboard{};
		oldLeaderboard = InitializeCharMatrix(oldLeaderboard, 5, FILE_LINE_MAX_SIZE);
		char line[FILE_LINE_MAX_SIZE];
		int rowIndex = 0, indexOfLineWithLowerScore = 5;
		while (leaderboard.getline(line, FILE_LINE_MAX_SIZE)) {
			CopyFileLine(oldLeaderboard, line, rowIndex);
			rowIndex++;
			if (currScore > ReadHighScoreFromFile(line, nickname) && indexOfLineWithLowerScore == 5) {
				indexOfLineWithLowerScore = line[0] - '0' - 1;
			}
		}
		leaderboard.close();
		if (indexOfLineWithLowerScore != 5) {
			for (int row = 4; row >= indexOfLineWithLowerScore; row--) {
				oldLeaderboard[row][0] = int(row + 2 + '0'); // changes the position of the ranking
				oldLeaderboard[row + 1] = EmptyChar(oldLeaderboard[row + 1]);
				CopyFileLine(oldLeaderboard, oldLeaderboard[row], row + 1);
			}
			oldLeaderboard[indexOfLineWithLowerScore] = EmptyChar(oldLeaderboard[indexOfLineWithLowerScore]);
			AddNewScoreToTheLeaderboard(oldLeaderboard, currScore, nickname, indexOfLineWithLowerScore);
		}
		leaderboard.open(fileName, std::ostream::out);
		if (leaderboard.is_open() == false) {
			std::cout << "Failed to open the file.\n";
			return;
		}
		for (int i = 0; i < 5; i++) {
			AddingLineToFile(leaderboard, oldLeaderboard[i]);
		}
		leaderboard.close();
	}
	else {

	}
}

bool IsNicknameValid(char* nickname) {
	for (int i = 0; i < NICKNAME_MAX_LETTERS - 1; i++) {
		if (nickname[i] == '\0')
		{
			return true;
		}
	}
	std::cout << "The nickname should be max 50 symbols!\n";
	return false;
	//while (isValid == false) {
	//	std::cout << "The nickname should be max 50 symbols!\n";
	//	std::cout << "Please enter a new one: " << std::endl;
	//	std::cin.ignore();
	//	IsNicknameValid(nickname);
	//}
}

void StartingGame(char* nickname, int matrixDimension) {
	std::cout << "Please enter your nickname: ";
	std::cin.ignore();
	std::cin.getline(nickname, NICKNAME_MAX_LETTERS);
	while (!IsNicknameValid(nickname)) {
		std::cin.getline(nickname, NICKNAME_MAX_LETTERS);// Fix the cin!
	}
	std::cout << "Enter a number for the dimension of the matrix: ";
	std::cin >> matrixDimension;
	IsMatrixDimensionValid(matrixDimension);
	system("cls");
	int** matrix{};
	srand((unsigned)time(NULL));
	matrix = InitializeIntMatrix(matrix, matrixDimension);
	FillMatrixWithZeros(matrix, matrixDimension);
	int score = 0;
	while (true) {
		if (AreThereZerosInMatrix(matrix, matrixDimension))
			SetARandomNumberInMatrix(matrix, matrixDimension);
		PrintMatrix(matrix, matrixDimension);
		score = CalculatingScore(matrix, matrixDimension);
		std::cout << "Score: " << score << '\n';
		if (!AreTherePossibleMoves(matrix, matrixDimension)) {
			std::cout << "There are no more possible moves!\n";
			std::cout << "Your result is: " << score;
			break;
		}
		std::cout << "Enter direction: ";
		char direction;
		std::cin >> direction;
		MovingNumbers(matrix, matrixDimension, direction);
	}
	CheckingIfScoreIsHigherThanThoseInLeaderboard(score, nickname, matrixDimension);
	DeletingDynamicMemory(matrix, matrixDimension);
}

void Leaderboard() {
	std::fstream leaderboardFile;
	std::cout << "Choose dimension you want to see the leaderboard for: ";
	int dimension;
	std::cin >> dimension;
	std::cout << '\n';
	IsMatrixDimensionValid(dimension);
	char fileName[10];
	CreateFileName(fileName, dimension);
	leaderboardFile.open(fileName, std::ifstream::in);
	if (leaderboardFile.is_open() == false) {
		std::cout << "Failed to open the file.\n";
		return;
	}
	std::cout << "The " << dimension << "x" << dimension << " leaderboard: \n";
	int positioninranking, score;
	char nickname[NICKNAME_MAX_LETTERS];
	while (leaderboardFile >> positioninranking >> nickname >> score) {
		std::cout << positioninranking << " " << nickname << " " << score << '\n';
	}
	leaderboardFile.close();
	std::cout << '\n';
}

int main()
{
	int chosenOption;
	do {
		std::cout << "      MENU     " << '\n';
		std::cout << "1. Start game\n";
		std::cout << "2. Leaderboard\n";
		std::cout << "3. Quit\n";
		std::cout << "\nPlease enter a number to choose one of the options: ";
		char nickname[NICKNAME_MAX_LETTERS];
		std::cin >> chosenOption;
		chosenOption = IsChosenOptionValid(chosenOption);
		int matrixDimension = 0;
		if (chosenOption == 1) {
			StartingGame(nickname, matrixDimension);
		}
		else if (chosenOption == 2) {
			Leaderboard();
		}
	} while (chosenOption != 3);
}
