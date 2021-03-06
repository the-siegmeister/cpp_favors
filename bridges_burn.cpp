#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
#include <iterator>

class Person
{
private:
	std::string name;
	int speed;

public:
	std::string GetName()
	{
		return name;
	}

	int GetSpeed()
	{
		return this->speed;
	}

	Person(std::string name, int speed)
	{
		this->name = name;
		this->speed = speed;
	}
};

class CrossingGame
{
private:
	bool lampIsRightSide = true;
	int timeLeft = 30;
	int choices[5] = {1, 3, 6, 8, 12};
	std::vector<Person> leftSide;
	std::vector<Person> rightSide;

	bool PrintMembersOnSide(std::vector<Person> sidePeople)
	{
		if (!sidePeople.size())
		{
			printf("There are no more people on this side of the bridge.\n");
			return false;
		}
		else if (sidePeople.size() == 1)
		{
			printf("%s", sidePeople[0].GetName().c_str());
		}
		else
		{
			printf("\n");
			for (int i = 0; i < sidePeople.size(); i++)
			{
				if (i == sidePeople.size() - 1)
					printf("and %s", sidePeople[i].GetName().c_str());
				else
					printf("%s, ", sidePeople[i].GetName().c_str());
			}
		}
		return true;
	}

	void SetTimeLeft(int s)
	{
		this->timeLeft = s;
	}

public:
	void SwitchLampSide()
	{
		this->lampIsRightSide = !this->lampIsRightSide;
	}

	bool LampIsOnRightSide()
	{
		return this->lampIsRightSide;
	}

	int GetTimeLeft()
	{
		return this->timeLeft;
	}

	bool IsPersonOnRightSide(int speed)
	{
		auto it = find_if(this->rightSide.begin(), this->rightSide.end(), [speed](Person &obj) { return obj.GetSpeed() == speed; });

		if (it != this->rightSide.end())
			return true;

		return false;
	}

	int GetMembersLeft()
	{
		return this->rightSide.size();
	}

	CrossingGame()
	{
		this->rightSide.push_back(Person("John", 1));
		this->rightSide.push_back(Person("Mark", 3));
		this->rightSide.push_back(Person("Mommy Betty", 6));
		this->rightSide.push_back(Person("Daddy Bo", 8));
		this->rightSide.push_back(Person("Grandpa Gusto", 12));
	}

	void PrintMenu()
	{
		std::cout << "\nMENU FOR FAMILY CRISIS\n\n";
		printf("[%d] %s (%d second to cross the bridge)\n", 1, "John", 1);
		printf("[%d] %s (%d seconds to cross the bridge)\n", 3, "Mark", 3);
		printf("[%d] %s (%d seconds to cross the bridge)\n", 6, "Mommy Betty", 6);
		printf("[%d] %s (%d seconds to cross the bridge)\n", 8, "Daddy Bo", 8);
		printf("[%d] %s (%d seconds to cross the bridge)\n", 12, "Grandpa Gusto", 12);
	}

	void PrintLeftSide(std::string extra)
	{
		if (PrintMembersOnSide(this->leftSide))
		{
			if (extra == "")
				printf(" is now on the left side of the bridge.\n");
			else
				printf(" %s\n", extra.c_str());
		}
	}

	void PrintRightSide()
	{
		if (PrintMembersOnSide(this->rightSide))
			printf(" is on the right side of the bridge.\n");
	}

