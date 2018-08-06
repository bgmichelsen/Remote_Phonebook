// directory.cpp
// This file defines the directory class 

#include <iostream>
#include <vector>
#include <set> // for sorting 
#include <algorithm> // for std::find
#include "directory.h"
#include "contacts.h"

void Directory::add_contact() {
	
	do {
		// prompt user 
		std::cout << "What type of contact would you like to add? " << std::endl;
		std::cout << "Personal contact - 1" << std::endl;
		std::cout << "Business contact - 2" << std::endl;
		std::cout << "Go back - 3" << std::endl;
		int choice;
		std::cin >> choice;

		if (choice == 1) {
			// add personal contact
			Personal* new_contact = new Personal;
			std::string user_input;

			// add name
			std::cout << "Give contact's first and/or last name: " << std::endl;
			std::cin.ignore();
			std::getline(std::cin, user_input);
			new_contact->set_name(user_input);

			// add phone number
			std::cout << "Give contact's phone number: " << std::endl;
			std::getline(std::cin, user_input);
			new_contact->set_phone(user_input);

			// add nickname
			std::cout << "Give contact's phone nickname: " << std::endl;
			std::getline(std::cin, user_input);
			new_contact->set_nickname(user_input);

			// add to contact book
			personal_contact_book.push_back(new_contact);
			
			// prompt user
			std::cout << "Added the following contact to Contact Book: " << std::endl;
			new_contact->print_contact_info();
			system("pause");
		}
		else if (choice == 2) {
			// add business contact
			Business* new_contact = new Business;
			std::string user_input;

			// add name
			std::cout << "Give contact's first and/or last name: " << std::endl;
			std::cin.ignore();
			std::getline(std::cin, user_input);
			new_contact->set_name(user_input);

			// add phone number
			std::cout << "Give contact's phone number: " << std::endl;
			std::getline(std::cin, user_input);
			new_contact->set_phone(user_input);

			// add company
			std::cout << "Give contact's company: " << std::endl;
			std::getline(std::cin, user_input);
			new_contact->set_company(user_input);

			// add to contact book
			business_contact_book.push_back(new_contact);

			// prompt user
			std::cout << "Added the following contact to Contact Book: " << std::endl;
			new_contact->print_contact_info();
			system("pause");
		}
		else if (choice == 3) {
			std::cout << "Back to menu..." << std::endl;
			break; // exit loop
		}
		else {
			std::cout << "Invalid input - please go again..." << std::endl;
		}
	} while (true);
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
	if (personal_contact_book.empty())
		std::cout << "Personal Book is empty!" << std::endl;
	else {
		for (unsigned int i = 0; i < personal_contact_book.size(); i++) {
			personal_contact_book[i]->get_name();
		}
	}
}