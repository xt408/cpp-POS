///////////////////////////////////////////////////////////
//  Inventory.h
//  Implementation of the Class Inventory
//  Created on:  11/15/2016
//  Author: Robert T
///////////////////////////////////////////////////////////

// Pseudocode:
// class Inventory
// - title: char;
// - ISBN: char;
// - author: char;
// - publisher: char;
// - date_added: char;
// - quantity: int;
// - wholesale_cost: double;
// - retail_price: double;
// - lookup(): void;
// - addABook(): void;
// - editABook(): void;
// - deleteABook(): void;
// # delimiter: const char = '|';
// # dataFileName: string = "books.txt";
// # **books: string = new string* [4];
// # bookRow: int;
// # bookColumn: const int = 8;
// Mutators
// # importDatafile(): void;
// # exportDatafile(): void;
// # csv2arr(string): string*;
// # setBookArray(string**): void;
// + setAuthor(int subscript, string author): void;
// + setTitle(int subscript, string title): void;
// + setISBN(int subscript, string isbn): void;
// + setPublisher(int subscript, string publisher): void;
// + setDateAdded(int subscript, string date): void;
// + setQuantity(int subscript, int qty): void;
// + setWhosleCost(int subscript, int cost): void;
// + setRetailPrice(int subscript, int price): void;

// Accessors
// + Inventory();
// + virtual ~Inventory();
// # getBookArray(): string** : const;
// # showbook(string * book, bool showHeading): void;
// # listBooks(): void;
// + deleteMemory(): void;
// + menu(): virtual void ;// Virtual function for dynamic binding / overriding
// + binarySearch(string**, string, int ): int;
// + selectionSort(string**, int): void;
// + implode(string *, char): string;
// + date2int(string ): int;
// + getAuthor(int subscript): string;
// + getTitle(int subscript): string;
// + getISBN(int subscript): string;
// + getPublisher(int subscript): string;
// + getDateAdded(int subscript): string;
// + getQuantity(int subscript): string;
// + getWhosleCost(int subscript): string;
// + getRetailPrice(int subscript): string;
// + main(): friend int ; // Friend function
// operator[](int subscript): string *; // Operator overloading

#ifndef _CRT_SECURE_NO_WARNING_INVENTORY
#define _CRT_SECURE_NO_WARNING_INVENTORY
#include <string>
using namespace std;

class Inventory
{
private:
	char title;
	char ISBN;
	char author;
	char publisher;
	char date_added;
	int quantity;
	double wholesale_cost;
	double retail_price;

	void lookup();
	void addABook();
	void editABook();
	void deleteABook();

protected:

	int bookRow = 0;
	const char delimiter = '|';
	string dataFileName = "books.txt";
	string **books;// = new string*[3];
	const int bookColumn = 8;

    // Mutators
	virtual void importDatafile();
	void exportDatafile();
	string *csv2arr(string);
	void setBookArray(string**);

    // Accessors
    string **getBookArray() const;
	void listBooks();
	void showbook(string * book, bool showHeading);

public:
	Inventory();
	virtual ~Inventory();
	void deleteMemory();

	// Virtual function for dynamic binding / overriding
	virtual void menu();

    int binarySearch(string**, string, int );
    void selectionSort(string**, int);
    string implode(string *, char);
    int date2int(string );

	// Accessors
    string getAuthor(int subscript);
    string getTitle(int subscript);
    string getISBN(int subscript);
    string getPublisher(int subscript);
    string getDateAdded(int subscript);
    string getQuantity(int subscript);
    string getWhosleCost(int subscript);
    string getRetailPrice(int subscript);

    // Mutators
	void setAuthor(int subscript, string author);
	void setTitle(int subscript, string title);
	void setISBN(int subscript, string isbn);
	void setPublisher(int subscript, string publisher);
	void setDateAdded(int subscript, string date);
	void setQuantity(int subscript, int qty);
	void setWhosleCost(int subscript, int cost);
	void setRetailPrice(int subscript, int price);

	// Friend function
	friend int main();

    // Operator overloading - get a book from book array
    string *operator[](int subscript){
        return books[subscript];
    }
};
#endif
