#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <ctime>

void login();
void game();
void playerCard();
void dealerCard();
void printSum();
void printHand();

bool userResult{};
bool passResult{};

void login()
{
		
		const std::string username = "admin";
		const std::string password = "password";
		char user_array[5]{};
		char pass_array[10]{};
		char input_array[10]{};


		std::string userInput{};
		std::string passInput{};

		std::cout << "Enter username: ";
		getline(std::cin, userInput);

		strcpy_s(input_array, password.c_str());

		strcpy_s(input_array, userInput.c_str());

		std::cout << "Enter password: ";
		getline(std::cin, passInput);

		strcpy_s(input_array, password.c_str());

		strcpy_s(input_array, passInput.c_str());

		//Converts the password string and input string to char arrays.
		//Credit: https://www.geeksforgeeks.org/convert-string-char-array-cpp/

		for (int i = 0; i < 4; i++)
		{
			if (tolower(input_array[i]) == username[i]) //Compares input array with username.
			{
				userResult = true;
			}
			else
			{
				userResult = false;
				break;
			}
		}

		for (int i = 0; i < 9; i++)
		{
			if (tolower(input_array[i]) == password[i]) //Compares input array with password.
			{
				passResult = true;
			}
			else
			{
				passResult = false;
				break;
			}
		}

}

int playerHand[5];
int playerSum;
int playerHandSize;
bool playerStand = false;



int dealerHand[5];
int dealerSum;
int dealerHandSize;
bool dealerStand = false;


void playerCard()
{
	srand(time(0));

	if (playerHandSize <= 5)
	{
		playerHand[playerHandSize] = 1 + (rand() % 11);
		playerHandSize++;
	}

	else
	{
		std::cout << "You have the maximum amount of cards" << std::endl;
	}


}

void dealerCard()
{
	if (dealerHandSize <= 5)
	{
		dealerHand[dealerHandSize] = 1 + (rand() % 11);
		dealerHandSize++;
	}

	else
	{
		dealerStand = true;
	}
}

void printSum()
{
	for (int i = 0; i < playerHandSize; i++)
	{
		playerSum += playerHand[i];
	}

	for (int j = 0; j < dealerHandSize; j++)
	{
		dealerSum += dealerHand[j];
	}

	std::cout << "Your current hand sum: " << playerSum << std::endl;

	std::cout << "Dealer's hand sum: " << dealerSum << std::endl;
}

void printHand()
{
	std::cout << "Your hand: ";

	for (int i = 0; i < playerHandSize; i++)
	{
		std::cout << "|" << playerHand[i];
	}

	std::cout << "|";

	std::cout << std::endl;

	std::cout << "Dealer's hand: ";

	for (int j = 0; j < dealerHandSize; j++)
	{
		std::cout << "|" << dealerHand[j];
	}

	std::cout << "|";

	std::cout << std::endl;
}

void game()
{
	srand(time(0));

	playerSum = 0;
	playerHandSize = 0;

	dealerSum = 0;
	dealerHandSize = 0;


	system("cls");
	std::cout << "Welcome to Blackjack!\n";
	system("pause");
	system("cls");

	playerCard();
	playerCard();

	dealerCard();
	dealerCard();

	printHand();
	printSum();

	while (playerStand == false || dealerStand == false)
	{
	
	if (playerSum == 21)
	{
		std::cout << "Player has blackjack and wins the hand!";

	}
	else if (playerSum < 21)
	{
		std::cout << "H - hit  |  S - stand";
		std::cin >> ans;
	}



	if (dealerSum == 21)
	{
		std::cout << "Dealer has blackjack, dealer wins!";
	}
	else if (dealerSum < 17)
	{
		dealerCard();
	}

	}
}

int main()
{
	while (userResult == false || passResult == false)
	{
		login();

		if (userResult == true || passResult == true)
		{
			break;
		}
	}
	
	
	game();
}