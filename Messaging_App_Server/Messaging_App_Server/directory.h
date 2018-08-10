// This file creates the class definition for the Directory (contact book)
//
// Authors: William Bryant and Brandon Michelsen

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <vector>
#include "contacts.h"

class Directory {

private:
	// Create vectors with pointers to the Personal and Business objects
	std::vector<Personal*> personal_contact_book;
	std::vector<Business*> business_contact_book;
public:
	// Create functions for using the directory. Functionality described in directory.cpp
	void add_contact(std::string, std::string, std::string, std::string);
	Personal* search_for_personal_contact(std::string);
	Business* search_for_business_contact(std::string);
	void personal_sort_by_name();
	void business_sort_by_name();
	void sort_phonebook_by_name();
	std::vector<Personal*>* return_personal_contact_book();
	std::vector<Business*>* return_business_contact_book();
	bool is_empty();
};

#endif // DIRECTORY_H