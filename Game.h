#pragma once

/// <summary>
///		C : clear path
///		J : jewel
///		P : potion
///		W : weapon
///		% : Death point
///		# : obstacle
///		& : Dragon
///		$ : Goblin
///		@ : Werewolf
///		* : Crystal(goal point)
/// </summary>
/// <returns></returns>
int score(char a)
{
	switch (a)
	{
	case 'C':			//Clear
		return 0;
	case 'J':			//Jewel
		return 50;
	case 'P':			//Potion
		return 70;
	case 'W':			//Werewolf
		return 30;
	case '%':			//game ends
		return INT_MIN;
	case '#':			//No move
		return INT_MIN;
	case '&':			//lose jewel
		return -50;
	case '$':			//lose potion
		return -70;
	case '@':			//lose weapon
		return -30;
	case '*':			//Win Game
		return INT_MAX;
	default:
		return 0;
	}
}

class Player
{
public:
	Player(string na="", int i = 0, int j = 0, char a = '>', int s = 0);
	void set(int i, int j);
	int getX();
	int getY();
	char get();
	int getScore();
	void setScore(int val);
	void dis();
	~Player();

private:
	string Name;
	int posx = 0;
	int posy = 0;
	char player_skin;
	int Score;
};

Player::Player(string na, int i, int j, char a, int s)
{
	Name = na;
	posx = i;
	posy = j;
	player_skin = a;
	Score = 0;
}

void Player::set(int i, int j)
{
	posx = i;
	posy = j;
}

int Player::getX()
{
	return posx;
}

int Player::getY()
{
	return posy;
}

int Player::getScore()
{
	return Score;
}

void Player::setScore(int val)
{
	Score += val;
}

char Player::get()
{
	return player_skin;
}

void Player::dis()
{
	cout << "Name : " << Name << "\tScore : " << Score << endl;
}

Player::~Player()
{
	posx = posy = 0;
}