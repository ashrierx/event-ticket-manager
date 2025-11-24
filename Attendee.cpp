// Attendee implementation file

#include "Attendee.h"
#include "Event.h"
#include "EventManager.h"
#include "Ticket.h"
#include <iostream>
#include <limits>


/**
	Display the menu options the attendee can choose from when logged in
*/
void Attendee::DisplayAttendeeMenu() {
	// std::cout << "Attendee: " << GetUsername() << "\n";
	std::cout << "Account Balance: $" << GetAccountBalance() << "\n";
	std::cout << "--------------------------------------\n";
	
	std::cout << "1. View all events\n";
	std::cout << "2. Purchase Tickets\n";
	std::cout << "3. Update Account\n";
	std::cout << "4. Exit\n";
	std::cout << "Enter your choice: ";
}

/**
	Main interface loop for attendee
*/
void Attendee::ShowAttendeeInterface() {
	bool showMenu = true;
	int choice = 0;
	EventManager* eventManager = EventManager::GetInstance();	
	auto allEvents = eventManager->GetAllEvents();

	std::cout << "\nWelcome, " << GetUsername() << "!\n";

	while (showMenu) {
		DisplayAttendeeMenu();
		std::cin >> choice;
		
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch(choice) {
			case 1: { // View ALL events
				std::cout << "\n--- All Events ---\n";
				for (const auto& event : allEvents) {
						std::cout << "ID: " << event->GetEventID() 
											<< " | " << event->GetEventName()
											<< " | Category: " << event->GetCategory()
											<< " | Price: $" << event->GetBaseTicketPrice()
											<< " | Tickets: " << event->GetSoldTickets() << "/" << event->GetTotalTickets()
											<< " | Status: " << event->GetTicketStatus()
											<< "\n";
				}
				std::cout << "\n";
				break;
			}
			case 2: { // Purchase Tickets
				for (const auto& event : allEvents) { 
					std::cout << "ID: " << event->GetEventID() 
									<< " | " << event->GetEventName()
									<< " | Category: " << event->GetCategory()
									<< " | Price: $" << event->GetBaseTicketPrice()
									<< " | Tickets: " << event->GetSoldTickets() << "/" << event->GetTotalTickets()
									<< " | Status: " << event->GetTicketStatus()
									<< "\n";
				}
				std::cout << "which event would you like to purchase tickets for? Enter ID of event: " << std::endl;
				int eventIDChoice;
				std::cin >> eventIDChoice;

				std::cout << "Enter quantity of tickets: ";
				int quantity;
				std::cin >> quantity;

				std::cout << "Enter tier of tickets: ";
				std::string tier;
				std::cin >> tier;

				Attendee::PurchaseTicket(eventIDChoice, quantity, tier);

				break;
			}
			case 3: { // Update Account
				std::cout << "What would you like to update? \n";
				std::cout << "email\n";
				std::cout << "username\n";
				std::cout << "password\n";

				std::string updateChoice;
				std::getline(std::cin, updateChoice);
				
				if (updateChoice == "email") {
					std::string newEmail;
					std::cout << "Enter new email: ";
					std::getline(std::cin, newEmail);
					SetEmail(newEmail);
					std::cout << "Success! Email updated to: " << newEmail << "\n";
				} else if (updateChoice == "username") {
					std::string newUsername;
					std::cout << "Enter new username: ";
					std::getline(std::cin, newUsername);
					SetUsername(newUsername);
					std::cout << "Success! Username updated to: " << newUsername << "\n";
				} else if (updateChoice == "password") {
					std::string newPassword;
					std::cout << "Enter new password: ";
					std::getline(std::cin, newPassword);
					SetPassword(newPassword);
					std::cout << "Success! Password updated!\n";
				}  else {
						std::cout << "Error: Invalid choice.\n";
					}

				EventManager* em = EventManager::GetInstance();
				auto allUsers = em->GetAllUsers();
				for (auto& user : allUsers) {
					if (user->GetUserID() == GetUserID()) {
						user->SetEmail(GetEmail());
						user->SetUsername(GetUsername());
						user->SetPassword(GetPassword());
						break;
					}
				}
				break;
			}
			case 4: { // Exit 
				std::cout << "\nThank you for using Events!\n";
				showMenu = false;
				break;
			}
			default: {
				std::cout << "Invalid choice. Please try again.\n";
				break;
			}
		}
	}
}

/**
    Allows a ticket to be purchased for an event

		@params eventID, quantity, tier
*/
void Attendee::PurchaseTicket(int eventID, int quantity, std::string tier) {
	EventManager* eventManager = EventManager::GetInstance();

	// Get old/current balance 
	float oldBalance = GetAccountBalance();
	
	eventManager->ProcessTicketPurchase(eventID, GetUserID(), quantity, tier);

	auto allUsers = eventManager->GetAllUsers();
	for (const auto& user : allUsers) {
		if (user->GetUserID() == GetUserID()) {
			SetAccountBalance(user->GetAccountBalance());  
			break;
		}
	}
	
	// Add ticket if purchase was successful
	if (GetAccountBalance() != oldBalance) {
		ticketIDs_.push_back(eventID);
		has_tickets_ = true;
	}
}

/**
    View all tickets purchased past and present 

		@params attendeeID
*/		
void Attendee::ViewTickets(int attendeeID) {
	if (ticketIDs_.empty()) {
		std::cout << "You have not purchased any tickets";
		return;
	}

	EventManager* eventManager = EventManager::GetInstance();
	std::cout << "Current Tickets: \n";

	for (int eventID : ticketIDs_) {
		auto event = eventManager->GetEventByID(eventID);

		if (event) {
			std::cout << "Event: " << event->GetEventID() 
														<< event->GetEventName() 
														<< event->GetCategory();
		}
	}
}

/**
    View ticket transaction details - breakdown of fees for each ticket

		@params attendeeID
*/		
void Attendee::ViewTransactionHistory(int attendeeID) {
	std::cout << "View Transaction history here\n";
}

/**
    View users tickets and account balance

		@params attendeeID
*/		
void Attendee::DisplayDashboard(int attendeeID) {
	std::cout << "Attendee: " << GetUsername() << "\n";
	std::cout << "Account Balance: $" << GetAccountBalance() << "\n";
	std::cout << "--------------------------------------\n";

	ViewTickets(attendeeID);
}