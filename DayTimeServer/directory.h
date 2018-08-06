// directory.h
// This file sets up the directory class 

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <vector>
#include <array>
#include "contacts.h"

class Directory {

private:
	std::vector<Personal*> personal_contact_book;
	std::vector<Business*> business_contact_book;

public:
	void add_contact();
	Personal* search_for_personal_contact(std::string);
	Business* search_for_business_contact(std::string);
	void personal_sort_by_name();
	void business_sort_by_name();
};

#endif DIRECTORY_H
