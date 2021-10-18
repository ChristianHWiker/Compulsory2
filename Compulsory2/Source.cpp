#include "declarations.h"

void login() //Copied my login from mock exam and added extra strings for username.
{
	int failCount{};
	while (failCount < 5) //Counts the wrong attempts to login up to 5.
	{
		const std::string username = "admin";
		const std::string password = "password";
		char user_array[6]{};
		char pass_array[10]{};
		char input_array[10]{};


		std::string userInput{};
		std::string passInput{};

		std::cout << "Enter username: ";
		getline(std::cin, userInput);

		strcpy_s(user_array, userInput.c_str());

		std::cout << "Enter password: ";
		getline(std::cin, passInput);

		strcpy_s(pass_array, passInput.c_str());

		//Converts the password string and input string to char arrays.
		//Credit: https://www.geeksforgeeks.org/convert-string-char-array-cpp/

		for (int i = 0; i < 4; i++)
		{
			if (tolower(user_array[i]) == username[i]) //Compares user array with username.
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
			if (tolower(pass_array[i]) == password[i]) //Compares password array with password.
			{
				passResult = true;
			}
			else
			{
				passResult = false;
				break;
			}
		}


		if (userResult == true && passResult == true) 
		{
			return;
		}
		else 
		{
			failCount++; //Failed attempt is added here.
		}
	}
	std::cout << "Too many failed attempts, closing" << std::endl;
	exit(0); //Exits the program after the while loop breaks from failed attempts.
}



void playerCard()
{
		playerHand.push_back(1 + (rand() % 10)); //Stores a random number from 1-10 in the vector used for cards in the player's hands.
}

void dealerCard()
{
		dealerHand.push_back(1 + (rand() % 10)); //Same as above but for the AI. These functions allow me to simply write player/dealerCard(): wherever a card should be added to either's hand in the main game function.
}

void printSum()
{	
	std::cout << "Your current hand sum: " << playerSum() << std::endl; //Prints the calculated sums of the cards in the player/dealer's hand.
	std::cout << "Dealer's hand sum: " << dealerSum() << std::endl;
}

void printHand() //This function prints the dealer and player's hands by looping through the vector and finding the numerical values while adding a line to divide them for ease of eyes.
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
	dealerTurn = false; //Resets the variable to its original state (line 166-122).

	system("cls"); //Clears login screen.
	std::cout << "Welcome to Blackjack!\n";
	
	std::cout << "Your capital: " << playerCurrency << std::endl;
	std::cout << "House capital: " << dealerCurrency << std::endl; //Shows the player and dealer's start capitals and asks for the amount the player wants to bet. (line 127-130)
	std::cout << "Enter bet amount: ";
	std::cin >> betInput;
	std::cin.ignore(10000, '\n'); //Clears cin to prevent bugs.
	std::cin.clear();

	if (betInput > dealerCurrency || betInput > playerCurrency)
	{
		std::cout << "Invalid amount"; //Prevents player from betting more than the player's or dealer's capitals. (line 134-140)
		std::cout << std::endl;
		system("pause");
		return;
	}

	betWin = betInput * 2; //The amount of currency the winner wins.

	playerCurrency -= betInput; //Removes the bet amount from the loser.
	dealerCurrency -= betInput;

	system("cls");

	//playerCard(); Can be uncommented for 2 starting cards for either party.
	playerCard();

	//dealerCard();
	dealerCard();

	printHand(); //Calls both these functions as they are explained above.
	printSum();

	if (stopPlaying == true) //stopPlaying bool that's set to true whenever a win condition is met and an if condition that restarts the game.
	{
		game();
	}

	while (playerTurn == true) //Loop  that checks for win conditions and adds currency to the winner. Sleep is added so things don't move too fast (especially the AI turn).
								// The winner is decided by functions that calculate the sums of both parties' hands. (lines 163-302).
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
			std::cout << "H - hit  |  S - stand" << std::endl; //Asks player if they want to hit or stand.
			std::cin >> input;
			if (input == tolower('H'))
			{
				system("cls");
				playerCard();
				bool changed = false;
				while (playerHand.back() == 1 && changed == false) //Allows the player to decide if an ace (1) should have the numerical value of 1 or 11 with the help of a bool to break the loop.
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
		else if (dealerSum() < 17) //The dealer will add another card to their hand while their sum is below 17 in accordance with the game rules.
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
	srand(time(0)); //Seeds the random number generator.
	login(); //Calls login function as explained above.
	while (playerCurrency > 0 && dealerCurrency > 0) //Keeps the game running until someone runs out of currency.
	{
		game();
	}
	return 0;
}

int playerSum() 
{
	int sum{};
	for (int i{}; i < playerHand.size(); i++) //Calculates the sum of the player's hand.
	{
		sum += playerHand[i];
	}
	return sum;
}

int dealerSum()
{
	int sum{};
	for (int i{}; i < dealerHand.size(); i++) //Calculates the sum of the dealer's hand.
	{
		sum += dealerHand[i];
	}
	return sum;
}