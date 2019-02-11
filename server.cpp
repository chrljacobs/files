#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <time.h>
using namespace std;

//the number of possilbe spaces. For a 3x3, 9, for a 4x4, 16. CHANGE ME TO TEST
#define SIZE 9
struct node {
	int state[SIZE];
	friend bool operator == (node x, node y) {
		for (int i = 0; i < SIZE; i++) {
			if (x.state[i] != y.state[i]) return false;
		}
		return true;
	}
	friend bool operator != (node x, node y) {
		for (int i = 0; i < SIZE; i++) {
			if (x.state[i] != y.state[i]) return true;
		}
		return false;
	}
} gameStart = { 0 };

int comChar = 2; //1 = X, 2 = O
int userChar = 1;

node userTurn(node option);
node comTurn(node option);
int gameWon(node option); //complete
double minPick(node option, double a, double b, double count);
double maxPick(node option, double a, double b, double count);
vector<node> getSucc(node option, int whosChoice); //complete
void printGame(node option); //complete
void printGameNumbers(); //complete!!!yay

int main() {
	node deleteme;
	string winner[3] = { "User","Stalemate","Computer" };
	string stale;
	char XorO;
	//user chooses to be x or o
	while (true) {
		cout << "Do you wanna be X or O? ";
		cin >> XorO;
		cin.clear();
		cin.ignore(10000, '\n');
		if (XorO == 79 || XorO == 111) {
			comChar = 1;
			userChar = 2;
			break;
		}
		else if (XorO == 88 || XorO == 120) {
			break;
		}
		else {
			system("clear");
			cout << "Error. Invalid Character.\n";
		}

	}
	//start of game
	deleteme = gameStart;//{0,1,2,0,0,0,1,2,0,0,0,0,0,0,0,0};
	while (gameWon(deleteme) == 2) {
		deleteme = userTurn(deleteme);
		if (gameWon(deleteme) < 2) break;
		deleteme = comTurn(deleteme);
	}
	printGame(deleteme);
	if (gameWon(deleteme) + 1 == 1)
		cout << "\nThe game was a stalemate.\n";
	else
		cout << "\nThe winner is the " << winner[gameWon(deleteme) + 1] << "!\n";
	return 0;
}

vector<node> getSucc(node option, int whosChoice) {
	node posChoice = option;
	vector<node> returnMe;
	for (int i = 0; i < SIZE; i++) {
		if (option.state[i] == 0) {
			posChoice.state[i] = whosChoice;
			returnMe.push_back(posChoice);
			posChoice.state[i] = 0;
		}
	}
	return returnMe;
}

//return 1 if com wins, -1 if user wins, 0 if stalemate, 2 if incomplete
int gameWon(node option) {
	int boardSize = static_cast<int>(sqrt(SIZE));
	int place1, place2, place3;
	//check verticle
	for (int i = 0; i < boardSize*(boardSize - 2) /*this took thinking, trust me, it works*/; i++) {
		place1 = option.state[i];
		place2 = option.state[i + boardSize];
		place3 = option.state[i + (2 * boardSize)];
		if (place1 != 0 && place1 == place2 && place2 == place3) {
			if (place1 == comChar)
				return 1;
			return -1;
		}
	}
	//check diagonal
	for (int i = 0; i < 2 + (boardSize - 3) * 6; i++) {
		//for diagonal down-left for board size 3
		if (boardSize < 4 && i > 0) i = 2;
		if (i % 4 < 2) {
			place1 = option.state[i];
			place2 = option.state[i + boardSize + 1];
			place3 = option.state[i + (2 * (boardSize + 1))];
		}
		else {
			place1 = option.state[i];
			place2 = option.state[i + boardSize - 1];
			place3 = option.state[i + (2 * (boardSize - 1))];
		}
		if (place1 != 0 && place1 == place2 && place2 == place3) {
			if (place1 == comChar)
				return 1;
			return -1;
		}
	}

	//check horizontal
	for (int i = 0; i < boardSize*(boardSize - 2); i++) {
		if (i < boardSize) {
			place1 = option.state[boardSize*i];
			place2 = option.state[boardSize*i + 1];
			place3 = option.state[boardSize*i + 2];
		}
		else {
			place1 = option.state[boardSize*(i % boardSize) + 1];
			place2 = option.state[boardSize*(i % boardSize) + 2];
			place3 = option.state[boardSize*(i % boardSize) + 3];
		}
		if (place1 != 0 && place1 == place2 && place2 == place3) {
			if (place1 == comChar)
				return 1;
			return -1;
		}
	}
	for (int i = 0; i < SIZE; i++) {
		if (option.state[i] == 0)
			return 2;
	}
	return 0;
}

