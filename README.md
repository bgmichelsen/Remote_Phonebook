# Remote_Phonebook
A basic client-server phonebook app.

# AirWave: The Remote Phonebook
Brandon Michelsen & William Bryant

Project Description:
  Our project is AirWave, a remote phonebook management program. The program is structured as a client-server set of applications, with the main core of the system being the server software. The server software handles most of the background work of the phonebook - creating a new contact, storing the contacts, deleting a contact, sorting contacts, etc. In addition to managing the contact storage, the server also provides data back to the user through the use of a menu and feedback data. The program manages two different types of contacts: business and personal. These two contacts differ slightly from each other in that they each have a different type of relationship with the user (a personal relationship versus a business relationship) and the additional data they take in (a nickname for a personal contact and a company for the business contact). These two types of contacts can help keep the contacts organized during the storing process.
  The client application provides the user interface for the remote storage program. It begins with an opening screen that describes what the program is and a basic description on how to use it. On the next screen, the application asks the user to enter the hostname or address of the server they would like to connect to. After connecting to the server, the menu from the server is forwarded to the client application and displayed to the user. The user can then enter values from the menu (options 1 through 6) that are forwarded back to the server to be used with the main program. The options allow for adding a contact (business or personal), searching for a particular contact (business or personal), sorting the contacts (business and personal), deleting a contact (business or personal), and viewing the contact list (business or personal).
  As the user enters data, the server tracks what the user has entered by displaying the last command through the console window. This allows for debugging on the server side of the program.
  All the input and output for this program is based around text data. When creating a contact, all the data members that are part of that contact is made up of strings - for the name, the phone number, the relationship, and any additional data. All the displays sent between the client and the server is also in the form of text data. When displaying the information for a contact, everything is also formatted as text data. The only exception to this is when a user enters an option from the menu. At first, the menu option starts as text data. However, the server takes that data and converts it into integer data to be used with a switch statement that allows the proper functionality to be chosen.

# The 9 Features:
Opening Screen:
We implemented an opening screen on the client-side of the application that describes what the program is and how to use it

Menu with Options:
On the server-side, we implemented a menu with options that the user can choose from to perform various actions; this menu is then forwarded to the client application where it is displayed to the user

4 Classes:
We implemented 4 classes for this project: a base contact class that describes the basic information for a contact, a personal class that describes a personal contact, a business class that describes a business contact, and a directory class that describes the structure and functionality of the phonebook

Encapsulation:
We incorporated encapsulation in this program by making sure the data and methods for our classes were under their respective access levels: private data going under private, public data going under public, and protected data going under protected

Inheritance:
We incorporated inheritance in this program by making the personal and business contact classes inherit data from the base contact class: the child classes inherit the name and phone number data from the base class

Search and Sort:
For search, we incorporated a basic algorithm that searches through the business directory and personal directory, respectively, and searches for a particular contact based off of a search term (contact’s name, number, relationship, or additional information), the algorithm returns the first result that matches the search criteria
For sort, we used a bubble sort algorithm that sorts the phonebook alphabetically based on the names of the contacts 

Vectors:
Vectors were used to store the contact objects (a vector of pointers to the objects); one vector was used for business contacts and another was used for personal contacts 

Exception Handling:
Exception handling was incorporated in both the client and server sides in order to catch any network errors encountered during operation and to prevent the program from crashing whenever the errors were encountered

Network Communication:
This is the biggest part of our program, as it is what allows the user to enter and store data; there is a client application that connects to a server application via a socket created using Boost ASIO

Boost Library:
We incorporated a couple aspects of the Boost Library in our program: one was the Boost ASIO library which allowed network communication and the other was the Boost Array, which was used as a buffer when reading data in from a socket
