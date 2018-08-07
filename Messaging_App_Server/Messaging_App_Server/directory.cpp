// directory.cpp
// This file defines the directory class 

#include <iostream>
#include <vector>
#include <set> // for sorting 
#include <algorithm> // for std::find
#include "directory.h"
#include "contacts.h"

void Directory::add_contact(std::string choice, std::string name, std::string number, std::string additionalInfo) {
	if (choice == "business" || choice == "Business") {
		Business* new_contact = new Business;

		new_contact->set_name(name);
		new_contact->set_phone(number);
		new_contact->set_company(additionalInfo);

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

Personal* Directory::search_for_personal_contact(std::string input) {
	if (personal_contact_book.empty())
		return  nullptr;
	else {
		for (unsigned int i = 0; i < personal_contact_book.size(); i++) {
			if (personal_contact_book[i]->get_name() == input)
				return personal_contact_book[i];
			else if (personal_contact_book[i]->get_phone() == input)
				return personal_contact_book[i];
			else if (personal_contact_book[i]->get_nickname() == input)
				return personal_contact_book[i];
		}
		return nullptr;
	}
}

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
		for (unsigned int i = 0; i < personal_contact_book.size(); i++) {
			if (i < (personal_contact_book.size() - 1)) {
				std::string contact1 = personal_contact_book[i]->get_name();
				std::string contact2 = personal_contact_book[(i + 1)]->get_name();

				if (contact1 > contact2) {
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
		for (unsigned int i = 0; i < business_contact_book.size(); i++) {
			if (i < (business_contact_book.size() - 1)) {
				std::string contact1 = business_contact_book[i]->get_name();
				std::string contact2 = business_contact_book[(i + 1)]->get_name();

				if (contact1 > contact2) {
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

bool Directory::is_empty() {
	return (business_contact_book.empty() && personal_contact_book.empty());
}