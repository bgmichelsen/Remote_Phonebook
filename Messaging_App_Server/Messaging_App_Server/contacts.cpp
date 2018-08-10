// This is the file for defining the function in the Contact, Personal, and Business classes
//
// Authors: William Bryant and Brandon Michelsen

#include <iostream>
#include "contacts.h"

/// Define Contact ///

// Default constructor
Contact::Contact() {};
// User defined constructor, function overload
Contact::Contact(std::string N, std::string P) {
	full_name = N;
	phone_number = P;
}

// These are setters and getters
void Contact::set_name(std::string N) { full_name = N; }
void Contact::set_phone(std::string P) { phone_number = P; }

std::string Contact::get_name() { return full_name; }
std::string Contact::get_phone() { return phone_number; }

// Funcion to print contact info
void Contact::print_contact_info() {
	std::cout << "Contact's name is " << get_name() << std::endl;
	std::cout << "Contact's phone number is " << get_phone() << std::endl;
}

/// Define Personal /// 

// Default constructor
Personal::Personal() {};
// Inheritence of full_name and phone_number 
Personal::Personal(std::string NN, std::string N, std::string P) : Contact::Contact(N, P) {
	nickname = NN;
}
// Getters and setters
void Personal::set_nickname(std::string NN) { nickname = NN; }
std::string Personal::get_nickname() { return nickname; }

// Function to print contact info
void Personal::print_contact_info() {
	Contact::print_contact_info();
	std::cout << "Contact's nickname is " << get_nickname() << std::endl;
}

/// Define Business /// 

// Default constructor
Business::Business() {};
// inheritance of full_name and phone number
Business::Business(std::string C, std::string N, std::string P) : Contact::Contact(N, P) {
	company = C;
}

// Getters and setters
void Business::set_company(std::string C) { company = C; }
std::string Business::get_company() { return company; }

// Function to print contact info
void Business::print_contact_info() {
	Contact::print_contact_info();
	std::cout << "Contact's company is " << get_company() << std::endl;
}