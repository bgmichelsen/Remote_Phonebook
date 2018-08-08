// directory.cpp
// This file defines the directory class 

#include <iostream>
#include <vector>
#include <set> // for sorting 
#include <algorithm> // for std::find
#include "directory.h"
#include "contacts.h"

// Function takes in users contact choice with contact details 
void Directory::add_contact(std::string choice, std::string name, std::string number, std::string additionalInfo) {
	if (choice == "business" || choice == "Business") {

		// create a new object
		Business* new_contact = new Business;

		// store contact details 
		new_contact->set_name(name);
		new_contact->set_phone(number);
		new_contact->set_company(additionalInfo);

		// push in vector
		business_contact_book.push_back(new_contact);
	}
	else if (choice == "personal" || choice == "Personal") {

		Personal* new_contact = new Personal;

		new_contact->set_name(name);
		new_contact->set_phone(number);
		new_contact->set_nickname(additionalInfo);

		personal_contact_book.push_back(new_contact);
	}
}

// Function takes in an input from user to search for a personal contact
Personal* Directory::search_for_personal_contact(std::string input) {
	if (personal_contact_book.empty())
		return  nullptr;
	else {
		// if contact book is not empty, compare input to contact detials
		for (unsigned int i = 0; i < personal_contact_book.size(); i++) {
			if (personal_contact_book[i]->get_name() == input)
				return personal_contact_book[i];
			else if (personal_contact_book[i]->get_phone() == input)
				return personal_contact_book[i];
			else if (personal_contact_book[i]->get_nickname() == input)
				return personal_contact_book[i];
		}
		// if reches here, contact was not found
		return nullptr;
	}
}

// Function takes in an input from user to search for a business contact
Business* Directory::search_for_business_contact(std::string input) {
	if (business_contact_book.empty())
		return  nullptr;
	else {
		for (unsigned int i = 0; i < business_contact_book.size(); i++) {
			if (business_contact_book[i]->get_name() == input)
				return business_contact_book[i];
			else if (business_contact_book[i]->get_phone() == input)
				return business_contact_book[i];
			else if (business_contact_book[i]->get_company() == input)
				return business_contact_book[i];
		}
		return nullptr;
	}
}


void Directory::personal_sort_by_name() {
	// Variable for storing temporary contacts
	Personal* temp = nullptr;
	if (personal_contact_book.empty())
		std::cout << "Personal Book is empty!" << std::endl;
	else {
		// Sort the string in alphebatical order
		for (int j = 0; j < (personal_contact_book.size() - 1); j++) {
			for (unsigned int i = 0; i < personal_contact_book.size(); i++) {
				if (i < (personal_contact_book.size() - 1)) {
					std::string contact1 = personal_contact_book[i]->get_name();
					std::string contact2 = personal_contact_book[(i + 1)]->get_name();

					temp = personal_contact_book[(i + 1)];
					personal_contact_book[(i + 1)] = personal_contact_book[i];
					personal_contact_book[i] = temp;
				}
			}
		}
	}
}

void Directory::business_sort_by_name() {
	// Variable for storing temporary contacts
	Business* temp = nullptr;
	if (business_contact_book.empty())
		std::cout << "Personal Book is empty!" << std::endl;
	else {
		// Sort the string in alphebatical order
		for (int j = 0; j < (business_contact_book.size() - 1); j++) {
			for (unsigned int i = 0; i < business_contact_book.size(); i++) {
				if (i < (business_contact_book.size() - 1)) {
					std::string contact1 = business_contact_book[i]->get_name();
					std::string contact2 = business_contact_book[(i + 1)]->get_name();

					temp = business_contact_book[(i + 1)];
					business_contact_book[(i + 1)] = business_contact_book[i];
					business_contact_book[i] = temp;
				}
			}
		}
	}
}

void Directory::sort_phonebook_by_name() {
	// Call the sort methods
	if (!(business_contact_book.empty()))
		business_sort_by_name();
	if (!(personal_contact_book.empty()))
		personal_sort_by_name();
}

// Function returns personal contact book in vector for display
std::vector<Personal*>* Directory::return_personal_contact_book() {
	return &(personal_contact_book);
}

// Function returns business contact book in vector for display
std::vector<Business*>* Directory::return_business_contact_book() {
	return &(business_contact_book);
}

// 
bool Directory::is_empty() {
	return (business_contact_book.empty() && personal_contact_book.empty());
}