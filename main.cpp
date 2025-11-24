// Ashley Judah
// main.cpp

#include <iostream>
#include <limits>
#include <memory>
#include "EventManager.h"
#include "Organizer.h"
#include "Attendee.h"

// Initial User Display in Terminal
void DisplayMainMenu() {
	std::cout << "\n--- Main Menu ---\n";
	std::cout << "1. Choose a role: Attendee or Organizer\n";
	std::cout << "2. Exit\n";
	std::cout << "Enter your choice: ";
}

int main() {

	// create instances of event
	EventManager* event = EventManager::GetInstance();	

	// load users from csv
	event->LoadUsers();
	
	// load transactions from csv
	event->LoadEvents();
	
	// while loop to run while conditions are true
	bool running = true;

	// Retrieve all users
	auto allUsers = event->GetAllUsers();

	// auto allEvents = event->getAllEvents
	auto allEvents = event->GetAllEvents();
	
	while (running) {
		DisplayMainMenu();
		
		// command line prompt to ask to login or register
		int choice;
		std::cin >> choice;

		if (std::cin.fail()) {
			std::cin.clear(); 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			std::cout << "\n[Error] Invalid input. Please enter a number.\n";
			continue; 
		}
		
		switch(choice) {
			case 1: { // Choose a role - then create new account or login option
				// Ensure the list of all users is current
				allUsers = event->GetAllUsers();
				
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::string role;
				bool validRole = false;
				
				while (!validRole) {
					std::cout << "\nChoose a role (Attendee or Organizer): ";
					std::getline(std::cin, role);

					// make role lower case for case-sensitvity 
					std::string lowerRole = role;
					for (char &c : lowerRole) c = std::tolower(c);

					if (lowerRole == "attendee" || lowerRole == "organizer") {
						validRole = true;
					} else {
						std::cout << "\n[Error] Invalid role. Please enter 'Attendee' or 'Organizer'.\n";
					}
				}
				
				std::cout << "Please choose an option: \n";
				std::cout << "1. Login\n";
				std::cout << "2. Create new account\n";
				int option;
				std::cin >> option;

				if (option == 1) {

					std::string email, password;
					
					// get user email and password
					std::cout << "\n--- Login ---\n";
					
					// Get rid of empty lines (was causing the user to enter email and password on same line)
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Enter email: ";
					std::getline(std::cin, email);
	
					std::cout << "Enter Password: ";
					std::getline(std::cin, password);
	
					// loop through user list to authenticate user input - get user type
					std::shared_ptr<User> loggedInUser = nullptr;
					std::string userType = "";
					
					for (const auto& user : allUsers) {
						if (user->GetEmail() == email && user->GetPassword() == password) {
							loggedInUser = user;
							userType = user->GetUserType();
							break;
						}
					}
					
					// show error message if input doesn't match any user
					if (loggedInUser == nullptr) {
							std::cout << "\n[Error] Invalid email or password. Please try again.\n";
						break;
					}
	
				// Display different dashboard depending on user type (organizer or attendee)
				if (userType == "Organizer") {
					auto organizer = std::make_shared<Organizer>();
					organizer->SetUserID(loggedInUser->GetUserID());
					organizer->SetUsername(loggedInUser->GetUsername());
					organizer->SetEmail(loggedInUser->GetEmail());
					organizer->SetPassword(loggedInUser->GetPassword());
					organizer->SetUserType(loggedInUser->GetUserType());
					organizer->SetAccountBalance(loggedInUser->GetAccountBalance());
					
					organizer->ShowOrganizerInterface();
						
				} else if (userType == "Attendee") {
					auto attendee = std::make_shared<Attendee>();
					attendee->SetUserID(loggedInUser->GetUserID());
					attendee->SetUsername(loggedInUser->GetUsername());
					attendee->SetEmail(loggedInUser->GetEmail());
					attendee->SetPassword(loggedInUser->GetPassword());
					attendee->SetUserType(loggedInUser->GetUserType());
					attendee->SetAccountBalance(loggedInUser->GetAccountBalance());
					
					attendee->ShowAttendeeInterface();
				} else {
					std::cout << "\nUnknown User type.\n";
				}
				} else if (option == 2) {
						// Create a new user
						std::shared_ptr<User> newUser;
						std::string lowerRole = role;
						for (char &c : lowerRole) c = std::tolower(c);
						if (lowerRole == "attendee") {
						    newUser = std::make_shared<Attendee>();
						} else if (lowerRole == "organizer") {
						    newUser = std::make_shared<Organizer>();
						} else {
						    std::cout << "[Error] Invalid role for account creation.\n";
						    break;
						}
						int newUserID = event->GenerateUserID();
						// Set user type to chosen role
						newUser->SetUserType(role);
						newUser->SetUserID(newUserID);

						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						// Enter a username
						std::string username;
						std::cout << "Enter a username: ";
						std::getline(std::cin, username);
						newUser->SetUsername(username);
						// Enter an email
						std::string email;
						std::cout << "Enter email: ";
						std::getline(std::cin, email);
						newUser->SetEmail(email);
						// Enter a password
						std::string password;
						std::cout << "Enter Password: ";
						std::getline(std::cin, password);
						newUser->SetPassword(password);
						// Enter an account balance
						float accountBalance;
						std::cout << "Enter Account Balance: ";
						std::cin >> accountBalance;
						newUser->SetAccountBalance(accountBalance);

						event->RegisterUser(newUser);

						// Refresh user list to include newly created user
						allUsers = event->GetAllUsers();

						std::cout << "\n[Success] Account created successfully!\n";
						std::cout << "User ID: " << newUserID << "\n";
						std::cout << "You can now log in with your credentials.\n\n";
						
					} else {
							std::cout << "\nInvalid option. Returning to main menu.\n";
						}
				
					break;
			}
			case 2: {
				std::cout << "\nThank you for using Events!\n";
				running = false;
				break;
			}
			default: {
				std::cout << "\nInvalid choice. Please try again\n";
				break;
			}
		}
		
	}

	return 0;
}