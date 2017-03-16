///////////////////////////////////////////////////////////
//  Report.cpp
//  Implementation of the Class Report
//  Created on:  11/15/2016
//  Author: Robert T
///////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "Report.h"

using namespace std;

Report::Report(){

}

Report::~Report(){

}

void Report::inventoryList(){
	listBooks();
	system("pause");
}

void Report::inventoryWholesaleValue(){
	cout << setw(105) << "Listed by Wholesale Value" << endl << endl;

	cout << setw(15) << left << "ISBN";
	cout << setw(70) << left << "Title";
	cout << setw(25) << left << "Author";
	cout << setw(25) << left << "Publisher";
	cout << setw(15) << left << "Date added";
	cout << setw(15) << left << "Quantity";
	cout << setw(25) << left << "Wholesale cost";
	cout << setw(25) << left << "Retail price";
	cout << setw(25) << left << "Wholesale value";
	cout << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;


	for (int i = 0; i < bookRow; i++){

		cout << setw(15) << left << getISBN(i); // ISBN
		cout << setw(70) << left << getTitle(i); // Title
		cout << setw(25) << left << getAuthor(i); // Author
		cout << setw(25) << left << getPublisher(i); // Publisher
		cout << setw(15) << left << getDateAdded(i); // Date added
		cout << setw(10) << right << getQuantity(i); // Quantity
		cout << setw(18) << right << getWhosleCost(i); // Wholesale cost
		cout << setw(18) << right << getRetailPrice(i); // Retail price
		cout << setw(22) << right << stod(getQuantity(i)) * stod(getWhosleCost(i)); // Wholesale value
		cout << endl;
	}// end for

	system("pause");
}


void Report::inventoryRetailValue(){
	cout << setw(105) << "Listed by Retail Value" << endl << endl;

	cout << setw(15) << left << "ISBN";
	cout << setw(70) << left << "Title";
	cout << setw(25) << left << "Author";
	cout << setw(25) << left << "Publisher";
	cout << setw(15) << left << "Date added";
	cout << setw(15) << left << "Quantity";
	cout << setw(25) << left << "Wholesale cost";
	cout << setw(25) << left << "Retail price";
	cout << setw(25) << left << "Retail value";
	cout << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;


	for (int i = 0; i < bookRow; i++){

		cout << setw(15) << left << getISBN(i); // ISBN
		cout << setw(70) << left << getTitle(i); // Title
		cout << setw(25) << left << getAuthor(i); // Author
		cout << setw(25) << left << getPublisher(i); // Publisher
		cout << setw(15) << left << getDateAdded(i); // Date added
		cout << setw(10) << right << getQuantity(i); // Quantity
		cout << setw(18) << right << getWhosleCost(i); // Wholesale cost
		cout << setw(18) << right << getRetailPrice(i); // Retail price
		cout << setw(25) << right << stod(getRetailPrice(i)) * stod(getQuantity(i)); // Retail value
		cout << endl;
	}// end for

	system("pause");
}


void Report::listByQuantity(){
	selectionSortByNumber(getBookArray(), 5);

	cout << setw(105) << "Listed by Quantity" << endl << endl;
	listBooks();
	system("pause");
}


void Report::listByCost(){
	selectionSortByNumber(getBookArray(), 6);

	cout << setw(105) << "Listed by Cost" << endl << endl;
	listBooks();
	system("pause");
}


void Report::listByAge(){
	selectionSortByNumber(getBookArray(), 4);

	cout << setw(105) << "Listed by Age" << endl << endl;
	listBooks();
	system("pause");
}


void Report::menu(){
	int choice;
	bool exit = false;

	do
	{
		system("cls");
		cout << "*****************************************" << endl;
		cout << "         Secrendipity Booksellers        " << endl;
		cout << "                   Reports               " << endl << endl;
		cout << "1. Inventory Listing" << endl;
		cout << "2. Inventory Wholesale Value" << endl;
		cout << "3. Inventory Retail Value" << endl;
		cout << "4. Inventory by Quantity" << endl;
		cout << "5. Inventory by Cost " << endl;
		cout << "6. Inventory by Age " << endl;
		cout << "7. Return to Main Menu " << endl;
		cout << "*****************************************" << endl << endl;

		cout << "Enter Your Choice:";
		while (!(cin >> choice))
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid choice, please enter a whole number:";
		}

		if (choice == 1){// Inventory Listing
			inventoryList();
		}
		else if (choice == 2) // Inventory Wholesale Value
		{
			inventoryWholesaleValue();
		}
		else if (choice == 3) // Inventory Retail Value
		{
			inventoryRetailValue();
		}
		else if (choice == 4) // Inventory by Quantity
		{
			listByQuantity();
		}
		else if (choice == 5) // Inventory by Cost
		{
			listByCost();
		}
		else if (choice == 6) // Inventory by Age
		{
			//cout << books[1][4] << "=" << date2int(books[1][4]) << endl;
			listByAge();
		}
		else
		{
			exit = true;
		}
	} while (exit != true);

}


void Report::selectionSortByNumber(string** array, int column)
{
	int minIndex, arrLength = bookRow;
	string* minValue;

	for (int startScan = 0; startScan < arrLength; startScan++)
	{
		minIndex = startScan;
		minValue = array[startScan];

		// Loop from startScan + 1
		for (int index = startScan + 1; index < arrLength; index++)
		{
			if (column==4){// date
				if (date2int(array[index][column]) < date2int(minValue[column]))// Compare number
				{
					//cout << "    " << array[index] << "<" << minValue << endl;

					// if current value < minValue
					// then replace min's Value by current value
					// then replace min's Index by current index
					minValue = array[index];
					minIndex = index;
				}
			}
			else
			{
				if (stod(array[index][column]) > stod(minValue[column]))// Compare number
				{
					//cout << "    " << array[index] << "<" << minValue << endl;

					// if current value < minValue
					// then replace min's Value by current value
					// then replace min's Index by current index
					minValue = array[index];
					minIndex = index;
				}
			}

		}

		// Swap values
		array[minIndex] = array[startScan];
		array[startScan] = minValue;
	}
}