	int *GetMoveInput()
	{
		bool again = false;
		int *arr = new int[2];
		do
		{
			arr[1] = 0, arr[2] = 0;
			again = false;
			std::string input = "";
			int secondIndex = 0;
			std::cout << "\nEnter the one or two persons that will cross the bridge: ";
			std::getline(std::cin, input);

			// .split() but way too primitive
			secondIndex = input.find(" ");
			std::string f1 = input.substr(0, secondIndex);
			std::string f2;
			try
			{
				arr[0] = stoi(f1);
				// the long line after isValid1 is a one-liner for finding out if input exists in choices
				bool isValid1 = std::find(std::begin(choices), std::end(choices), arr[0]) != std::end(choices);
				bool isValid2 = true;
				if (secondIndex != -1)
				{
					f2 = input.substr(secondIndex, -1);
					arr[1] = stoi(f2);
					isValid2 = std::find(std::begin(choices), std::end(choices), arr[1]) != std::end(choices);
				}
				// if any of the inputs are invalid
				// if both have the same value (can't move the person twice in on press)
				if (!(isValid1 && isValid2) || arr[0] == arr[1])
				{
					again = true;
					printf("\nPick again. That shit cray\n");
				}
			}
			catch (...)
			{
				again = true;
				std::cout << "\n!!! WARNING !!! INVALID INPUT\n";
			}
		} while (again);
		return arr;
	}

	bool MoveToOtherSide(int arr[])
	{
		int people = 1;
		int personTime = -1;
		bool toTheLeft = this->IsPersonOnRightSide(arr[0]);

		// check if people are on the same side
		if (arr[1] != 0)
		{
			people = 2;
			if (!this->IsPersonOnRightSide(arr[1]) == toTheLeft)
			{
				printf("\nThe people you chose aren't on the same side!\n");
				return false;
			}
		}

		// check if the lamp is accessible to them
		if (!(this->LampIsOnRightSide() == toTheLeft))
		{
			printf("\nThe lamp is not on that side of the bridge!\n");
			return false;
		}

		for (int i = 0; i < people; i++)
		{
			int speed = arr[i];
			if (toTheLeft)
			{
				//printf("The person is moving from right to left\n");
				auto it = find_if(this->rightSide.begin(), this->rightSide.end(), [speed](Person &obj) { return obj.GetSpeed() == speed; });
				int index = std::distance(rightSide.begin(), it);
				this->leftSide.push_back(*it);

				if (this->rightSide[index].GetSpeed() > personTime)
					personTime = this->rightSide[index].GetSpeed();

				this->rightSide.erase(it);
			}
			else if (!toTheLeft)
			{
				//printf("The person is moving from left to right\n");
				auto it = find_if(this->leftSide.begin(), this->leftSide.end(), [speed](Person &obj) { return obj.GetSpeed() == speed; });
				int index = std::distance(leftSide.begin(), it);
				this->rightSide.push_back(*it);

				printf("\n%s will go back to the right side of the bridge to get another member of the family.\n", this->leftSide[index].GetName().c_str());

				if (this->leftSide[index].GetSpeed() > personTime)
					personTime = this->leftSide[index].GetSpeed();

				this->leftSide.erase(it);

				this->PrintLeftSide("remains in the left side of the bridge.");
			}
		}

		this->SetTimeLeft(this->GetTimeLeft() - personTime);

		if (this->GetTimeLeft() <= 0)
		{
			return false;
		}

		if (toTheLeft)
		{
			this->PrintLeftSide("");
		}
		printf("\nLamp is good for = %d seconds\n", this->GetTimeLeft());
		this->PrintRightSide();

		return true;
	};
};

void GameLoop()
{
	CrossingGame game;
	bool gameOver = false;

	do
	{
		game.PrintMenu();
		int *arr = game.GetMoveInput();
		if (game.MoveToOtherSide(arr))
		{
			game.SwitchLampSide();
		}

		if (game.GetTimeLeft() <= 0 && game.GetMembersLeft() > 0)
		{
			gameOver = true;
			printf("\n\nYou lose...");
		}
		else if (game.GetTimeLeft() >= 0 && game.GetMembersLeft() <= 0)
		{
			gameOver = true;
			printf("\n\nYou win this time!");
		}

		system("read -p '\nPress any key to continue' var");
		/*
			if you're on windows, replace the line that says system with:
			system("pause");
			printf("\nPress any key to continue");
			(not sure though)	
		*/

	} while (!gameOver);
	printf("\n[G A M E O V E R]\n");
}

int main()
{
	GameLoop();
	return 0;
}
