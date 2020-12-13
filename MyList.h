#pragma once
#include <iostream>
using namespace std;


struct Date;
class Data;
struct Node;
typedef Node* TList;

void init(TList& head); //�����������
bool isEmpty(TList head); //�������� �� ������� 
void addToHead(TList& head, Data elem); //���������� � ������
void addAfterNode(TList pNode, Data elem); //���������� � �������� 
void deleteFromHead(TList& head); //�������� � ������ ������ 
void deleteAfterNode(TList pNode); //�������� ����� ��������� �������� 
void clear(TList& head); //������� ������ 
void printList(TList head); // ������ ������

bool search(string& s, string& c);
void findName(TList& head);
bool fromFileToList(TList& head);