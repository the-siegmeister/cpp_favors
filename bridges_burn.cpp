#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

class Person
{
private:
	std::string name;
	int speed;

public:
	void SetName(std::string name)
	{
		this->name = name;
	}

	std::string GetName()
	{
		return name;
	}

	void SetSpeed(int speed)
	{
		this->speed = speed;
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
			printf("There are no people on this side of the bridge.\n");
			return false;
		}
		else if (sidePeople.size() == 1)
		{
			printf("%s", sidePeople[1].GetName().c_str());
		}
		else
		{
			for (int i = 0; i < sidePeople.size(); i++)
			{
				if (i == sidePeople.size() - 1)
					printf(" and %s", sidePeople[i].GetName().c_str());
				else
					printf("%s", sidePeople[i].GetName().c_str());
			}
		}
		return true;
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

	bool IsPersonOnRightSide(std::string name)
	{
		auto it = find_if(this->rightSide.begin(), this->rightSide.end(), [&name](Person &obj) { return obj.GetName() == name; });

		if (it != this->rightSide.end())
			return true;

		return false;
	}

	int GetTimeLeft()
	{
		return this->timeLeft;
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
		std::cout << "MENU FOR FAMILY CRISIS\n\n";
		printf("[%d] %s (%d second to cross the bridge)\n", 1, "John", 1);
		printf("[%d] %s (%d seconds to cross the bridge)\n", 3, "Mark", 3);
		printf("[%d] %s (%d seconds to cross the bridge)\n", 6, "John", 6);
		printf("[%d] %s (%d seconds to cross the bridge)\n", 8, "John", 8);
		printf("[%d] %s (%d seconds to cross the bridge)\n", 12, "John", 12);
	}

	void PrintLeftSide()
	{
		if (PrintMembersOnSide(this->leftSide))
			printf(" is now on the left side of the bridge.\n");
	}

	void PrintRightSide()
	{
		if (PrintMembersOnSide(this->leftSide))
			printf(" is in the right side of the bridge.\n");
	}
};

int main()
{
	CrossingGame game;
	printf("John is on the right side %d\n", game.IsPersonOnRightSide("John"));

	return 0;
}

// code for switching players
// int index = std::distance(this->rightSide.begin(), it);
// this->leftSide.push_back(this->rightSide[index]);
// this->rightSide.erase(this->rightSide.begin() + index);
