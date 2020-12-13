#pragma once
#include <iostream>
using namespace std;


struct Date;
class Data;
struct Node;
typedef Node* TList;

void init(TList& head); //инициалиция
bool isEmpty(TList head); //проверка на пустоту 
void addToHead(TList& head, Data elem); //добавление в начало
void addAfterNode(TList pNode, Data elem); //добавление в середину 
void deleteFromHead(TList& head); //удаление с начала списка 
void deleteAfterNode(TList pNode); //удаление после заданного элемента 
void clear(TList& head); //очистка списка 
void printList(TList head); // печать списка

bool search(string& s, string& c);
void findName(TList& head);
bool fromFileToList(TList& head);