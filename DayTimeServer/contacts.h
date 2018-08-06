// contacts.h
// This file sets up the contact classes 

#ifndef CONTACTS_H
#define CONTACTS_H

#include <iostream>
#include <string>

// parent class for contact types 
class Contact {

protected:
	std::string full_name;
	std::string phone_number;

public:
	// create blank constructor 
	Contact();
	// takes in name and phone number
	Contact(std::string N, std::string P);

	void set_name(std::string);
	void set_phone(std::string);

	// void store_name(std::string);
	// void store_phone(std::string);

	std::string get_name();
	std::string get_phone();

	void print_contact_info();
};

class Personal : public Contact {

private:
	std::string nickname;

public:
	Personal();
	// takes in nickname 'NN' with N and P
	Personal(std::string NN, std::string N, std::string P);

	void set_nickname(std::string);
	// void store_nickname(std::string);
	std::string get_nickname();
	void print_contact_info();
};

class Business : public Contact {

private:
	std::string company;

public:
	Business();
	// takes in company 'C' with N and P
	Business(std::string C, std::string N, std::string P);
	
	void set_company(std::string);
	// void store_company(std::string);
	std::string get_company();
	void print_contact_info();
};

#endif CONTACTS_H













