/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Manoela Barakova
* @idnumber 5MI0600271 @compiler VC
*
* Executing the 2048 game
*
*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits>

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

void PrintMatrix(int** matrix, int dimension, int const SPACE_BETWEEN_NUMBERS) {
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

int GenerateRandomNumber() {
	int randomNum = rand() % 2;
	if (randomNum == 0)
		return 2;
	else
		return 4;
}

void PlaceRandomNumberInMatrix(int** matrix, int dimension) {
	int row, col, randomNumber;
	do {
		randomNumber = rand() % (dimension * dimension);
		row = randomNumber / dimension;
		col = randomNumber % 4;
	} while (matrix[row][col] != 0);
	matrix[row][col] = GenerateRandomNumber();
}

int CalculateScore(int** matrix, int dimension) {
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
	for (int col = 0; col < dimension; col++) {
		if (matrix[row][col] != 0)
			return false;
	}
	return true;
}

void MoveNumbersUp(int** matrix, int dimension, int col) {
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

void MoveNumbersDown(int** matrix, int dimension, int col) {
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

void MoveNumbersLeft(int** matrix, int dimension, int row) {
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

void MoveNumbersRight(int** matrix, int dimension, int row) {
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
	if (direction == 'w' || direction == 's') {
		for (int col = 0; col < dimension; col++) {
			if (CheckForColumnWithZeros(matrix, dimension, col))
				continue;
			if (direction == 'w')
				MoveNumbersUp(matrix, dimension, col);
			else
				MoveNumbersDown(matrix, dimension, col);
		}
	}
	else {
		for (int row = 0; row < dimension; row++) {
			if (CheckForRowWithZeros(matrix, dimension, row))
				continue;
			if (direction == 'a')
				MoveNumbersLeft(matrix, dimension, row);
			else
				MoveNumbersRight(matrix, dimension, row);
		}
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

void IsChosenOptionValid(char* chosenOption) {
	while (!(chosenOption[0] >= '1' && chosenOption[0] <= '3') || chosenOption[1] != '\0') {
		std::cout << "That is not a valid option! Please choose again: ";
		std::cin >> chosenOption;
	}
}

void IsMatrixDimensionValid(char* dimension) {
	while (!((dimension[0] >= '4' && dimension[0] <= '9' && dimension[1] == '\0') || (dimension[0] == '1' && dimension[1] == '0'))) {
		std::cout << "The dimension should be between 4 and 10!\n";
		std::cout << "Please enter new dimension: ";
		std::cin >> dimension;
	}
}

void DeleteDynamicMemory(int** matrix, int dimension) {
	for (int col = 0; col < dimension; col++) {
		delete matrix[col];
	}
	delete[] matrix;
}

void CreateFileName(char* fileName, char* dimension) {
	int index = 0;
	fileName[index++] = dimension[0];
	if (dimension[1] == '0')
		fileName[index++] = '0';
	fileName[index++] = 'x';
	fileName[index++] = dimension[0];
	if (dimension[1] == '0')
		fileName[index++] = '0';
	char txt[5] = ".txt";
	for (int i = 0; i < 4; i++) {
		fileName[index++] = txt[i];
	}
	fileName[index] = '\0';
}

void CopyFileLine(char** oldLeaderboard, char* line, int rowIndex) {
	for (int index = 0; line[index] != '\0' && line[index] >= 0; index++) {
		oldLeaderboard[rowIndex][index] = line[index];
	}
}

void NumberToChar(int number, char* score) {
	int lengthOfNum = LengthOfSymbolsInNumber(number);
	for (int index = lengthOfNum; index >= 0; index--) {
		score[index] = number % 10 + '0';
		number /= 10;
	}
}

void AddNewScoreToTheLeaderboard(char** leaderboard, int score, char* nickname, int position) {
	int index = 0;
	leaderboard[position][index++] = position + 1 + '0';
	leaderboard[position][index++] = ' ';
	for (int i = 0; nickname[i] != '\0'; i++) {
		leaderboard[position][index++] = nickname[i];
	}
	leaderboard[position][index++] = ' ';
	char charScore[10];
	NumberToChar(score, charScore);
	for (int i = 0; charScore[i] >= '0'; i++) {
		leaderboard[position][index++] = charScore[i];
	}
}

int LengthOfChar(char score[10]) {
	int length = 0;
	while (score[length++] >= '0');
	return length - 1;
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

void FindIndexOfLastSpace(int& indexOfLastSpace, char* line) {
	for (indexOfLastSpace; line[indexOfLastSpace] > 0; indexOfLastSpace++); // finds the last symbol in the line
	for (indexOfLastSpace; line[indexOfLastSpace] != ' '; indexOfLastSpace--); // finds the space after the nickname
}

int ReadHighScoreFromFile(char* line, char* nickname) {
	char highScore[10];
	int scoreIndex = 0;
	int indexOfLastSpace = 0;
	FindIndexOfLastSpace(indexOfLastSpace, line);
	indexOfLastSpace++;
	for (indexOfLastSpace; line[indexOfLastSpace] != '\0' && line[indexOfLastSpace] >= 0; indexOfLastSpace++) {
		highScore[scoreIndex++] = line[indexOfLastSpace];
	}
	return TransformCharToNumber(highScore);
}

char* EmptyChar(char* line) {
	for (int i = 0; line[i] != '\0' && line[i] >= 0; i++)
		line[i] = '\0';
	return line;
}

void AddingLineToFile(std::fstream& leaderboard, char* lineToBeAdded) {
	for (int i = 0; lineToBeAdded[i] != '\0' && lineToBeAdded[i] >= 0; i++) {
		leaderboard << lineToBeAdded[i];
	}
}

void CongratulatePlayer(int positionInRanking, int score, char* nickname) {
	std::cout << "Congratulations " << nickname << "! You climbed the leaderboard!\n";
	std::cout << "You are now position " << positionInRanking << " in the leaderboard with " << score << " score\n\n";
}

void CheckForLowerThanCurrScore(std::fstream& leaderboard, char* line, char** oldLeaderboard, int& countOfRows, int currScore, char* nickname, int& indexOfLineWithLowerScore, int const FILE_LINE_MAX_SIZE) {
	while (leaderboard.getline(line, FILE_LINE_MAX_SIZE)) {
		CopyFileLine(oldLeaderboard, line, countOfRows);
		countOfRows++;
		int fileScore = ReadHighScoreFromFile(line, nickname);
		if (currScore > fileScore && indexOfLineWithLowerScore == 5) {
			indexOfLineWithLowerScore = line[0] - '0' - 1;
		}
	}
}

void RearangeScoresInLeaderboard(int& countOfRows, int indexOfLineWithLowerScore, char** oldLeaderboard, int currScore, char* nickname) {
	for (int row = countOfRows - 1; row >= indexOfLineWithLowerScore; row--) {
		oldLeaderboard[row][0] = int(row + 2 + '0'); // changes the position of the ranking
		oldLeaderboard[row + 1] = EmptyChar(oldLeaderboard[row + 1]);
		CopyFileLine(oldLeaderboard, oldLeaderboard[row], row + 1);
	}
	oldLeaderboard[indexOfLineWithLowerScore] = EmptyChar(oldLeaderboard[indexOfLineWithLowerScore]);
	AddNewScoreToTheLeaderboard(oldLeaderboard, currScore, nickname, indexOfLineWithLowerScore);
	CongratulatePlayer(indexOfLineWithLowerScore + 1, currScore, nickname);
	if (countOfRows < 5) {
		countOfRows++;
	}
}

void IsFileOpened(std::fstream& file) {
	if (file.is_open() == false) {
		std::cout << "Failed to open the file.\n";
		exit(0);
	}
}

void CheckForHighscore(int currScore, char* nickname, char* dimension, int const NICKNAME_MAX_LETTERS, int const FILE_LINE_MAX_SIZE) {
	std::fstream leaderboard;
	char fileName[10];
	CreateFileName(fileName, dimension);
	int positionInRanking = 0;
	int highScore = 0;
	char* currNickname = new char[NICKNAME_MAX_LETTERS];
	leaderboard.open(fileName, std::fstream::in);
	IsFileOpened(leaderboard);
	char** oldLeaderboard{};
	oldLeaderboard = InitializeCharMatrix(oldLeaderboard, 5, FILE_LINE_MAX_SIZE);
	char* line = new char[FILE_LINE_MAX_SIZE];
	int countOfRows = 0, indexOfLineWithLowerScore = 5;
	CheckForLowerThanCurrScore(leaderboard, line, oldLeaderboard, countOfRows, currScore, nickname, indexOfLineWithLowerScore, FILE_LINE_MAX_SIZE);
	leaderboard.close();
	bool hasLeaderboardChanged = false;
	if (indexOfLineWithLowerScore != 5) {
		RearangeScoresInLeaderboard(countOfRows, indexOfLineWithLowerScore, oldLeaderboard, currScore, nickname);
		hasLeaderboardChanged = true;
	}
	else if (countOfRows != 5) {
		AddNewScoreToTheLeaderboard(oldLeaderboard, currScore, nickname, countOfRows);
		CongratulatePlayer(countOfRows + 1, currScore, nickname);
		countOfRows++;
		hasLeaderboardChanged = true;
	}
	if (hasLeaderboardChanged)
	{
		leaderboard.open(fileName, std::fstream::out);
		IsFileOpened(leaderboard);
		for (int i = 0; i < countOfRows; i++) {
			AddingLineToFile(leaderboard, oldLeaderboard[i]);
			if (i != countOfRows - 1) {
				leaderboard << '\n';
			}
		}
	}
	delete[] currNickname, line;
	leaderboard.close();
}

void IsNicknameValid(char* nickname, int const NICKNAME_MAX_LETTERS) {
	while (nickname[50] > 0) {
		std::cout << "The nickname should be max 50 symbols! Please enter new one: ";
		nickname = EmptyChar(nickname);
		std::cin.getline(nickname, NICKNAME_MAX_LETTERS);
	}
}

void IsDirectionValid(char* direction) {
	while (direction[1] != '\0' || (direction[0] != 'w' && direction[0] != 'a' && direction[0] != 's' && direction[0] != 'd'))
	{
		std::cout << "Please enter a valid direction!\n";
		std::cout << "Type one of the following - 'w' 'a' 's' 'd': ";
		std::cin >> direction;
	}
}

void ExecutingGame(int** matrix, int dimension, int& score, int SPACE_BETWEEN_NUMBERS) {
	while (true) {
		if (AreThereZerosInMatrix(matrix, dimension))
			PlaceRandomNumberInMatrix(matrix, dimension);
		PrintMatrix(matrix, dimension, SPACE_BETWEEN_NUMBERS);
		score = CalculateScore(matrix, dimension);
		std::cout << "Score: " << score << '\n';
		if (!AreTherePossibleMoves(matrix, dimension)) {
			std::cout << "There are no more possible moves!\n";
			std::cout << "Your result is: " << score << "\n\n";
			return;
		}
		else {
			char direction[50];
			std::cout << "Enter direction: ";
			std::cin >> direction;
			IsDirectionValid(direction);
			MovingNumbers(matrix, dimension, direction[0]);
		}
	}
}

void StartGame(char* nickname, char* matrixDimension, int const NICKNAME_MAX_LETTERS, int const FILE_LINE_MAX_SIZE, int const SPACE_BETWEEN_NUMBERS) {
	std::cout << "Please enter your nickname: ";
	std::cin.ignore();
	std::cin.getline(nickname, NICKNAME_MAX_LETTERS);
	IsNicknameValid(nickname, NICKNAME_MAX_LETTERS);
	std::cout << "Enter a number for the dimension of the matrix: ";
	std::cin >> matrixDimension;
	IsMatrixDimensionValid(matrixDimension);
	int dimension = matrixDimension[0] - '0';
	if (matrixDimension[1] == '0') {
		dimension *= 10;
		dimension += matrixDimension[1] - '0';
	}
	system("cls");
	int** matrix{};
	srand((unsigned)time(NULL));
	matrix = InitializeIntMatrix(matrix, dimension);
	FillMatrixWithZeros(matrix, dimension);
	int score = 0;
	ExecutingGame(matrix, dimension, score, SPACE_BETWEEN_NUMBERS);
	CheckForHighscore(score, nickname, matrixDimension, NICKNAME_MAX_LETTERS, FILE_LINE_MAX_SIZE);
	DeleteDynamicMemory(matrix, dimension);
}

void PrintLineOfLeaderboard(std::fstream& leaderboardFile, char* line, bool& isLeaderboardEmpty, int const FILE_LINE_MAX_SIZE) {
	while (leaderboardFile.getline(line, FILE_LINE_MAX_SIZE)) {
		isLeaderboardEmpty = false;
		std::cout << line;
		std::cout << '\n';
	}
}

void PrintLeaderboard(int const FILE_LINE_MAX_SIZE) {
	std::fstream leaderboardFile;
	std::cout << "Choose dimension you want to see the leaderboard for: ";
	char dimension[50];
	std::cin >> dimension;
	std::cout << '\n';
	IsMatrixDimensionValid(dimension);
	char fileName[10];
	CreateFileName(fileName, dimension);
	leaderboardFile.open(fileName);
	IsFileOpened(leaderboardFile);
	std::cout << "The " << dimension << "x" << dimension << " leaderboard: \n\n";
	char* line = new char[FILE_LINE_MAX_SIZE];
	bool isLeaderboardEmpty = true;
	PrintLineOfLeaderboard(leaderboardFile, line, isLeaderboardEmpty, FILE_LINE_MAX_SIZE);
	if (isLeaderboardEmpty) {
		std::cout << "There are no highscores!\n";
	}
	delete[] line;
	leaderboardFile.close();
	std::cout << '\n';
}

int main()
{
	int const NICKNAME_MAX_LETTERS = 100;
	int const SPACE_BETWEEN_NUMBERS = 6;
	int const FILENAME_MAX_SIZE = 10;
	int const FILE_LINE_MAX_SIZE = 70;
	char chosenOption[2];
	do {
		std::cout << "      MENU     " << '\n';
		std::cout << "1. Start game\n";
		std::cout << "2. Leaderboard\n";
		std::cout << "3. Quit\n";
		std::cout << "\nPlease enter a number to choose one of the options: ";
		char nickname[NICKNAME_MAX_LETTERS];
		std::cin >> chosenOption;
		IsChosenOptionValid(chosenOption);
		char matrixDimension[2];
		if (chosenOption[0] == '1') {
			StartGame(nickname, matrixDimension, NICKNAME_MAX_LETTERS, FILE_LINE_MAX_SIZE, SPACE_BETWEEN_NUMBERS);
		}
		else if (chosenOption[0] == '2') {
			PrintLeaderboard(FILE_LINE_MAX_SIZE);
		}
	} while (chosenOption[0] != '3');
	std::cout << "Goodbye!";
}
