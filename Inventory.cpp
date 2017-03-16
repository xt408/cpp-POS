///////////////////////////////////////////////////////////
//  Inventory.cpp
//  Implementation of the Class Inventory
//  Created on:  11/15/2016
//  Author: Robert T
///////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // Header providing parametric manipulators
#include <sstream> // Header providing string stream classes


#include "Inventory.h"
using namespace std;

string* Inventory::csv2arr(string line)
{
	const int SIZE = 8;
	string str, *ret = new string[SIZE];

	istringstream is(line); // Input string stream

	int i = 0;
	while (getline(is, str, delimiter))
	{
		//cout << str << endl;
		ret[i] = str;
		i++;
	}

	return ret;
}

Inventory::Inventory(){
	books = new string*[99];
	importDatafile();
	selectionSort(getBookArray(), 0);

}

Inventory::~Inventory(){
	deleteMemory();
}

void Inventory::deleteMemory()
{
	//cout << "Inventory" << endl;
	if (bookRow > 0){
		//cout << "going to delete book array." << endl; system("pause");
		for (int i = 0; i < bookRow; i++) {
			//cout << "going to delete book array :" << i << endl; system("pause");
			delete[] books[i];
			//cout << "deleted book array :" << i << endl; system("pause");
		}

		bookRow = 0;
		//cout << "books deleted." << endl; system("pause");
	}
}


void Inventory::importDatafile(){
	fstream file; // txt database file
	file.open(dataFileName, ios::in);
	string line, str;
	string *strArr;

	if (file.fail())// If the file does not existed
	{
		cout << "The database file (books.txt) does not exist." << endl;
		system("PAUSE");
		exit(0);
	}
	else// If the file successfully opened
	{
		int SIZE = 0;

		while (getline(file, line)){
			books[SIZE] = new string[bookColumn]; // columns
			strArr = csv2arr(line);

			for (int i = 0; i < 8; i++){
				books[SIZE][i] = strArr[i];
			}

			SIZE++;
		}

		if (SIZE > bookRow){
			bookRow = SIZE;
		}

		//cout << bookRow << " books imported" << endl; system("pause");
		//setBookArray(books);
		//listBooks();
	}

	file.close();
}

void Inventory::exportDatafile()
{
	fstream file; // txt database file
	file.open(dataFileName, ios::out);

	//cout << "111" << endl; system("pause");

	if (file.fail())
	{
		cout << "Couldn't open the database file (books.txt)." << endl;
		system("PAUSE");
		exit(0);
	}
	else
	{
		string str;
		for (int i = 0; i < bookRow; i++){
			str = implode(books[i], '|');
			file << str << endl; // Write to file
		}// end for
	}

	file.close();
}


string Inventory::implode(string* arr, char delimiter='|'){

	string str;
	for (int i = 0; i < bookColumn; i++)
	{
		if (i < bookColumn-1)
		{
			str += arr[i] + delimiter;
		}
		else
		{
			str += arr[i];
		}

	}

	return str;
}

void Inventory::setBookArray(string **arr){
	books = arr;
}

string ** Inventory::getBookArray() const{
	return books;
}

void Inventory::listBooks(){
	books = getBookArray();

	for (int i = 0; i < bookRow; i++){
		if (i == 0){
			showbook(books[i], true);
		}
		else
		{
			showbook(books[i], false);
		}
	}// end for
}

void Inventory::showbook(string * book, bool showHeading){
	if (showHeading)
	{
		cout << setw(15) << left << "ISBN";
		cout << setw(70) << left << "Title";
		cout << setw(25) << left << "Author";
		cout << setw(25) << left << "Publisher";
		cout << setw(15) << left << "Date added";
		cout << setw(15) << left << "Quantity";
		cout << setw(25) << left << "Wholesale cost";
		cout << setw(25) << left << "Retail price";
		cout << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

	}

	cout << setw(15) << left << book[0]; // ISBN
	cout << setw(70) << left << book[1]; // Title
	cout << setw(25) << left << book[2]; // Author
	cout << setw(25) << left << book[3]; // Publisher
	cout << setw(15) << left << book[4]; // Date added
	cout << setw(10) << right << book[5]; // Quantity
	cout << setw(18) << right << book[6]; // Wholesale cost
	cout << setw(18) << right << book[7]; // Retail price


	cout << endl;
}

