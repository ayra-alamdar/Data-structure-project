#include <iostream>
#include <string>
#include <cstdlib>
#include<Windows.h>
#include <ctime>
#include "Vector.h"
using namespace std;

/// <summary>
///  C : clear path
///  J : jewel
///	 P : potion
///	 W : weapon
///	 % : Death point
///	 # : obstacle
///	 & : Dragon
///	 $ : Goblin
///	 @ : Werewolf
///	 * : Crystal(goal point)
/// </summary>
/// <returns></returns>
int main()
{
	string possible = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCJPW%#&$@*";
	int index = possible.length();
	srand(time(NULL));
	int rows = rand() % 20+10;
	Vector<Vector<char>> obj(rows);
	
	for (int i = 0; i < rows; i++)
	{
		Vector<char> temp;
		for (int j = 0; j < rows; j++)
		{
			int val = rand() % index;
			temp.push_back(possible[val]);
		}
		obj.push_back(temp);
	}
	
	

	while (true)
	{
		system("cls");
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		for (int i = 0; i < rows; i++)
		{
			cout << "\t\t\t\t\t\t\t";
			for (int j = 0; j < rows; j++)
			{
				cout << obj[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "C : clear path J : jewel P : potion W : weapon % : Death point # : obstacle & : Dragon $ : Goblin @ : Werewolf * : Crystal(goal point)";
		cin.get();
	}
	
}
