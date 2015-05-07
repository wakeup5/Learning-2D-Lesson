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
	add("������");
	add("������");
	add("�峲��");
	add("����");
	add("Ʈ��������");
	add("ȣ��");
	add("ũ�θ�����");

	add_front("123123");

	reverse();
	output();

	return 0;
}

node* insert(node* address, const char* data)
{
	//ù��° �����ͻ��� �Ǵ� ����Ʈ�� ������ �������̸�..
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
node* _reverse(node* cu)//��� ȣ��� �̱۸�ũ�帮��Ʈ ������.
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