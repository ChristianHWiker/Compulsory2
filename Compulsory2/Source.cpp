#include "declarations.h"

void login()
{
	int failCount{};
	while (failCount < 5) 
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


		if (userResult == true && passResult == true) {
			return;
		}
		else {
		failCount++;
		}
	}
	std::cout << "Too many failed attempts, closing" << std::endl;
	exit(0);
}




void playerCard()
{
		playerHand.push_back(1 + (rand() % 10));
}

void dealerCard()
{
		dealerHand.push_back(1 + (rand() % 10));
}

void printSum()
{	
	std::cout << "Your current hand sum: " << playerSum() << std::endl;
	std::cout << "Dealer's hand sum: " << dealerSum() << std::endl;
}

void printHand()
{
	std::cout << "Your hand: ";

	for (int i{}; i < playerHand.size(); i++) 
	{
		std::cout << playerHand[i] << " | ";
	}
	std::cout << std::endl;


	std::cout << "Dealer's hand: ";

	
	for (int i{}; i < dealerHand.size(); i++) 
	{
		std::cout << dealerHand[i] << " | ";
	}
	std::cout << std::endl;
	
}

void game()
{
	playerHand.clear();
	dealerHand.clear();

	stopPlaying = false;

	playerTurn = true;
	dealerTurn = false;

	system("cls");
	std::cout << "Welcome to Blackjack!\n";
	
	std::cout << "Your capital: " << playerCurrency << std::endl;
	std::cout << "House capital: " << dealerCurrency << std::endl;
	std::cout << "Enter bet amount: ";
	std::cin >> betInput;
	std::cin.ignore(10000, '\n');
	std::cin.clear();

	if (betInput > dealerCurrency || betInput > playerCurrency)
	{
		std::cout << "Invalid amount";
		std::cout << std::endl;
		system("pause");
		return;
	}

	betWin = betInput * 2;

	playerCurrency -= betInput;
	dealerCurrency -= betInput;

	system("cls");

	//playerCard();
	playerCard();

	//dealerCard();
	dealerCard();

	printHand();
	printSum();

	if (stopPlaying == true)
	{
		game();
	}

	while (playerTurn == true)
	{


		if (playerSum() == 21)
		{
			std::cout << "Player has blackjack and wins the hand!";
			Sleep(2000);
			playerTurn = false;
			playerCurrency += betWin;
			stopPlaying = true;
			break;

		}
		else if (playerSum() > 21)
		{
			std::cout << "You bust! Dealer wins!";
			Sleep(2000);
			playerTurn = false;
			dealerCurrency += betWin;
			stopPlaying = true;
			break;
		}
		else if (playerSum() < 21)
		{
			std::cout << "H - hit  |  S - stand" << std::endl;
			std::cin >> input;
			if (input == tolower('H'))
			{
				system("cls");
				playerCard();
				bool changed = false;
				while (playerHand.back() == 1 && changed == false)
				{
					std::cout << "Make the ace 1 or 11?: ";
					std::cin >> aceInput;

					switch (aceInput)
					{
					case 1:
						playerHand.back() = 1;
						changed = true;
						break;
					case 11:
						playerHand.back() = 11;
						changed = true;
						break;
					default:
						std::cout << "Invalid input" << std::endl;
						break;
					}
				}
				
				printHand();
				printSum();
				count++;
			}
			else if (input == tolower('S'))
			{
				system("cls");
				playerTurn = false;
				dealerTurn = true;

			}


		}


	}

	while (dealerTurn == true)
	{

		if (dealerSum() == 21)
		{
			std::cout << "Dealer has blackjack and wins the hand!";
			Sleep(2000);
			dealerCurrency += betWin;
			stopPlaying = true;
			break;
		}
		else if (dealerSum() > 21)
		{
			std::cout << "Dealer busts! You win!";
			Sleep(2000);
			playerCurrency += betWin;
			stopPlaying = true;
			break;
		}
		else if (dealerSum() < 17)
		{
			Sleep(1000);
			system("cls");
			dealerCard();
			printHand();
			printSum();
			count++;
				
			
		}
		else if (dealerSum() >= 17)
		{
			dealerTurn = false;
			//break;
		}

	}

	while (playerTurn == false && dealerTurn == false && stopPlaying == false)
	{

		if (playerSum() > dealerSum())
		{
			std::cout << "You win the hand!";
			Sleep(2000);
			playerCurrency += betWin;
			stopPlaying = true;
			break;
				
		}
		else if (dealerSum() > playerSum())
		{
			std::cout << "Dealer wins the hand!";
			Sleep(2000);
			dealerCurrency += betWin;
			stopPlaying = true;
			break;
				
		}
		else if (playerSum() == dealerSum())
		{
			std::cout << "It's a draw!";
			break;
		}

	}

	
}

int main()
{
	srand(time(0));
	login();
	while (playerCurrency > 0 && dealerCurrency > 0)
	{
		game();
	}
	return 0;
}

int playerSum() 
{
	int sum{};
	for (int i{}; i < playerHand.size(); i++) 
	{
		sum += playerHand[i];
	}
	return sum;
}

int dealerSum()
{
	int sum{};
	for (int i{}; i < dealerHand.size(); i++)
	{
		sum += dealerHand[i];
	}
	return sum;
}