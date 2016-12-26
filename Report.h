///////////////////////////////////////////////////////////
//  Report.h
//  Implementation of the Class Report
//  Created on:  11/15/2016
//  Author: Robert T
///////////////////////////////////////////////////////////

// Pseudocode:
// class Report : public Inventory
// + Report();
// + virtual ~Report();
// Accessors
// + void inventoryList(): void;
// + inventoryWholesaleValue(): void;
// + inventoryRetailValue(): void;
// + listByQuantity(): void;
// + listByCost(): void;
// + listByAge(): void;
// + menu(): void;
// Mutators
// + selectionSortByNumber(string** array, int column): void;
// Friend function
// + main(): friend int;


#ifndef _CRT_SECURE_NO_WARNING_REPORT
#define _CRT_SECURE_NO_WARNING_REPORT
#include "Inventory.h"

class Report : public Inventory
{
public:
	Report();
	virtual ~Report();

    // Accessors
	void inventoryList();
	void inventoryWholesaleValue();
	void inventoryRetailValue();
	void listByQuantity();
	void listByCost();
	void listByAge();
	void menu();

    // Mutators
	void selectionSortByNumber(string** array, int column);

	// Friend function
	friend int main();
};
#endif
