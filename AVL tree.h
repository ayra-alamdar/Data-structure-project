#pragma once
#include <iostream>
#include <string>
using namespace std;

struct node {
	string Weapon;
	int type;
	int number;

	int id;				  //generated randomly
	int reward_score;		 //score of a particular reward you obtained
	int count;			//to avoid duplicate id nodes (maintain count of the id)

	node(int i = 0, string n = "", int num = 0, int ID = 0, int Rs = 0) {
		type = i;
		Weapon = n;
		number = num;
		id = ID;
		reward_score = Rs;
	}
};

ostream& operator<<(ostream& out, const node& c)
{
	cout << "---------------------------NUMBER " << c.number << "--------------------------" << endl;
	out << "Weapon " << c.Weapon << endl;
	out << "Type " << c.type << endl;
	out << "ID : " << c.id << endl;
	return out;
}

struct AVL
{
	node data;
	int height;
	AVL* left;
	AVL* right;

	AVL(node set)
	{
		this->data = set;
		this->height = 1;
		this->left = this->right = NULL;
	}
};

int height(AVL* p)
{
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		return p->height;
	}
}

AVL* successor(AVL* root)
{
	AVL* temp = root;
	while (temp->left != NULL && temp)
	{
		temp = temp->left;
	}
	return temp;
}

int Balance(AVL* root)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		return (height(root->left)) - (height(root->right));
	}
}

AVL* RR(AVL* root)
{
	if (root == nullptr) {
		return nullptr;
	}

	AVL* x = root->left;
	if (x == nullptr) {
		return root;
	}

	AVL* y = x->right;

	x->right = root;
	root->left = y;

	root->height = max(height(root->left), height(root->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}


AVL* LR(AVL* root)
{
	if (root == nullptr) {
		return nullptr;
	}

	AVL* x = root->right;
	if (x == nullptr) {
		return root;
	}

	AVL* y = x->left;

	x->left = root;
	root->right = y;

	root->height = max(height(root->left), height(root->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}


AVL* insert(node val, AVL* root)
{
	if (root == NULL)
	{
		return new AVL(val);
	}
	if (val.id < root->data.id)
	{
		root->left = insert(val, root->left);
	}
	else if (val.id > root->data.id)
	{
		root->right = insert(val, root->right);
	}
	else
	{
		return root;
	}

	root->height = max(height(root->left), height(root->right)) + 1;

	int balance_Factor = Balance(root);

	// Left case
	if (balance_Factor > 1)
	{
		if (val.id < root->left->data.id)
		{
			return RR(root);
		}
		else
		{
			root->left = LR(root->left);
			return RR(root);
		}
	}
	// Right case
	if (balance_Factor < 1)
	{
		if (val.id > root->right->data.id)
		{
			return LR(root);
		}
		else
		{
			root->right = RR(root->right);
			return LR(root);
		}
	}

	return root;
}

AVL* deleteNode(AVL* root, int weapon) {
	if (root == NULL) {
		return root;
	}if (weapon < root->data.id) {
		root->left = deleteNode(root->left, weapon);
	}
	else if (weapon > root->data.id) {
		root->right = deleteNode(root->right, weapon);
	}
	else {
		if ((root->left == NULL) || (root->right == NULL)) {
			AVL* temp = root->left ? root->left : root->right;

			if (temp == NULL) {
				temp = root;
				root = NULL;
			}
			else {
				*root = *temp;
			}

			delete temp;
		}
		else {
			AVL* temp = successor(root->right);
			root->data = temp->data;
			root->right = deleteNode(root->right, temp->data.id);
		}
	}
	if (root == NULL) {
		return root;
	}
	root->height = max(height(root->left), height(root->right)) + 1;
	int balance_Factor = Balance(root);
	// Left case
	if (balance_Factor > 1) {
		if (Balance(root->left) >= 0) {
			root = RR(root);
		}
		else {
			root->left = LR(root->left);
			root = RR(root);
		}
	}
	// Right case
	if (balance_Factor < -1) {
		if (Balance(root->right) <= 0) {
			root = LR(root);
		}
		else {
			root->right = RR(root->right);
			root = LR(root);
		}
	}
	return root;
}

bool search(AVL* root, int weapon) {
	if (root == NULL) {
		return false;
	}if (root->data.id == weapon) {
		return true;
	}

	if (root->data.id < weapon) {
		return search(root->right, weapon);
	}

	return search(root->left, weapon);
}

void PreOrderTransversal(AVL* p)
{
	if (p != NULL)
	{
		cout << p->data << ' ';
		PreOrderTransversal(p->left);
		PreOrderTransversal(p->right);
	}
}

void PostOrderTransversal(AVL* p)
{
	if (p != NULL)
	{
		PostOrderTransversal(p->left);
		PostOrderTransversal(p->right);
		cout << p->data << ' ';
	}
}

void InOrderTransversal(AVL* p)
{
	if (p != NULL)
	{
		InOrderTransversal(p->left);
		cout << p->data << ' ';
		InOrderTransversal(p->right);
	}
}