void printGame(node option) {
	int boardSize = static_cast<int>(sqrt(SIZE));
	char XorO = ' ', Ascii = 196, line = 179, plus = 197;
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (option.state[i*boardSize + j] == 0) {
				XorO = ' ';
			}
			else XorO = (option.state[i*boardSize + j] == 1) ? 88 : 79;
			if (j%boardSize == boardSize - 1) {
				cout << XorO;
			}
			else {
				cout << XorO << line;
			}
		}
		if (i < boardSize - 1) {
			cout << "\n";
			for (int k = 0; k < boardSize - 1; k++) {
				cout << Ascii << plus;
			}
			cout << Ascii << endl;
		}
		else cout << endl << endl;
	}
}

void printGameNumbers() {
	int boardSize = static_cast<int>(sqrt(SIZE));
	int trueNum = 0;
	char Ascii = 196, line = 179, plus = 197;
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			trueNum = j + i * boardSize;
			if (j%boardSize == boardSize - 1) {
				cout << trueNum;
			}
			else
			{
				cout << trueNum << line;
			}
		}
		if (i < boardSize - 1) {
			cout << "\n";
			for (int k = 0; k < boardSize - 1; k++) {
				cout << Ascii << plus;
			}
			cout << Ascii << endl;
		}
		else cout << endl;
	}
}

node userTurn(node state) {
	printGame(state);
	int boardSize = static_cast<int>(sqrt(SIZE));
	char input;
	int modIn = -1;
	while (true) {
		printGameNumbers();
		cout << "Please input the Hexidecimal char to place your " << ((userChar == 1) ? "X: " : "O: ");
		cin >> input;
		cin.clear();
		cin.ignore(10000, '\n');
		if (input >= 48 && input <= 57) {
			if (boardSize < 4 && input == 57) {
				system("clear");
				cout << "Error: The entered Character is invalid.\n";
				printGame(state);
				continue;
			}
			modIn = input - 48;
		}
		else if (input >= 65 && input <= 70 && boardSize > 3) {
			modIn = input - 55; //-64 so A = 0, then +10 so A = 10
		}
		else if (input >= 97 && input <= 102 && boardSize > 3) {
			modIn = input - 87; //-96 so a = 0, then +10 so a = 10
		}
		else {
			system("clear");
			cout << "Error: The entered Character is invalid.\n";
			printGame(state);
			continue;
		}
		if (state.state[modIn] != 0) {
			system("clear");
			cout << "Error: The entered Location is invalid.\n";
			printGame(state);
			continue;
		}
		break;
	}
	state.state[modIn] = userChar;
	printGame(state);
	system("clear");
	return state;
}

node comTurn(node option) {
	double count = 0;
	cout << "\nComputer's turn\n";
	vector<node> children = getSucc(option, comChar);
	double maxGame = -100;
	double temp;
	double a = -1;
	double b = 1;
	node favChild;
		int userPlace = 0;
		for (int i = 0; i < SIZE; i++) {
			if (option.state[i] == userChar) userPlace = i;
		}
		for (int i = 0; i < children.size(); i++)
		{
			temp = minPick(children[i], a, b, count);
			if (temp >= maxGame) {
				favChild = children[i];
				maxGame = temp;
			}
			if (temp > b) return favChild;
			else (a < maxGame) ? maxGame : a;
		}
	return favChild;
}

double minPick(node option, double a, double b, double count) {
	count += 0.01;
	vector<node> children = getSucc(option, userChar);
	double minGame = 100;
	double temp;
	if (gameWon(option) == 2) {
		for (int i = 0; i < children.size(); i++) {
			temp = maxPick(children[i], a, b, count);
			if (minGame > temp) minGame = temp;
			if (temp <= a) return temp + count;
			else b = (b > minGame) ? minGame : b;
			//else b = (b < temp) ? b : temp;
			//if (count > 7) return temp;
		}
		return minGame + count;
	}
	else {
		temp = gameWon(option);
		if (temp != 0)
			return temp;
		else
			return temp + count;
	}
}

double maxPick(node option, double a, double b, double count) {
	count += 0.01;
	vector<node> children = getSucc(option, comChar);
	double maxGame = -100;
	double temp;
	if (gameWon(option) == 2) {
		for (int i = 0; i < children.size(); i++) {
			temp = minPick(children[i], a, b, count);
			if (temp > maxGame) maxGame = temp;
			if (temp >= b) return temp - count;
			else a = (a < maxGame) ? maxGame : a;
		}
		return maxGame - count;
	}
	else {
		temp = gameWon(option);
		if (temp != 0)
			return temp;
		else
			return temp - count;
	}
}
