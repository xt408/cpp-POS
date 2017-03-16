///////////////////////////////////////////////////////////
//  Cashier.cpp
//  Implementation of the Class Cashier
//  Created on:  11/15/2016
//  Author: Robert T
///////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <atltime.h>
#include <iomanip>

#include "Cashier.h"
using namespace std;

Cashier::Cashier(){
	purchased_books = new string *[1];
}

Cashier::~Cashier(){

}

void Cashier::menu(){

	int choice;
	bool exit = false;

	do
	{
		system("cls");
		cout << "*****************************************" << endl;
		cout << "                Booksellers        " << endl;
		cout << "                  Cashier                " << endl << endl;
		cout << "1. Cash register" << endl;
		cout << "2. Return to Main Menu " << endl;
		cout << "*****************************************" << endl << endl;

		cout << "Enter Your Choice:";
		while (!(cin >> choice))
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid choice, please enter a whole number:";
		}

		if (choice == 1){// Inventory Listing
			purchaseBooks();
		}
		else
		{
			deleteMemory();
			exit = true;
		}
	} while (exit != true);

}

void Cashier::purchaseBooks()
{
	//listBooks();
	deleteMemory();

	bool exit = false;
	string choice = "yes";
	string isbn;

	do
	{
		if (choice == "yes")
		{
			string keyword;
			int quantity;

			cout << "Please enter book (ISBN, title):";
			cin >> keyword;

			int searchRange[] = { 0, 1 }; // Searching book's ISBN, Title
			int searchRangeSize = sizeof(searchRange) / sizeof(searchRange[0]);

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

				int book_quantity = stoi(books[key_found][5]);

				if (book_quantity>0)
				{
					cout << "Please enter quantity (1-" << book_quantity << "):";
					if (!(cin >> quantity) || quantity < 1 || quantity > book_quantity)
					{
						do{
							cin.clear();
							cin.ignore(INT_MAX, '\n');
							cout << "Error, please enter a whole number between 1 and " << book_quantity << ":";
						} while (!(cin >> quantity) || quantity < 1 || quantity > book_quantity);
					}

					isbn = books[key_found][0];
					addBookToCart(isbn, to_string(quantity));
				}
				else
				{
					cout << "Sorry! This book is sold out." << endl;
				}
			}
			else
			{
				cout << "There are no books matching " << keyword << endl;
			}
			cout << "\n\n" << endl;

			cout << "Add more book? (yes/no):";
			cin >> choice;
		}
		else
		{
			exit = true;
		}

	} while (exit==false);

	if (purchased_books_row>0)
	{
		system("cls");
		displayShopppingCart();
	}

	system("pause");
}

bool Cashier::addBookToCart(string isbn, string quantity){
	bool book_existed = false;

	// Find, weather book exists
	for (int i = 0; i < purchased_books_row; i++)
	{
		if (purchased_books[i][0] == isbn)
		{
			int qty = stoi(purchased_books[i][1]) + stoi(quantity);
			purchased_books[i][1] = to_string(qty); // quantity
			book_existed = true;
		}
	}

	if (book_existed== false){
		purchased_books[purchased_books_row] = new string[2];
		purchased_books[purchased_books_row][0] = isbn; // book isbn
		purchased_books[purchased_books_row][1] = (quantity); // quantity

		purchased_books_row++;
	}

	return  true;
}


bool Cashier::placeOrder(){
	int key_found, new_qty;

	for (int i = 0; i < purchased_books_row; i++)
	{
		// Find book by ISBN
		key_found = binarySearch(getBookArray(), purchased_books[i][0], 0);

		if (key_found>-1)
		{

			new_qty = stoi(books[key_found][5]) - stoi(purchased_books[i][1]);
			books[key_found][5] = to_string(new_qty);
		}

	}

	exportDatafile();

	return  true;
}

void Cashier::displayShopppingCart()
{
	cout << endl;
	cout << "Serendipity Book Sellers\n" << endl;

	CTime time = CTime::GetCurrentTime();
	string date = to_string(time.GetMonth()) + "/" + to_string(time.GetDay()) + "/" + to_string(time.GetYear());
	cout << "Date:" << date << endl << endl;

	cout << setw(15) << left << "Qty";
	cout << setw(15) << left << "ISBN";
	cout << setw(60) << left << "Title";
	cout << setw(20) << left << "Price";
	cout << setw(20) << left << "Total";
	cout << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;

	// set precision
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout.setf(ios::fixed);


	// Loop to show books
	selectionSort(getBookArray(), 0);
	int key_found=-1;

	double amount=0, subtotal=0, tax=0, total=0;
	for (int i = 0; i < purchased_books_row; i++)
	{
		// Find book by ISBN
		key_found = binarySearch(getBookArray(), purchased_books[i][0], 0);
		if (key_found>-1)
		{
			amount = stod(purchased_books[i][1]) * stod(books[key_found][7]);
			subtotal += amount;

			cout << setw(15) << left << purchased_books[i][1];// qty
			cout << setw(15) << left << books[key_found][0]; // isbn
			cout << setw(60) << left << books[key_found][1]; // title
			cout << setw(10) << right << books[key_found][7]; // price
			cout << setw(20) << right << amount; // price
			cout << endl;
		}

	}

	tax = calculateTax(subtotal);
	total = subtotal + tax;

	cout << "\n\n\n";

	cout << setw(80) << right << "Subtotal: ";
	cout << setw(8) << right << subtotal << endl;

	cout << setw(80) << right << "Tax: ";
	cout << setw(8) << right << tax << endl;

	cout << setw(80) << right << "Total: ";
	cout << setw(8) << right << total << endl;

	cout << "Thank you for Shopping at Serendipity!" << endl;

	cout << "Confirmed checkout? (yes/no):";
	string choice;
	cin >> choice;

	if (choice == "yes")
	{
		placeOrder();
		cout << "Order placed." << endl;
	}
	else
	{
		cout << "Order cancelled." << endl;
	}
}

void Cashier::deleteMemory()
{
	// Delete array
	for (int i = 0; i < purchased_books_row; i++)
	{
		delete[] purchased_books[i];
	}

	purchased_books_row = 0;
}

template <class T>
T Cashier::calculateTax(T subtotal){
	if (subtotal > 0)
	{
		return taxRate * subtotal;
	}
	else
	{
		throw InvalidSubtotal();
	}

}