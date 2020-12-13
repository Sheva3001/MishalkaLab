#include "MyList.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;



int main() {
	setlocale(LC_ALL, "Russian");
	TList books;
	fromFileToList(books);
	findName(books);

	return 0;
}

