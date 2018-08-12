// This is the file for defining the functions in the Directory class
//
// Authors: William Bryant and Brandon Michelsen

#include <iostream>
#include <vector>
#include <algorithm>
#include "directory.h"
#include "contacts.h"

// Function takes in users contact choice with contact details 
void Directory::add_contact(std::string choice, std::string name, std::string number, std::string relationship, std::string additional_info) {
	if (choice == "BUSINESS") {
		// If the user chooses business, add a new business contact

		// Create a new Business object
		Business* new_contact = new Business;

		// Store contact details 
		new_contact->set_name(name);
		new_contact->set_phone(number);
		new_contact->set_company(additional_info);
		new_contact->set_busines_relationship(relationship);

		// Push in vector
		business_contact_book.push_back(new_contact);
	}
	else if (choice == "PERSONAL") {
		// Otherwise, add a new Personal contact

		// Create a new Personal contact
		Personal* new_contact = new Personal;

		// Add contact info
		new_contact->set_name(name);
		new_contact->set_phone(number);
		new_contact->set_nickname(additional_info);
		new_contact->set_personal_relationship(relationship);

		// Push into vector
		personal_contact_book.push_back(new_contact);
	}
}

// Function takes in type of contact and contact search term for deletion
void Directory::erase_contact(std::string choice, std::string key_word) {
	if (choice == "BUSINESS") {
		// If the user chooses business, delete the instance of the business contact
		Business* contact = search_for_business_contact(key_word);
		business_contact_book.erase(std::remove(business_contact_book.begin(), business_contact_book.end(), contact), business_contact_book.end());
	}
	else if (choice == "PERSONAL") {
		// Otherwise, delete the instance of the personal contact
		Personal* contact = search_for_personal_contact(key_word);
		personal_contact_book.erase(std::remove(personal_contact_book.begin(), personal_contact_book.end(), contact), personal_contact_book.end());
	}
}

// Function takes in an input from user to search for a personal contact (returns a pointer to the found object, null ptr otherwise)
Personal* Directory::search_for_personal_contact(std::string input) {
	if (personal_contact_book.empty())
		// If the contact book is empty, return null ptr
		return  nullptr;
	else {
		// If contact book is not empty, compare input to contact details
		for (unsigned int i = 0; i < personal_contact_book.size(); i++) {
			std::string name = personal_contact_book[i]->get_name();
			std::string number = personal_contact_book[i]->get_phone();
			std::string nickname = personal_contact_book[i]->get_nickname();
			std::string relationship = personal_contact_book[i]->get_personal_relationship();

			if ((name.find(input) != std::string::npos) || (number == input) || (nickname == input) || (relationship.find(input) != std::string::npos))
				return personal_contact_book[i];
		}
		// If no contact is found, return null ptr
		return nullptr;
	}
}

// Function takes in an input from user to search for a business contact (returns pointer to found object, null ptr otherwise)
Business* Directory::search_for_business_contact(std::string input) {
	if (business_contact_book.empty())
		// If phone book is empty, return a null ptr
		return  nullptr;
	else {
		// If contact book is not empty, search for contact based on user input
		for (unsigned int i = 0; i < business_contact_book.size(); i++) {
			std::string name = business_contact_book[i]->get_name();
			std::string number = business_contact_book[i]->get_phone();
			std::string company = business_contact_book[i]->get_company();
			std::string relationship = business_contact_book[i]->get_business_relationship();

			if ((name.find(input) != std::string::npos) || (number == input) || (company == input) || (relationship.find(input) != std::string::npos))
				return business_contact_book[i];
		}
		// If the contact was not found, return null ptr
		return nullptr;
	}
}

// Function for sorting the personal contact book
void Directory::personal_sort_by_name() {
	// Variable for storing temporary contacts
	Personal* temp = nullptr;

	if (personal_contact_book.empty())
		// If the contact book is empty, cannot sort
		std::cout << "Personal Book is empty!";
	else {
		// Otherwise, sort based on Bubble Sort

		// Sort the string in alphebatical order
		bool swapped = true; // Variable for checking is data is swapped
		int j = 0; // Variable for tracking how many iterations of the loop

				   // Continue sorting the data until the data is in alhpabetical order
		while (swapped) {
			swapped = false;
			j++;
			for (int i = 0; i < (personal_contact_book.size() - j); i++) {
				std::string contact1 = personal_contact_book[i]->get_name();
				std::string contact2 = personal_contact_book[i + 1]->get_name();
				if (contact1 > contact2) {
					// If the the current element is alphabetically greater than the next, swap them
					temp = personal_contact_book[i];
					personal_contact_book[i] = personal_contact_book[i + 1];
					personal_contact_book[i + 1] = temp;
					// Update the swapped value to true (since we swapped the data)
					swapped = true;
				}
			}
		}
	}
}

// Function for sorting the business contact book
void Directory::business_sort_by_name() {
	// Variable for storing temporary contacts
	Business* temp = nullptr;


	if (business_contact_book.empty())
		// If the contact book is empty, cannot sort
		std::cout << "\nBusiness Book is empty!\n";
	else {
		// Otherwise, sort the string based on Bubble Sort

		// Sort the string in alphebatical order
		bool swapped = true; // Variable for checking if the data is swapped
		int j = 0; // Variable for tracking iterations of the loop

				   // Continue sorting until the data is in alphabetical order
		while (swapped) {
			swapped = false;
			j++;
			for (int i = 0; i < (business_contact_book.size() - j); i++) {
				std::string contact1 = business_contact_book[i]->get_name();
				std::string contact2 = business_contact_book[i + 1]->get_name();
				if (contact1 > contact2) {
					// If the current element is alphabetically greater than the next, swap them
					temp = business_contact_book[i];
					business_contact_book[i] = business_contact_book[i + 1];
					business_contact_book[i + 1] = temp;
					// Update the swapped value
					swapped = true;
				}
			}
		}
	}
}

// Function for calling the sorting methods on each contact book
void Directory::sort_phonebook_by_name() {
	// Call the sort methods
	business_sort_by_name();
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

// Function returns if the contact book is empty or not
bool Directory::is_empty() {
	return (business_contact_book.empty() && personal_contact_book.empty());
}