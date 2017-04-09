// INFO450FavoriteThing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int READERROR = 100;
const int WRITEERROR = 200;
const int ARRAYSIZE = 10;

class Diamond {
	string shape;
	string carat;
	string cut;
	string color;
	string clarity;
	string price;
public:
	Diamond();
	Diamond(string, string, string, string,string, string);
	void CaptureNewDiamond();
	void ShowDiamond();
	int SaveDiamondToFile(ofstream &outfile);

};

class DiamondList {
	string defaultFilePath = "C:\\Users\\srob300\\Documents\\info450\\favoriteThing.txt";
	string filePath = defaultFilePath;
	Diamond **dList;
	int numrecords;
	int listsize;
	int ReallocateArray();
public:
	DiamondList();
	~DiamondList();
	void GetUserInput();
	void GetFilePath();
	void ShowDiamondList();
	string GetFileString();
	int SaveDiamondList(string filename);
	int ReadDiamondList(string filename);
};

Diamond::Diamond() {
	shape = "";
	carat = "";
	cut = "";
	color = "";
	clarity = "";
	price = "";
}

Diamond::Diamond(string shapeIn, string caratIn, string cutIn, string colorIn, string clarityIn, string priceIn) {
	shape = shapeIn;
	carat = caratIn;
	cut = cutIn;
	color = colorIn;
	clarity = clarityIn;
	price = priceIn;
}

void Diamond::CaptureNewDiamond() {
	cout << "Shape?";
	getline(cin, shape);
	cout << "Carat Weight?";
	getline(cin, carat);
	cout << "Cut?";
	getline(cin, cut);
	cout << "Color?";
	getline(cin, color);
	cout << "Clarity?";
	getline(cin, clarity);
	cout << "Price?";
	getline(cin, price);

}

void Diamond::ShowDiamond() {
	cout << "----------------------------" << endl;
	cout << "Shape: " << shape << endl;
	cout << "Carat: " << carat << endl;
	cout << "Cut: " << cut << endl;
	cout << "Color: " << color << endl; 
	cout << "Clarity: " << clarity << endl;
	cout << "Price: " << price << endl;
	cout << "----------------------------" << endl;
}

int Diamond::SaveDiamondToFile(ofstream& outfile) {
	if (outfile.is_open()) {
		outfile << shape << "|" << carat << "|" << cut << "|" << color << "|" << clarity << "|" << price << endl;
		return 0;
	}
	else {
		return WRITEERROR;
	}
}

DiamondList::DiamondList() {
	dList = new Diamond*[ARRAYSIZE];
	numrecords = 0;
	listsize = ARRAYSIZE;
}

DiamondList::~DiamondList() {
	for (int i = 0; i < numrecords; i++) {
		delete dList[i];
	}
	delete[]dList;
}

int DiamondList::ReallocateArray() {
	int newSize = ARRAYSIZE + listsize;
	Diamond **temp;
	temp = new Diamond*[newSize];
	listsize = newSize;
	for (int i = 0; i < numrecords; i++) {
		temp[i] = dList[i];
	}
	delete[]dList;
	dList = temp;
	return 0;
}

string DiamondList::GetFileString() {
	return filePath;
}

void DiamondList::GetFilePath() {
	string fileAnswer = "n";
	cout << "Would you like to enter a file path (Y/N)?" << endl;
	getline(cin, fileAnswer);
	if (fileAnswer == "Y" || fileAnswer == "y") {
		cout << "Please enter the path ->" << endl;
		getline(cin, filePath);
	}
}

void DiamondList::GetUserInput() {
	
	string answer = "Y";
	cout << "enter item Y/N?" << endl;
	getline(cin, answer);
	while (answer == "Y" || answer == "y") {
		dList[numrecords] = new Diamond();
		dList[numrecords]->CaptureNewDiamond();
		numrecords++;
		cout << "enter item Y/N?" << endl;
		getline(cin, answer);
	}
}

void DiamondList::ShowDiamondList() {
	cout << "----------------------------" << endl;
	cout << "Diamonds" << endl;
	cout << "----------------------------" << endl;
	for(int i = 0; i < numrecords; i++)
		dList[i]->ShowDiamond();
}


int DiamondList::SaveDiamondList(string filename) {
	ofstream output(filename, ios::trunc);
	if (output) {
		for (int i = 0; i < numrecords; i++) {
			dList[i]->SaveDiamondToFile(output);
		}
		output.close();
		return 0;
	}
	else {
		return WRITEERROR;
	}
	return 0;
}

int DiamondList::ReadDiamondList(string filename) {
	string iShape, iCarat, iCut, iColor, iClarity,iPrice;
	ifstream infile(filename, ios::in);
	if (!infile) {
		cout << "File cant open for reading." << endl;
		return READERROR;
	}

	while (!infile.eof()) {
		if (numrecords == listsize) {
			ReallocateArray();
		}
		getline(infile, iShape, '|');
		if (!iShape.empty()) {
			getline(infile, iCarat, '|');
			getline(infile, iCut, '|');
			getline(infile, iColor, '|');
			getline(infile, iClarity, '|');
			getline(infile, iPrice);
			dList[numrecords] = new Diamond(iShape, iCarat,iCut,iColor,iClarity,iPrice);
			numrecords++;
		}

	}
	return 0;
}

int main()
{
	DiamondList myDiaList;
	int err;
	string answer;
	myDiaList.GetFilePath();
	err = myDiaList.ReadDiamondList(myDiaList.GetFileString());
	if (err)
	{
		cout << "Cannot read inventory - continue creating new list? Y/N -->";
		getline(cin, answer);
		if (answer != "Y" && answer != "y")
		{
			return 1;
		}
	}
	myDiaList.GetUserInput();
	myDiaList.SaveDiamondList(myDiaList.GetFileString());
	myDiaList.ShowDiamondList();
    return 0;
}

