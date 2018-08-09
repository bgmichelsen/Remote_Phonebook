// directory.cpp
// This file defines the directory class 

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
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
			std::string name = personal_contact_book[i]->get_name();
			std::string number = personal_contact_book[i]->get_phone();
			std::string nickname = personal_contact_book[i]->get_nickname();

			std::transform(name.begin(), name.end(), name.begin(), ::toupper);
			std::transform(number.begin(), number.end(), number.begin(), ::toupper);
			std::transform(nickname.begin(), nickname.end(), nickname.begin(), ::toupper);
			std::transform(input.begin(), input.end(), input.begin(), ::toupper);

			if ((name == input) || (number == input) || (nickname == input))
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
			std::string name = business_contact_book[i]->get_name();
			std::string number = business_contact_book[i]->get_phone();
			std::string company = business_contact_book[i]->get_company();

			std::transform(name.begin(), name.end(), name.begin(), ::toupper);
			std::transform(number.begin(), number.end(), number.begin(), ::toupper);
			std::transform(company.begin(), company.end(), company.begin(), ::toupper);
			std::transform(input.begin(), input.end(), input.begin(), ::toupper);

			if ((name == input) || (number == input) || (company == input))
				return business_contact_book[i];
		}
		return nullptr;
	}
}


void Directory::personal_sort_by_name() {
	// Variable for storing temporary contacts
	Personal* temp = nullptr;
	if (personal_contact_book.empty())
		std::cout << "Personal Book is empty!";
	else {
		// Sort the string in alphebatical order
		bool swapped = true;
		int j = 0;

		while (swapped) {
			swapped = false;
			j++;
			for (int i = 0; i < (personal_contact_book.size() - j); i++) {
				std::string contact1 = personal_contact_book[i]->get_name();
				std::string contact2 = personal_contact_book[i + 1]->get_name();
				if (contact1 > contact2) {
					temp = personal_contact_book[i];
					personal_contact_book[i] = personal_contact_book[i + 1];
					personal_contact_book[i + 1] = temp;
					swapped = true;
				}
			}
		}
	}
}

void Directory::business_sort_by_name() {
	// Variable for storing temporary contacts
	Business* temp = nullptr;
	if (business_contact_book.empty())
		std::cout << "\nBusiness Book is empty!\n";
	else {
		// Sort the string in alphebatical order
		bool swapped = true;
		int j = 0;
		
		while (swapped) {
			swapped = false;
			j++;
			for (int i = 0; i < (business_contact_book.size() - j); i++) {
				std::string contact1 = business_contact_book[i]->get_name();
				std::string contact2 = business_contact_book[i + 1]->get_name();
				if (contact1 > contact2) {
					temp = business_contact_book[i];
					business_contact_book[i] = business_contact_book[i + 1];
					business_contact_book[i + 1] = temp;
					swapped = true;
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