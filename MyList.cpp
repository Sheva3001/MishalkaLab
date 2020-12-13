using namespace std;
#include "MyList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

class Data { // Класс, содержащий поля (Имя, автор и т.д.)
public:
	string author;
	string name;
	int year;
	int count;
	string spec;
	friend ifstream& operator>> (ifstream& inf, Data& data) { // Перегруженный оператор для считывания
		Data tmp;
		Data pNode = tmp;
		if (inf.peek() != -1) {
			inf >> tmp.author;
			inf >> tmp.name;
			inf >> tmp.year;
			inf >> tmp.count;
			inf >> tmp.spec;
		}
		else
			return inf;
		data = tmp;
		return inf;
	}
};

struct Node // Элемент списка, содержит класс Data с полями и ссылку на следующий элемент
{
	Data data;
	Node* next;
};

typedef Node* TList;

void init(TList& head)
{
	head = NULL;
}

bool isEmpty(TList head)
{
	return head == NULL;
}

void addToHead(TList& head, Data elem)
{
	TList p = new Node;
	p->data = elem;
	p->next = head;
	head = p;
}

void addAfterNode(TList pNode, Data elem)
{
	TList p = new Node;
	p->data = elem;
	p->next = pNode->next;
	pNode->next = p;
}

void deleteFromHead(TList& head)
{
	TList p = head;
	head = head->next;
	p->next = 0;
	delete p;
}

void deleteAfterNode(TList pNode)
{
	if (pNode != 0)
	{
		TList p = pNode->next;
		pNode->next = p->next;
		p->next = 0;
		delete p;
	}
}

void clear(TList& head)
{
	while (!isEmpty(head))
		deleteFromHead(head);
	delete head;
}

void printList(TList head)
{
	TList p = head;
	while (p != NULL)
	{
		cout << p->data.author << endl;
		cout << p->data.name << endl;
		cout << p->data.year << endl;
		cout << p->data.count << endl;
		cout << p->data.spec << endl;
		p = p->next;
	}
}

bool search(string& s, string& c) { // Получает две строки (в первой ищет вторую) если она там есть, возвращает 1, иначе 0
	bool check = 0; // По этой переменной функция понимает, найдена ли строка
	for (int i = 0; i <= s.length() - c.length(); i++) { // Проходимся по строке, в которой ищем, до (длина 1 строки минус длина 2) так как дальше нет смысла искать, вторая строка там не поместится
		if (tolower(s[i]) == tolower(c[0])) { // tolower преобразует символ в нижний регистр (из Н в н), далее мы их сравниваем. Если символ строки = 0-му символу 2 строки, то он может быть началом слова, далее это проверяется циклом
			check = 1; // Присваиваем 1, если остальные символы не совпадут, сменится обратно на 0
			for (int j = 1; j < c.length(); j++) { // Проходимся, попарно сравнивая символы
				if (tolower(s[i + j]) != tolower(c[0 + j]))
					check *= 0;
			}
		}
	}
	return check; // Возвращаем результат
}

void findName(TList& head) {
	TList pNode = head; string temp; // Стравим указатель pNode на начало списка и создаем строку
	cout << "Введите слово для поиска:" << endl;
	cin >> temp; // В строку помещаем слово, которое будем искать
	while (pNode != NULL) { // Проходимся по списку
		if (search(pNode->data.name, temp)) { // Сравниваем имя, для каждого элемента списка, если функция search найдет temp в имени, выводим инфу об элементе списка
			cout << pNode->data.author << endl;
			cout << pNode->data.name << endl;
			cout << pNode->data.year << endl;
			cout << pNode->data.count << endl;
			cout << pNode->data.spec << endl;
			cout << "-------------------------" << endl;
		}
		pNode = pNode->next; // Переходим к следующему элементу
	}
}

bool fromFileToList(TList& head) { // Функция, которая считывает из файла и сортирует список
	ifstream inf("List.txt");
	if (!inf.is_open()) {
		cout << "Не удалось считать файл";
		return 0;
	}
	init(head); // Инициализируем голову списка
	TList tail = head; // Ставим указатель на хвот (сейчас в списке 1 элемент, поэтому голова и хвост совпадают)
	TList pNode; // Создаем указатель pNode
	for (Data current; inf >> current;) { // Пока считывается из файла
		if (isEmpty(head)) // Если список пуст, добавляем в голову
		{
			addToHead(head, current);
			tail = head;
		}
		else if (head == tail) { // Если один элемент (head==tail)
			if (current.name >= head->data.name) { // Если имя, которое считали >= имени элемента списка, добавляем после головы
				addAfterNode(head, current);
			}
			else
				addToHead(head, current); // Иначе в голову
			tail = head->next; // Хвост перемещаем на следующий после головы элемент
		}
		else // Если больше 1 элемента
		{
			pNode = head; // Ставим указатель на голову и проходимся циклом до конца, далее условиями мы ищем для него место и вставляем
			while (pNode->next != NULL) {
				if ((current.name < pNode->data.name) && (pNode == head)) {
					addToHead(head, current);
					break;
				}
				if ((current.name >= pNode->data.name) && (current.name <= pNode->next->data.name)) {
					addAfterNode(pNode, current);
					break;
				}
				if ((current.name > pNode->next->data.name) && (pNode->next == tail)) {
					addAfterNode(tail, current);
					tail = tail->next;
					break;
				}
				pNode = pNode->next;
			}
		}
	}
	return 1;
}