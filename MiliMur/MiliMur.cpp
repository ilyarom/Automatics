// MiliMur.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "Automatic.h"
#include "Minifier.h"


using namespace std;


int main()
{
	CAutomatic automatic;
	ifstream input("input.txt");
	string format;
	getline(input, format);
	if (format == "Moore") {
		automatic.GetValuesFromFile(input, Format::Moore);
	}
	else if (format == "Mili") {
		automatic.GetValuesFromFile(input, Format::Mili);
	}
	else {
		cout << "Invalid format\n";
		return 1;
	}

	automatic.Minify();
    return 0;
}

