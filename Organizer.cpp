// Organizer implementation file

#include "Organizer.h"
#include "Event.h"
#include "EventManager.h"
#include "Ticket.h"
#include <iostream>
#include <limits>

/**
	Display the menu options the organizer can choose from when logged in
*/
void Organizer::DisplayOrganizerMenu() {
	
	// std::cout << "Organizer: " << GetUsername() << "\n";
	std::cout << "Account Balance: $" << GetAccountBalance() << "\n";
	std::cout << "--------------------------------------\n";
	
	std::cout << "1. View all my events\n";
	std::cout << "2. Create new event\n";
	std::cout << "3. Close an event\n";
	std::cout << "4. Reopen an event\n";
	std::cout << "5. Update Account\n";
	std::cout << "6. Exit\n";
	std::cout << "Enter your choice: ";
}

/**
	Main interface loop for organizer
*/
void Organizer::ShowOrganizerInterface() {
	bool showMenu = true;
	int choice;
	
	std::cout << "\nWelcome, " << GetUsername() << "!\n";
	
	while (showMenu) {
		Organizer::DisplayOrganizerMenu();
		std::cin >> choice;
		
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
		switch(choice) {
			case 1: { // View all my events
				ViewAllEvents();
				break;
			}
			case 2: { // Create new event
				std::string category, name, tier;
				float basePrice;
				int totalTickets;
				
				std::cout << "\n--- Create New Event ---\n";
				std::cout << "Enter event category: ";
				std::getline(std::cin, category);
				
				std::cout << "Enter event name: ";
				std::getline(std::cin, name);
				
				std::cout << "Enter base ticket price: $";
				std::cin >> basePrice;
				
				std::cout << "Enter total tickets: ";
				std::cin >> totalTickets;
				
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Enter ticket tier (Standard/VIP/Premium): ";
				std::getline(std::cin, tier);
				
				CreateNewEvent(category, name, basePrice, totalTickets, tier);
				break;
			}
			case 3: { // close an event
				int closeEventID;
				std::cout << "Enter ID of event you would like to close: ";
				std::cin >> closeEventID;
				Organizer::CloseEvent(closeEventID);
				break;
			}
			case 4: { // reopen an event
				int reopeneventID;
				std::cout << "Enter ID of event you would like to reopen: ";
				std::cin >> reopeneventID;
				Organizer::ReopenEvent(reopeneventID);
				break;
			}
			case 5: { // Update Account
				std::cout << "What would you like to update? \n";
				std::string updateChoice;
				std::cout << "email\n";
				std::cout << "username\n";
				std::cout << "password\n";
				std::getline(std::cin, updateChoice);

				if (updateChoice == "email") {
					std::string newEmail;
					std::cout << "Enter new email: ";
					Organizer::SetEmail(newEmail);
				} else if (updateChoice == "username") {
					std::string newUsername;
					std::cout << "Enter new username: ";
					Organizer::SetUsername(newUsername);
				} else if (updateChoice == "password") {
					std::string newPassword;
					std::cout << "Enter new password: ";
					Organizer::SetPassword(newPassword);
				}
				break;
			}
			case 6: { // Exit
				std::cout << "\nLogging out...\n";
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
	Allows organizer to create a new event
	
	@params std::string category, std::string name, float basePrice, int totalTickets, std::string tier
	@return pointer to new event
*/
std::shared_ptr<Event> Organizer::CreateNewEvent(const std::string& category, const std::string& name, float basePrice, int totalTickets, const std::string& tier) {
    EventManager* eventManager = EventManager::GetInstance(); 

    auto newEvent = eventManager->CreateEvent(category, name, basePrice, totalTickets, tier, GetUserID());

    if (newEvent) {
        std::cout << "\n[Success] Event '" << name << "' created successfully!\n";
        std::cout << "Event ID: " << newEvent->GetEventID() << "\n";

        eventIDs_.push_back(newEvent->GetEventID());
    } else {
        std::cout << "\n[Error] Failed to create event.\n";
    }
    return newEvent; 
}

/**
	Close an event that is currently open

	@params eventID
*/
void Organizer::CloseEvent(int eventID) {
	EventManager* eventManager = EventManager::GetInstance(); 
	auto event = eventManager->GetEventByID(eventID);

	if (!event) {
		std::cout << "Event not found\n";
		return;
	}

	if (event->GetOrganizerID() != GetUserID()) {
		std::cout << "You do not have permission to close this event\n";
		return;
	}
	
	event->CloseEvent();
	event->SetTicketStatus("Closed");
	std::cout << "This event is now closed\n";
}

/**
	Reopen an event that is currently closed

	@params eventID
*/
void Organizer::ReopenEvent(int eventID) {
	EventManager* eventManager = EventManager::GetInstance(); 
	auto event = eventManager->GetEventByID(eventID);
	
	if (!event) {
		std::cout << "Event not found\n";
		return;
	}

	if (event->GetOrganizerID() != GetUserID()) {
		std::cout << "You do not have permission to reopen this event\n";
		return;
	}

	event->ReopenEvent();
	event->SetTicketStatus("Available");
	std::cout << "This event is now reopen\n";
}


/**
	View a list of all events by organizer

	@params eventID
*/
void Organizer::ViewAllEvents() {
	EventManager* eventManager = EventManager::GetInstance();
	auto allEvents = eventManager->GetAllEvents();
	
	std::cout << "\n--- My Events ---\n";
	bool foundEvents = false;
	
	for (const auto& event : allEvents) {
		if (event->GetOrganizerID() == GetUserID()) {
			foundEvents = true;
			std::cout << "ID: " << event->GetEventID() 
								<< " | " << event->GetEventName()
								<< " | Category: " << event->GetCategory()
								<< " | Price: $" << event->GetBaseTicketPrice()
								<< " | Tickets: " << event->GetSoldTickets() << "/" << event->GetTotalTickets()
								<< " | Status: " << event->GetTicketStatus()
								<< "\n";
		}
	}
	
	if (!foundEvents) {
			std::cout << "You haven't created any events yet.\n";
	}
}

/**
  View menu options to choose from 
*/
void Organizer::DisplayDashboard() {
	std::cout << "Organizer: " << GetUsername() << "\n";
	std::cout << "Account Balance: $" << GetAccountBalance() << "\n";
	std::cout << "--------------------------------------\n";
	
	ViewAllEvents();
}