void Inventory::lookup(){

	//listBooks();

	cout << "\nPlease enter book ISBN, title or author name to look up:";
	string keyword;
	cin >> keyword;

	int searchRange[] = { 0, 1, 2 }; // Searching book's ISBN, Title, Author
	int searchRangeSize = sizeof(searchRange) / sizeof(searchRange[0]);
	//cout << "size of range: " << searchRangeSize; system("pause");

	int key_found = -1;
	int index = 0;
	do
	{
		selectionSort(getBookArray(), searchRange[index]);
		key_found = binarySearch(getBookArray(), keyword, searchRange[index]);
		index++;
	} while (key_found == -1 && index < searchRangeSize);

	//cout << "key:" << key_found << endl;
	if (key_found != -1){
		showbook(books[key_found], true);
	}
	else
	{
		cout << "There are no books matching " << keyword << endl;
	}
	cout << "\n\n" << endl;
	system("pause");

}

void Inventory::menu(){
	int choice;
	bool exit = false;

	do
	{
		system("cls");
		cout << "*****************************************" << endl;
		cout << "Secrendipity Booksellers" << endl;
		cout << "   Inventory Database   " << endl << endl;
		cout << "1. Look Up a Book" << endl;
		cout << "2. Add a Book" << endl;
		cout << "3. Edit a Book's Record" << endl;
		cout << "4. Delete a Book" << endl;
		cout << "5. Return to the Main Menu" << endl;
		cout << "*****************************************" << endl << endl;

		cout << "Enter Your Choice:";
		while (!(cin >> choice))
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid choice, please enter a whole number:";
		}

		if (choice == 1){// Look up a book
			lookup();
		}
		else if (choice == 2) // add a book
		{
			addABook();
		}
		else if (choice == 3) // edit a book
		{
			editABook();
		}
		else if (choice == 4) // edit a book
		{
			deleteABook();
		}
		else
		{
			exit = true;
		}
	} while (exit != true);

}


string Inventory::getAuthor(int subscript){

	return books[subscript][2];
}


void Inventory::setAuthor(int subscript, string author){
	books[subscript][2] = author;
}


string Inventory::getTitle(int subscript){

	return books[subscript][1];
}


void Inventory::setTitle(int subscript, string title){
	books[subscript][1] = title;
}


string Inventory::getISBN(int subscript){
	return books[subscript][0];
}


void Inventory::setISBN(int subscript, string isbn){
	books[subscript][0] = isbn;
}


string Inventory::getPublisher(int subscript){

	return books[subscript][3];
}


void Inventory::setPublisher(int subscript, string publisher){
	books[subscript][3] = publisher;
}


string Inventory::getDateAdded(int subscript){

	return books[subscript][4];
}


void Inventory::setDateAdded(int subscript, string date){
	books[subscript][4] = date;
}


string Inventory::getQuantity(int subscript){

	return books[subscript][5];
}


void Inventory::setQuantity(int subscript, int qty){
	books[subscript][5] = qty;
}

string Inventory::getWhosleCost(int subscript){
	return books[subscript][6];
}

void Inventory::setWhosleCost(int subscript, int cost){
	books[subscript][6] = cost;
}

string Inventory::getRetailPrice(int subscript){
	return books[subscript][7];
}

void Inventory::setRetailPrice(int subscript, int price){
	books[subscript][7] = price;
}

