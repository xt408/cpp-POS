///////////////////////////////////////////////////////////
//  Cashier.h
//  Implementation of the Class Cashier
//  Created on:  11/15/2016
//  Author: Robert T
///////////////////////////////////////////////////////////

// Pseudocode:
// class Cashier : public Inventory
// - purchased_books: string ** ;
// - purchased_books_row: int =0;
// - book_isbn: char;
// - book_title: char;
// - book_qty: int;
// - book_price: double;
// - book_total: int;
// - subtotal: double;
// - taxRate: const double  = 0.0875;
// - tax: double;
// - total: int;
// - char date_ordered: char;
// Accessors
// + Cashier();
// + virtual ~Cashier();
// + menu(): void;
// + purchaseBooks(): void;
// + displayShopppingCart(): void;
// Mutators
// + addBookToCart(string isbn, string quantity): void;
// + placeOrder(): void;
// + deleteMemory(): void;
// Template
// T calculateTax(T subtotal);
// Exception
// class InvalidSubtotal{};
// Friend function
// friend int main();


#ifndef _CRT_SECURE_NO_WARNING_CASHIER
#define _CRT_SECURE_NO_WARNING_CASHIER
#include "Inventory.h"
class Cashier : public Inventory
{
private:
	string ** purchased_books;
	int purchased_books_row=0;

	char book_isbn;
	char book_title;
	int book_qty;
	double book_price;
	int book_total;
	double subtotal;
	const double taxRate = 0.0875;
	double tax;
	int total;
	char date_ordered;

public:
	Cashier();
	virtual ~Cashier();

    // Accessors
	void menu();
	void purchaseBooks();
    void displayShopppingCart();

    // Template
	template <class T>
	T calculateTax(T subtotal);

	// Exception
	class InvalidSubtotal{};

	// Friend function
	friend int main();

    // Mutators
	bool addBookToCart(string isbn, string quantity);
    bool placeOrder();
    void deleteMemory();
};
#endif
