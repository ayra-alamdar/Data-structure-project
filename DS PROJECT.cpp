#include <iostream>
#include <string>
#include <cstdlib>
#include<iomanip>
#include <conio.h>
#include <Windows.h>
#include <ctime>
using namespace std;

#include "List.h"
#include "AVL tree.h"
#include"Game.h"
#include"Queue.h"
#include"Graph Functions.h"
int main()
{
	string Possibilities = "CJPW%#&$@*";
	string possible = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCJPW%#&$@";
	int index = possible.length();

	srand(time(NULL));

	int N = rand() % 20 + 10;
	List<List<char>> obj(N);

	List<List<int>> VALUES(N);

	List<int> WeaponIndex(5);
	List<int> PotionIndex(5);
	List<int> JewelIndex(5);

	for (int i = 0; i < N; i++)
	{
		List<char> temp;
		List<int> temp2;
		for (int j = 0; j < N; j++)
		{
			int val = rand() % index;
			temp.push_back(possible[val]);
			temp2.push_back(score(possible[val]));
		}
		obj.push_back(temp);
		VALUES.push_back(temp2);
	}

	obj[0].set(0, 'C');
	obj[N - 1].set(N - 1, '*');
	string PlayerName = "";
	char PlayerCharacter = '\0';

	


	cout << "************************************************************The Quest for the Crystal Kingdom************************************************************" << endl;
	cout << endl;
	cout << endl;
	cout << "\t\tEnter Your Name : ";
	getline(cin, PlayerName);
	cout << endl;
	cout << endl;
	cout << "\t\tEnter Your Character : ";
	cin >> PlayerCharacter;
	cout << endl;
	cout << endl;
	cout << "\t\tThe Grid Size is : " << N << endl;
	cout << "***********************************************************************************************************************************************************" << endl;

	system("pause");

	Player P(PlayerName, 0, 0, PlayerCharacter);

	AVL* Weapons = NULL;

	bool flag = true;

	int input;
	///Game Loop
	while (true)
	{
		int ID = rand() % 201;
		system("cls");
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		for (int i = 0; i < N; i++)
		{
			cout << "\t\t\t\t\t\t\t|";
			for (int j = 0; j < N; j++)
			{
				if (P.getX() == i && P.getY() == j)
				{
					cout << P.get() << " ";
				}
				else
				{
					cout << obj[i][j] << " ";
				}
			}
			cout << "|" << endl;
		}
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "C : clear path \nJ : jewel \nP : potion \nW : weapon \n% : Death point \n# : obstacle \n& : Dragon \n$ : Goblin \n@ : Werewolf \n* : Crystal(goal point)\n";
		P.dis();

		cout << endl;
		cout << "From Starting location ( Dijkstra )" << endl;
		DijkstrafindShortestPath(VALUES);
		cout << endl;
		cout << "From players location ( Floyd )" << endl;
		FloydfindShortestPath(VALUES, P.getX(), P.getY());
		cout << endl;
		input = _getch();
		switch (input) {
		case 72: // Up arrow key
			if (P.getX() - 1 != -1)
			{
				if (obj[P.getX() - 1][P.getY()] == '#')
				{
					//does nothing
				}
				else if (obj[P.getX() - 1][P.getY()] == 'J')
				{
					if (flag == true)
					{
						node n = node(1, "Jewel", score('J'), 100, score('J'));
						JewelIndex.push_back(100);
						Weapons = insert(n, Weapons);
						flag = false;
					}
					else
					{
						while (search(Weapons, ID) == true) {
							ID = rand() % 201;
						}
						node n = node(1, "Jewel", score('J'), ID, score('J'));
						JewelIndex.push_back(ID);
						Weapons = insert(n, Weapons);
					}

					P.set(P.getX() - 1, P.getY());
					int value = P.getScore() + score('J');
					P.setScore(value);
					obj[P.getX()].set(P.getY(), 'C');
				}
				else if (obj[P.getX() - 1][P.getY()] == 'P')
				{
					if (flag == true)
					{
						node n = node(2, "Potion", score('P'), 100, score('P'));
						Weapons = insert(n, Weapons);
						PotionIndex.push_back(100);
						flag = false;
					}
					else
					{
						while (search(Weapons, ID) == true) {
							ID = rand() % 201;
						}
						PotionIndex.push_back(ID);
						node n = node(2, "Potion", score('P'), ID, score('P'));
						Weapons = insert(n, Weapons);
					}
					P.set(P.getX() - 1, P.getY());
					int value = P.getScore() + score('P');
					P.setScore(value);
					obj[P.getX()].set(P.getY(), 'C');
				}
				else if (obj[P.getX() - 1][P.getY()] == 'W')
				{
					if (flag == true)
					{
						node n = node(3, "Weapon", score('W'), 100, score('W'));
						Weapons = insert(n, Weapons);
						WeaponIndex.push_back(100);
						flag = false;
					}
					else
					{
						while (search(Weapons, ID) == true) {
							ID = rand() % 201;
						}
						WeaponIndex.push_back(ID);
						node n = node(3, "Weapon", score('W'), ID, score('W'));
						Weapons = insert(n, Weapons);
					}
					P.set(P.getX() - 1, P.getY());
					int value = P.getScore() + score('W');
					P.setScore(value);
					obj[P.getX()].set(P.getY(), 'C');
				}
				else if (obj[P.getX() - 1][P.getY()] == '&')
				{
					if (search(Weapons, WeaponIndex[0]) == true)
					{
						Weapons = deleteNode(Weapons, WeaponIndex[0]);
						WeaponIndex.erase(0);
						obj[P.getX() - 1].set(P.getY(), 'C');
						int value = P.getScore() + score('&');
						P.setScore(value);
						cout << "\t\t\t\t\t\t\t|Dragon Defeated|" << endl;
						cin.get();
					}
					else
					{
						cout << "\t\t\t\t\t\t\t|Weapon Not in Inventory|" << endl;
						cin.get();
					}
				}
				else if (obj[P.getX() - 1][P.getY()] == '$')
				{
					if (search(Weapons, WeaponIndex[0]) == true)
					{
						Weapons = deleteNode(Weapons, PotionIndex[0]);
						PotionIndex.erase(0);
						obj[P.getX() - 1].set(P.getY(), 'C');
						int value = P.getScore() + score('$');
						P.setScore(value);
						cout << "\t\t\t\t\t\t\t|Goblin Defeated|" << endl;
						cin.get();
					}
					else
					{
						cout << "\t\t\t\t\t\t\t|Potion Not in Inventory|" << endl;
						cin.get();
					}
				}
				else if (obj[P.getX() - 1][P.getY()] == '@')
				{
					if (search(Weapons, WeaponIndex[0]) == true)
					{
						Weapons = deleteNode(Weapons, JewelIndex[0]);
						JewelIndex.erase(0);
						obj[P.getX() - 1].set(P.getY(), 'C');
						int value = P.getScore() + score('@');
						P.setScore(value);
						cout << "\t\t\t\t\t\t\t|WereWolf Defeated|" << endl;
						cin.get();
					}
					else
					{
						cout << "\t\t\t\t\t\t\t|Jewel Not in Inventory|" << endl;
						cin.get();
					}
				}
				else if (P.getX() - 1 != -1)
				{
					P.set(P.getX() - 1, P.getY());
				}
			}
			
			break;
		case 80: // Down arrow key
			if (obj[P.getX() + 1][P.getY()] == '#')
			{
				//does nothing
			}
			else if (obj[P.getX() + 1][P.getY()] == 'J')
			{
				if (flag == true)
				{
					node n = node(1, "Jewel", score('J'), 100, score('J'));
					Weapons = insert(n, Weapons);
					flag = false;
				}
				else
				{
					while (search(Weapons, ID) == true) {
						ID = rand() % 201;
					}
					node n = node(1, "Jewel", score('J'), ID, score('J'));
					Weapons = insert(n, Weapons);
				}

				P.set(P.getX() + 1, P.getY());
				int value = P.getScore() + score('J');
				P.setScore(value);
				obj[P.getX()].set(P.getY(), 'C');
			}
			else if (obj[P.getX() + 1][P.getY()] == 'P')
			{
				if (flag == true)
				{
					node n = node(2, "Potion", score('P'), 100, score('P'));
					Weapons = insert(n, Weapons);
					flag = false;
				}
				else
				{
					while (search(Weapons, ID) == true) {
						ID = rand() % 201;
					}
					node n = node(2, "Potion", score('P'), ID, score('P'));
					Weapons = insert(n, Weapons);
				}
				P.set(P.getX() + 1, P.getY());
				int value = P.getScore() + score('P');
				P.setScore(value);
				obj[P.getX()].set(P.getY(), 'C');
			}
			else if (obj[P.getX() + 1][P.getY()] == 'W')
			{
				if (flag == true)
				{
					node n = node(3, "Weapon", score('W'), 100, score('W'));
					Weapons = insert(n, Weapons);
					WeaponIndex.push_back(100);
					flag = false;
				}
				else
				{
					while (search(Weapons, ID) == true) {
						ID = rand() % 201;
					}
					WeaponIndex.push_back(ID);
					node n = node(3, "Weapon", score('W'), ID, score('W'));
					Weapons = insert(n, Weapons);
				}
				P.set(P.getX() + 1, P.getY());
				int value = P.getScore() + score('W');
				P.setScore(value);
				obj[P.getX()].set(P.getY(), 'C');
			}
			else if (obj[P.getX() + 1][P.getY()] == '&')
			{
				if (search(Weapons, WeaponIndex[0]) == true)
				{
					Weapons = deleteNode(Weapons, WeaponIndex[0]);
					WeaponIndex.erase(0);
					obj[P.getX() + 1].set(P.getY(), 'C');
					int value = P.getScore() + score('&');
					P.setScore(value);
					cout << "\t\t\t\t\t\t\t|Dragon Defeated|" << endl;
					cin.get();
				}
				else
				{
					cout << "\t\t\t\t\t\t\t|Weapon Not in Inventory|" << endl;
					cin.get();
				}
			}
			else if (obj[P.getX() + 1][P.getY()] == '$')
			{
				if (search(Weapons, WeaponIndex[0]) == true)
				{
					Weapons = deleteNode(Weapons, PotionIndex[0]);
					PotionIndex.erase(0);
					obj[P.getX() + 1].set(P.getY(), 'C');
					int value = P.getScore() + score('$');
					P.setScore(value);
					cout << "\t\t\t\t\t\t\t|Goblin Defeated|" << endl;
					cin.get();
				}
				else
				{
					cout << "\t\t\t\t\t\t\t|Potion Not in Inventory|" << endl;
					cin.get();
				}
			}
			else if (obj[P.getX() + 1][P.getY()] == '@')
			{
				if (search(Weapons, WeaponIndex[0]) == true)
				{
					Weapons = deleteNode(Weapons, JewelIndex[0]);
					JewelIndex.erase(0);
					obj[P.getX() + 1].set(P.getY(), 'C');
					int value = P.getScore() + score('@');
					P.setScore(value);
					cout << "\t\t\t\t\t\t\t|WereWolf Defeated|" << endl;
					cin.get();
				}
				else
				{
					cout << "\t\t\t\t\t\t\t|Jewel Not in Inventory|" << endl;
					cin.get();
				}
			}
			else if (P.getX() + 1 != N)
			{
				P.set(P.getX() + 1, P.getY());
			}
			break;
		case 75: // Left arrow key
			if (obj[P.getX()][P.getY() - 1] == '#')
			{
				//does nothing
			}
			else if (obj[P.getX()][P.getY() - 1] == 'J')
			{
				if (flag == true)
				{
					node n = node(1, "Jewel", score('J'), 100, score('J'));
					Weapons = insert(n, Weapons);
					flag = false;
				}
				else
				{
					while (search(Weapons, ID) == true) {
						ID = rand() % 201;
					}
					node n = node(1, "Jewel", score('J'), ID, score('J'));
					Weapons = insert(n, Weapons);
				}

				P.set(P.getX(), P.getY() - 1);
				int value = P.getScore() + score('J');
				P.setScore(value);
				obj[P.getX()].set(P.getY(), 'C');
			}
			else if (obj[P.getX()][P.getY() - 1] == 'P')
			{
				if (flag == true)
				{
					node n = node(2, "Potion", score('P'), 100, score('P'));
					Weapons = insert(n, Weapons);
					flag = false;
				}
				else
				{
					while (search(Weapons, ID) == true) {
						ID = rand() % 201;
					}
					node n = node(2, "Potion", score('P'), ID, score('P'));
					Weapons = insert(n, Weapons);
				}
				P.set(P.getX(), P.getY() - 1);
				int value = P.getScore() + score('P');
				P.setScore(value);
				obj[P.getX()].set(P.getY(), 'C');
			}
			else if (obj[P.getX()][P.getY() - 1] == 'W')
			{
				if (flag == true)
				{
					node n = node(3, "Weapon", score('W'), 100, score('W'));
					WeaponIndex.push_back(100);
					Weapons = insert(n, Weapons);
					flag = false;
				}
				else
				{
					while (search(Weapons, ID) == true) {
						ID = rand() % 201;
					}
					WeaponIndex.push_back(ID);
					node n = node(3, "Weapon", score('W'), ID, score('W'));
					Weapons = insert(n, Weapons);
				}
				P.set(P.getX(), P.getY() - 1);
				int value = P.getScore() + score('W');
				P.setScore(value);;
				obj[P.getX()].set(P.getY(), 'C');
			}
			else if (obj[P.getX()][P.getY() - 1] == '&')
			{
				if (search(Weapons, WeaponIndex[0]) == true)
				{
					Weapons = deleteNode(Weapons, WeaponIndex[0]);
					WeaponIndex.erase(0);
					obj[P.getX()].set(P.getY() - 1, 'C');
					int value = P.getScore() + score('&');
					P.setScore(value);
					cout << "\t\t\t\t\t\t\t|Dragon Defeated|" << endl;
					cin.get();
				}
				else
				{
					cout << "\t\t\t\t\t\t\t|Weapon Not in Inventory|" << endl;
					cin.get();
				}
			}
			else if (obj[P.getX()][P.getY() - 1] == '$')
			{
				if (search(Weapons, WeaponIndex[0]) == true)
				{
					Weapons = deleteNode(Weapons, PotionIndex[0]);
					PotionIndex.erase(0);
					obj[P.getX()].set(P.getY() - 1, 'C');
					int value = P.getScore() + score('$');
					P.setScore(value);
					cout << "\t\t\t\t\t\t\t|Goblin Defeated|" << endl;
					cin.get();
				}
				else
				{
					cout << "\t\t\t\t\t\t\t|Potion Not in Inventory|" << endl;
					cin.get();
				}
			}
			else if (obj[P.getX()][P.getY() - 1] == '@')
			{
				if (search(Weapons, WeaponIndex[0]) == true)
				{
					Weapons = deleteNode(Weapons, JewelIndex[0]);
					JewelIndex.erase(0);
					obj[P.getX()].set(P.getY() - 1, 'C');
					int value = P.getScore() + score('@');
					P.setScore(value);
					cout << "\t\t\t\t\t\t\t|WereWolf Defeated|" << endl;
					cin.get();
				}
				else
				{
					cout << "\t\t\t\t\t\t\t|Jewel Not in Inventory|" << endl;
					cin.get();
				}
			}
			else if (P.getY() - 1 != -1)
				P.set(P.getX(), P.getY() - 1);

			break;
		case 77: // Right arrow key
			if (obj[P.getX()][P.getY() + 1] == '#')
			{
				//does nothing
			}
			else if (obj[P.getX()][P.getY() + 1] == 'J')
			{
				if (flag == true)
				{
					node n = node(1, "Jewel", score('J'), 100, score('J'));
					Weapons = insert(n, Weapons);
					flag = false;
				}
				else
				{
					while (search(Weapons, ID) == true) {
						ID = rand() % 201;
					}
					node n = node(1, "Jewel", score('J'), ID, score('J'));
					Weapons = insert(n, Weapons);
				}

				P.set(P.getX(), P.getY() + 1);

				int value = P.getScore() + score('J');
				P.setScore(value);
				obj[P.getX()].set(P.getY(), 'C');
			}
			else if (obj[P.getX()][P.getY() + 1] == 'P')
			{
				if (flag == true)
				{
					node n = node(2, "Potion", score('P'), 100, score('P'));
					Weapons = insert(n, Weapons);
					flag = false;
				}
				else
				{
					while (search(Weapons, ID) == true) {
						ID = rand() % 201;
					}
					node n = node(2, "Potion", score('P'), ID, score('P'));
					Weapons = insert(n, Weapons);
				}
				P.set(P.getX(), P.getY() + 1);
				int value = P.getScore() + score('P');
				P.setScore(value);
				obj[P.getX()].set(P.getY(), 'C');
			}
			else if (obj[P.getX()][P.getY() + 1] == 'W')
			{
				if (flag == true)
				{
					node n = node(3, "Weapon", score('W'), 100, score('W'));
					Weapons = insert(n, Weapons);
					WeaponIndex.push_back(100);
					flag = false;
				}
				else
				{
					while (search(Weapons, ID) == true) {
						ID = rand() % 201;
					}
					WeaponIndex.push_back(ID);
					node n = node(3, "Weapon", score('W'), ID, score('W'));
					Weapons = insert(n, Weapons);
				}
				P.set(P.getX(), P.getY() + 1);
				int value = P.getScore() + score('W');
				P.setScore(value);
				obj[P.getX()].set(P.getY(), 'C');
			}
			else if (obj[P.getX()][P.getY() + 1] == '&')
			{
				if (search(Weapons, WeaponIndex[0]) == true)
				{
					Weapons = deleteNode(Weapons, WeaponIndex[0]);
					WeaponIndex.erase(0);
					obj[P.getX()].set(P.getY() + 1, 'C');
					int value = P.getScore() + score('&');
					P.setScore(value);
					cout << "\t\t\t\t\t\t\t|Dragon Defeated|" << endl;
					cin.get();
				}
				else
				{
					cout << "\t\t\t\t\t\t\t|Weapon Not in Inventory|" << endl;
					cin.get();
				}
			}
			else if (obj[P.getX()][P.getY() + 1] == '$')
			{
				if (search(Weapons, WeaponIndex[0]) == true)
				{
					Weapons = deleteNode(Weapons, PotionIndex[0]);
					PotionIndex.erase(0);
					obj[P.getX()].set(P.getY() + 1, 'C');
					int value = P.getScore() + score('$');
					P.setScore(value);
					cout << "\t\t\t\t\t\t\t|Goblin Defeated|" << endl;
					cin.get();
				}
				else
				{
					cout << "\t\t\t\t\t\t\t|Potion Not in Inventory|" << endl;
					cin.get();
				}
			}
			else if (obj[P.getX()][P.getY() + 1] == '@')
			{
				if (search(Weapons, WeaponIndex[0]) == true)
				{
					Weapons = deleteNode(Weapons, JewelIndex[0]);
					JewelIndex.erase(0);
					obj[P.getX()].set(P.getY() + 1, 'C');
					int value = P.getScore() + score('@');
					P.setScore(value);
					cout << "\t\t\t\t\t\t\t|WereWolf Defeated|" << endl;
					cin.get();
				}
				else
				{
					cout << "\t\t\t\t\t\t\t|Jewel Not in Inventory|" << endl;
					cin.get();
				}
			}
			else if (P.getY() + 1 != N)
				P.set(P.getX(), P.getY() + 1);

			break;
		case 27:
			exit(1);
			break;
		}
		if (obj[P.getX()][P.getY()] == '*')
		{
			system("cls");
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "\t\t\t*************************************************GAME ENDED*************************************************" << endl;
			cout << "\t\t\t\t\t";
			P.dis();
			exit(1);
		}


		Sleep(50);
	}

}
