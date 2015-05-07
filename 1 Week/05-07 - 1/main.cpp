#include <iostream>

using namespace std;

class node
{
public:
	const char* data;
	node* next;

	node(void){};
	~node(void){};
};

node* head = NULL;
node* current = NULL;

node* insert(node* address, const char* data);

void add(const char* data);
void add_front(const char* data);
void output(void);
void reverse();

void a(node* a)
{
	a->next = new node;
	a->next->data = "sdw";
}

int main(void)
{
	add("개똥이");
	add("말숙이");
	add("장남이");
	add("게이");
	add("트레스젠더");
	add("호모");
	add("크로마뇽인");

	add_front("123123");

	reverse();
	output();

	return 0;
}

node* insert(node* address, const char* data)
{
	//첫번째 데이터삽입 또는 리스트의 마지막 데이터이면..
	if (address == NULL)
	{
		address = new node;
		address->data = data;
		address->next = NULL;
		if (head == NULL) head = address;
	}
	else
	{
		address->next = insert(address->next, data);
	} 

	return address;
}

void add(const char* data)
{
	current = insert(current, data);
}

void add_front(const char* data)
{
	current = new node;
	current->next = head;
	head = current;

	current->data = data;
}

void output(void)
{
	current = head;
	while (current != NULL)
	{
		cout << current->data << endl;
		current = current->next;
	}
}
node* _reverse(node* cu)//재귀 호출로 싱글링크드리스트 뒤집기.
{
	current = cu->next;
	head = current;
	if (current->next != NULL)
	{
		_reverse(current);
	}
	cu->next = NULL;
	current->next = cu;
	
	return cu;
}

void reverse()
{
	_reverse(head);
}