//***************************************************************************
//* This funciton will perform binary search                                *
//* Auther: Xu Tang                                                         *
//***************************************************************************
int Inventory::binarySearch(string ** array, string keyword, int column=0)
{

	bool found = false; // Flag

	int size = bookRow - 1, // Array length
		first = 0,		// First array element
		last = size,	// Last array element
		middle,			// Mid point of search
		position = -1;	// Position of search value
	/*
	cout << "size: " << size << endl;
	cout << "first: " << first << endl;
	cout << "last: " << last << endl;
	system("pause");
	*/

	while (!found && first <= last)
	{
		middle = (first + last) / 2; // Calculate mid point

		if (array[middle][column].find(keyword) != -1) // If value is found at mid
		{
			found = true;
			position = middle;
		}
		else if (array[middle][column] > keyword) // If value is in lower half
		{
			last = middle - 1;
		}
		else// If value is in upper half
		{
			first = middle + 1;
		}
	}

	return position;
}

//***************************************************************************
//* This funciton will perform selecting sort                               *
//* For Ascending sort                                                      *
//* 1. Locate smallest element in array ¨Cswap it with element at position 0 *
//* 2. Locate second smallest element ¨Cswap it with element at position 1   *
//* 3. Continue process until array sorted                                  *
//* Auther: Xu Tang                                                         *
//***************************************************************************
void Inventory::selectionSort(string** array, int column)
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
			// Compare string
			// 0	They compare equal
			// <0	Either the value of the first character that does not match is lower in the compared string, or all compared characters match but the compared string is shorter.
			// >0	Either the value of the first character that does not match is greater in the compared string, or all compared characters match but the compared string is longer.
			if (array[index][column].compare(minValue[column]) < 0)
			{
				//cout << "    " << array[index] << "<" << minValue << endl;

				// if current value < minValue
				// then replace min's Value by current value
				// then replace min's Index by current index
				minValue = array[index];
				minIndex = index;
			}
		}

		// Swap values
		array[minIndex] = array[startScan];
		array[startScan] = minValue;
	}
}

void Inventory::addABook(){
	string isbn, title, author, publisher, date_added, quantity, wholesale_cost, retail_price;

	cout << "******************* Add a book ******************* " << endl;
	cout << "Enter ISBN:";
	cin >> isbn;

	cout << "Enter title:";
	cin >> title;

	cout << "Enter author:";
	cin >> author;

	cout << "Enter publisher:";
	cin >> publisher;

	cout << "Enter date:";
	cin >> date_added;

	cout << "Enter quantity:";
	cin >> quantity;

	cout << "Enter wholesale cost:";
	cin >> wholesale_cost;

	cout << "Enter retail price:";
	cin >> retail_price;

	string confirm;
	cout << "Confirm to add? (yes/no):";
	cin >> confirm;

	if (confirm == "yes")
	{
		bookRow++;
		books[bookRow - 1] = new string[bookColumn]; // columns

		books[bookRow - 1][0] = isbn;
		books[bookRow - 1][1] = title;
		books[bookRow - 1][2] = author;
		books[bookRow - 1][3] = publisher;
		books[bookRow - 1][4] = date_added;
		books[bookRow - 1][5] = quantity;
		books[bookRow - 1][6] = wholesale_cost;
		books[bookRow - 1][7] = retail_price;

		exportDatafile();
		importDatafile();
		cout << "New book has been added to database." << endl;

	}
	else
	{
		cout << "Add a book has been cancelled." << endl;
	}
	system("pause");
}

