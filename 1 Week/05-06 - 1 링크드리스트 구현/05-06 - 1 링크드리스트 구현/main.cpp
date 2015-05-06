#include <iostream>

using namespace std;

//template < typename t >
struct Node{
	int element;
	Node *prev;
	Node *next;
};

Node* list;
int size;

void initializeList();
void insert(int index, int value);
int at(int index);
void erase(int index);
void pushBack(int value);
int popBack();
Node* getNode(int index);
int getSize();

void main()
{
	initializeList();
	//return;
	pushBack(1);
	pushBack(2);
	pushBack(3);
	pushBack(4);
	pushBack(5);
	pushBack(6);
	pushBack(7);
	pushBack(8);
	pushBack(9);
	pushBack(10);
	insert(5, 100);
	erase(7);
	
	cout << "ÆË! : " << popBack() << endl;

	for (int i = 0; i < getSize(); i++)
	{
		cout << at(i) << endl;
	}

	cout << "»çÀÌÁî´Â ? : " << getSize() << endl;
}

int getSize()
{
	return size;
}

void initializeList()
{
	list = new Node;
	list->prev = NULL;
	list->next = NULL;
	list->element = 0;
	size = 0;
}

void insert(int index, int value)
{
	Node* indexNode = getNode(index);
	Node* prevNode = indexNode->prev;
	Node* newNode = new Node;
	
	indexNode->prev = newNode;
	prevNode->next = newNode;

	newNode->prev = prevNode;
	newNode->next = indexNode;

	newNode->element = value;

	size += 1;
}

int at(int index)
{
	Node *node = getNode(index);
	return node->element;
}

void erase(int index)
{
	Node *node = getNode(index);
	Node *prev = node->prev;
	Node *next = node->next;

	prev->next = next;
	next->prev = prev;

	size -= 1;

	delete node;
}

void pushBack(int value)
{
	Node *node = getNode(size - 1);
	Node *newNode = new Node;
	node->next = newNode;
	newNode->prev = node;
	newNode->next = NULL;
	newNode->element = value;

	size += 1;
}

int popBack()
{
	Node *node = getNode(size - 1);
	int value = node->element;

	Node *prev = node->prev;
	prev->next = NULL;
		
	size -= 1;

	delete node;
	
	return value;
}

Node* getNode(int index)
{
	Node *node = list;

	if (index > size)
	{
		return NULL;
	}

	for (int i = 0; i < index + 1; i++)
	{
		node = node->next;
	}

	return node;
}