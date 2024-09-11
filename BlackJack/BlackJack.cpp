#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;

template<typename T>
T GetInput(string inputMessage);
void StartGame();
int Menu();
int RandNumber(int max, int min);
int AceChoice();

int main()
{
	bool endPrg = false;
	while (endPrg == false) 
	{
		int menuOption = Menu();
		if (menuOption == 1)
		{
			StartGame();
		}
		else if (menuOption == 2)
		{
			endPrg = true;
		}
	}
}
template <typename T>
T GetInput(string inputMessage)
{
	T userInput;
	while (true)
	{
		cout << inputMessage << endl << endl;
		string rawInput;
		getline(cin, rawInput);
		try
		{
			istringstream iss(rawInput);
			iss >> userInput;
			if (iss.fail() && iss.peek() != EOF)
			{
				throw new bad_cast();
			}
		}
		catch (bad_cast)
		{
			cout << "This input is of the wrong data type" << endl << endl;
		}
	}
}
int GetChoice(string inputMessage, vector<string> options)
{
	int userInput = 0;
	while(true)
	{
		for (int x = 0; x < options.size(); x++)
		{
			cout << x + 1 << " ----> " << options[x] << endl << endl;
		}
		cout << inputMessage << endl << endl;
		string rawInput;
		getline(cin, rawInput);
		try
		{
			istringstream iss(rawInput);
			iss >> userInput;
			if (iss.fail() && iss.peek() != EOF)
			{
				throw logic_error("This is not the right data type... The value needs to be a whole number");
			}
			if (userInput < 1)
			{
				throw out_of_range("This is beneath the range of choices... choice should be 1 or more");
			}
			else if (userInput > options.size())
			{
				throw out_of_range("This is over the range of choices... use a smaller value");
			}
			break;
		}
		catch (const exception& e)
		{
			cerr << e.what() << endl << endl;
		}
	}
	return userInput;
}
int RandNumber(int max, int min)
{
	srand((unsigned) time(NULL));
	int randNumber = min + (rand() % (max - min + 1));
	return randNumber;
}
int Menu()
{
	vector<string> menuOptions = { "Start BlackJack", "Exit" };
	int menuChoice = GetChoice("What would you like to do?", menuOptions);
	return menuChoice;
}
void StartGame()
{
	vector<string> cardNames{ "Ace", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
	map<int, int> cards = { {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {11, 4}, {12, 4} };
	int roundPlayed = 0;
	int playerScore = 0;
	int cardsIndex = 0;
	while (true)
	{
		cout << "Round: " << roundPlayed + 1 << endl;
		cout << "Score: " << playerScore << endl;
		if (roundPlayed == 0)
		{
			for (int x = 0; x < 2; x++)
			{
				while (true)
				{
					cardsIndex = RandNumber(12, 0);
					cout << "Card: " << cardNames[cardsIndex] << endl;
					if (cards[cardsIndex] > 0)
					{
						if (cardsIndex < 9 && cardsIndex != 0)
						{
							playerScore += cardsIndex + 1;
						}
						else if (cardsIndex == 0)
						{
							playerScore += AceChoice();
						}
						else if (cardsIndex >= 9)
						{
							playerScore += 10;
						}
						cards[cardsIndex] -= 1;
						break;
					}
				}
			}
			roundPlayed++;
		}
		vector<string> roundOptions = { "Hit", "Stick" };
		int roundChoice = GetChoice("What would you like to do?", roundOptions);
		if (roundChoice == 1)
		{
			while (true)
			{
				cardsIndex = RandNumber(12, 0);
				cout << "Card: " << cardNames[cardsIndex] << endl;
				if (cards[cardsIndex] > 0)
				{
					if (cardsIndex < 9 && cardsIndex != 0)
					{
						playerScore += cardsIndex + 1;
					}
					else if (cardsIndex == 0)
					{
						playerScore += AceChoice();
					}
					else if (cardsIndex >= 9)
					{
						playerScore += 10;
					}
					cards[cardsIndex] -= 1;
					roundPlayed++;
					break;
				}
			}
		}
		else if (roundChoice == 2)
		{
			while (true)
			{
				cardsIndex = RandNumber(12, 0);
				cout << "Card: " << cardNames[cardsIndex] << endl;
				if (cards[cardsIndex] > 0)
				{
					cards[cardsIndex] --;
					roundPlayed++;
					break;
				}
			}
		}
		if (playerScore == 21)
		{
			cout << "You Win!!!" << endl;
			break;
		}
		else if (playerScore > 21)
		{
			cout << "You lost..." << endl;
			cout << "Your final score: " << playerScore << endl;
			cout << "Your final round: " << roundPlayed << endl;
			break;
		}
	}
}
int AceChoice()
{
	vector<string> aceOptions = { "11", "1" };
	int aceChoice = GetChoice("What would you like your ace score to be?", aceOptions);
	int points = 0;
	if (aceChoice == 1)
	{
		points += 11;
	}
	else if (aceChoice == 2)
	{
		points++;
	}
	return points;
}