void Inventory::editABook(){
	//listBooks();

	cout << "******************* Edit a book ******************* " << endl;
	cout << "\nPlease enter book ISBN to edit:";
	string keyword;
	cin >> keyword;

	int searchRange[] = { 0 }; // Searching book's ISBN
	int searchRangeSize = sizeof(searchRange) / sizeof(searchRange[0]);

	int key_found = -1;
	int index = 0;
	do
	{
		selectionSort(getBookArray(), searchRange[index]);
		key_found = binarySearch(getBookArray(), keyword, searchRange[index]);
		index++;
	} while (key_found == -1 && index < searchRangeSize);

	if (key_found != -1){
		showbook(books[key_found], true);
	}
	else
	{
		cout << "There are no books matching " << keyword << endl;
	}


	string isbn, title, author, publisher, date_added, quantity, wholesale_cost, retail_price;

	cout << "Enter ISBN (" << books[key_found][0] << ") :";
	cin >> isbn;

	cout << "Enter new title (" << books[key_found][1] << "):";
	cin >> title;

	cout << "Enter new author (" << books[key_found][2] << "):";
	cin >> author;

	cout << "Enter new publisher (" << books[key_found][3] << "):";
	cin >> publisher;

	cout << "Enter new date (" << books[key_found][4] << "):";
	cin >> date_added;

	cout << "Enter new quantity (" << books[key_found][5] << "):";
	cin >> quantity;

	cout << "Enter new wholesale cost (" << books[key_found][6] << "):";
	cin >> wholesale_cost;

	cout << "Enter new retail price (" << books[key_found][7] << "):";
	cin >> retail_price;

	string confirm;
	cout << "Confirm to edit? (yes/no):";
	cin >> confirm;

	if (confirm == "yes")
	{

		books[key_found][0] = isbn;
		books[key_found][1] = title;
		books[key_found][2] = author;
		books[key_found][3] = publisher;
		books[key_found][4] = date_added;
		books[key_found][5] = quantity;
		books[key_found][6] = wholesale_cost;
		books[key_found][7] = retail_price;

		exportDatafile();
		cout << "Book info has been updated to database." << endl;

	}
	else
	{
		cout << "Edit a book has been cancelled." << endl;
	}
	cout << "\n\n" << endl;
	system("pause");
}

void Inventory::deleteABook(){
	//listBooks();

	cout << "******************* Delete a book ******************* " << endl;
	cout << "\nPlease enter book ISBN to delete:";
	string keyword;
	cin >> keyword;

	int searchRange[] = { 0 }; // Searching book's ISBN
	int searchRangeSize = sizeof(searchRange) / sizeof(searchRange[0]);

	int key_found = -1;
	int index = 0;
	do
	{
		selectionSort(getBookArray(), searchRange[index]);
		key_found = binarySearch(getBookArray(), keyword, searchRange[index]);
		index++;
	} while (key_found == -1 && index < searchRangeSize);

	if (key_found != -1){
		showbook(books[key_found], true);
	}
	else
	{
		cout << "There are no books matching " << keyword << endl;
	}

	string confirm;
	cout << "Confirm delete this book? (yes/no):";
	cin >> confirm;

	if (confirm == "yes")
	{
		//cout << bookRow << " books; delele book form index: " << key_found << endl; system("pause");

		int i;
		for (i = key_found; i < bookRow; i++)
		{
			books[i] = books[i + 1];
		}

		//delete[] books[i];// Delete last element from books

		bookRow--;
		exportDatafile();
		cout << "Deleted." << endl;
		//cout << bookRow << " books now;" << endl; system("pause");

	}
	else
	{
		cout << "Cancelled." << endl;
	}
	system("pause");
}

int Inventory::date2int(string c_date){
	int mm=0, dd=0, yyyy=0;
	sscanf_s(c_date.c_str(), "%d/%d/%d", &mm, &dd, &yyyy);

	string ret;
	ret += to_string(yyyy);
	//cout << ret << endl; system("pause");


	if (mm<10){
		ret += "0" + to_string(mm);
	}
	else
	{
		ret += to_string(mm);
	}
	//cout << ret << endl; system("pause");

	if (dd<10){
		ret += "0" + to_string(dd);
	}
	else
	{
		ret += to_string(dd);
	}
	//cout << ret << endl; system("pause");

	return stoi(ret);
}