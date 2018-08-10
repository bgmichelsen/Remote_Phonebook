// This file defines the three contact classes (Contact, Personal, and Business)
//
// Authors: William Bryant and Brandon Michelsen

#ifndef CONTACTS_H
#define CONTACTS_H

#include <iostream>
#include <string>

/// Parent contact class ///

class Contact {

protected:
	// Protected data (shared with inherited classes)
	std::string full_name;
	std::string phone_number;

public:
	// Create constructor 
	Contact();
	// Takes in name and phone number
	Contact(std::string N, std::string P);
	
	// Getters and setters
	void set_name(std::string);
	void set_phone(std::string);

	std::string get_name();
	std::string get_phone();

	// Display info
	void print_contact_info();
};

/// Child personal contact class ///

class Personal : public Contact {

private:
	// Private data
	std::string nickname;

public:
	// Create constructor
	Personal();
	// Takes in nickname 'NN' with N and P
	Personal(std::string NN, std::string N, std::string P);

	// Getters and setters
	void set_nickname(std::string);
	std::string get_nickname();

	// Display info
	void print_contact_info();
};

/// Child business contact class ///

class Business : public Contact {

private:
	// Private data
	std::string company;

public:
	// Create constructor
	Business();
	// Takes in company 'C' with N and P
	Business(std::string C, std::string N, std::string P);

	// Getters and setters
	void set_company(std::string);
	std::string get_company();

	// Display info
	void print_contact_info();
};

#endif // CONTACTS_H