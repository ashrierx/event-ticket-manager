// EventManager implementation file

#include "EventManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <cstdlib>

EventManager::EventManager() : eventID_(0), transactionID_(0) {}

/**
  Retrieves an instance of an event
*/
EventManager* EventManager::instance = nullptr;

/**
	Register a new user

	@params pointer to a user
*/
void EventManager::RegisterUser(std::shared_ptr<User> user) {
	users_.push_back(user);
}

/**
	Add a new event to the system
	
	@params event - pointer to a new event
*/
void EventManager::AddEvent(std::shared_ptr<Event> event) {
    events_.push_back(event);
}

/**
	Creates a new event
	
	@params category, name, basePrice, totalTickets, tier, organizerID
	@return pointer to events
*/
std::shared_ptr<Event> EventManager::CreateEvent(std::string category, std::string name, float basePrice, int totalTickets, std::string tier, int organizerID) {
    
    int newEventID = ++eventID_;
    
    auto newEvent = std::make_shared<Event>(
			newEventID, 
			category, 
			name, 
			basePrice, 
			totalTickets, 
			tier, 
			organizerID
    );

    events_.push_back(newEvent);
    
    std::cout << "[INFO] Created new event with ID: " << newEventID << "\n";
    return newEvent;
}


/**
  Loads Users from csv file
*/
void EventManager::LoadUsers() {
	// Read in users from csv file
	std::ifstream file("users.csv");
	if (!file.is_open()) {
			std::cerr << "[Error] Could not open users.csv\n";
			return;
	}

    std::string line;
		// skip the first header line
    bool firstLine = true;
		// while loop to read through each line
    while (std::getline(file, line)) {
			if (line.empty()) continue;
			if (firstLine) { firstLine = false; continue; }

			std::stringstream ss(line);
			std::string user_id_str, username, email, password, user_type, balance_str;

			std::getline(ss, user_id_str, ',');
			std::getline(ss, username, ',');
			std::getline(ss, email, ',');
			std::getline(ss, password, ',');
			std::getline(ss, user_type, ',');
			std::getline(ss, balance_str, ',');

			// Convert if line contains number 
			if (!std::all_of(user_id_str.begin(), user_id_str.end(), ::isdigit) || !std::all_of(balance_str.begin(), balance_str.end(), [](char c) { 
					return ::isdigit(c) || c=='.'; })) {
					std::cerr << "[Warning] Skipping invalid line: " << line << "\n";
					continue;
			}

			int user_id = std::stoi(user_id_str);
			float balance = std::stof(balance_str);

			auto user = std::make_shared<User>();
			user->SetUserID(user_id);
			user->SetUsername(username);
			user->SetEmail(email);
			user->SetPassword(password);
			user->SetUserType(user_type);
			user->SetAccountBalance(balance);
			// add user to users_ vector
			users_.push_back(user);
    }

    // Print users
    for (const auto& user : users_) {
			std::cout << "ID: " << user->GetUserID()
				<< ", Username: " << user->GetUsername()
				<< ", Email: " << user->GetEmail()
				<< ", Type: " << user->GetUserType()
				<< ", Balance: " << user->GetAccountBalance() << "\n";
    }
}

/**
  Loads Events from csv file
*/
void EventManager::LoadEvents() {
	// Read in events from CSV file
	std::ifstream file("events.csv");
	if (!file.is_open()) {
		std::cerr << "[Error] Could not open events.csv\n";
		return;
	}
	
    std::string line;
    bool firstLine = true;
    while (std::getline(file, line)) {
			if (line.empty()) continue;
			if (firstLine) { 
				firstLine = false; 
				continue; 
			}
			std::stringstream ss(line);
			std::string event_id_str, event_name, category, organizer_id_str;
			std::string base_ticket_price_str, total_tickets_str, sold_tickets_str;
			std::string ticket_tier, ticket_status;
			
			std::getline(ss, event_id_str, ',');
			std::getline(ss, event_name, ',');
			std::getline(ss, category, ',');
			std::getline(ss, organizer_id_str, ',');
			std::getline(ss, base_ticket_price_str, ','); 
			std::getline(ss, total_tickets_str, ',');
			std::getline(ss, sold_tickets_str, ',');
			std::getline(ss, ticket_tier, ',');
			std::getline(ss, ticket_status);  
        
        // Validate numeric fields
        if (event_id_str.empty() || organizer_id_str.empty() || base_ticket_price_str.empty() || total_tickets_str.empty() || sold_tickets_str.empty()) {
	        continue;
        }
        
        // Validate numeric strings with digits and '.'
        if (!std::all_of(event_id_str.begin(), event_id_str.end(), ::isdigit) || !std::all_of(organizer_id_str.begin(), organizer_id_str.end(), ::isdigit) || !std::all_of(total_tickets_str.begin(), total_tickets_str.end(), ::isdigit) || !std::all_of(sold_tickets_str.begin(), sold_tickets_str.end(), ::isdigit)) {
          continue;
        }
        
			// Validate format 
			bool valid_price = std::all_of(base_ticket_price_str.begin(), base_ticket_price_str.end(), [](char c) { return ::isdigit(c) || c == '.'; });
			if (!valid_price) {
				continue;
			}
        
        try {
					// Convert strings to numbers
					int event_id = std::stoi(event_id_str);
					int organizer_id = std::stoi(organizer_id_str);
					float base_ticket_price = std::stof(base_ticket_price_str);
					int total_tickets = std::stoi(total_tickets_str);
					int sold_tickets = std::stoi(sold_tickets_str);
					
					auto event = std::make_shared<Event>();
					event->SetEventID(event_id);
					event->SetEventName(event_name);
					event->SetCategory(category);
					event->SetOrganizerID(organizer_id);
					event->SetBaseTicketPrice(base_ticket_price);
					event->SetTotalTickets(total_tickets);
					event->SetSoldTickets(sold_tickets);
					event->SetTicketTier(ticket_tier);
					event->SetTicketStatus(ticket_status);
					
					events_.push_back(event);
        } catch (const std::exception& e) {
          continue;
        }
    }
    
    // Print events
    std::cout << "\nLoaded " << events_.size() << " events:\n";
    for (const auto& event : events_) {
			std::cout << "ID: " << event->GetEventID()
								<< ", Name: " << event->GetEventName()
								<< ", Category: " << event->GetCategory()
								<< ", Organizer ID: " << event->GetOrganizerID()
								<< ", Base Price: $" << event->GetBaseTicketPrice()
								<< ", Total Tickets: " << event->GetTotalTickets()
								<< ", Sold: " << event->GetSoldTickets()
								<< ", Tier: " << event->GetTicketTier()
								<< ", Status: " << event->GetTicketStatus()
								<< "\n";
    }
}

/**
	Processes a ticket purchse
	
	@params eventID, userID, quantity, tier
*/
void EventManager::ProcessTicketPurchase(int eventID, int userID, int quantity, std::string tier) 
{
	auto event = GetEventByID(eventID);
	// Check that event exists
	if (!event) {
		std::cout << "Event not found.\n";
		return;
	}
	// Check that sales are currently active for event
	if (!event->isSalesActive()) {
		std::cout << "Sales are not active for this event.\n";
		return;
	}
	if (event->GetTicketStatus() == "SoldOut") {
		std::cout << "Sorry - This event is sold out.\n";
		return;
	}
	// Check that there are enough tickets for user to purchase desired quantity
	int available = event->GetTotalTickets() - event->GetSoldTickets();
	if (available < quantity) {
		std::cout << "[Error] Not enough tickets available. Only " << available << " left.\n";
		return;
	}

	float base_price = event->GetTicketPrice();
	float tierFees = 1.0f;
	if (tier == "Standard") {
		tierFees = 1.0f;
	} else if (tier == "VIP") {
		tierFees = 2.0f;
	} else if (tier == "Premium") {
		tierFees = 3.0f;
	}

	// Calculate ticket cost with tier fee
	float ticketCostPlusTierFee = base_price * tierFees;
	
	// Calculate Attendee fee
	float attendeeFee = ticketCostPlusTierFee * 0.03f;

	// Total cost per individiual ticket with all fees
	float totalCostPerTicket = ticketCostPlusTierFee + attendeeFee;

	// Total cost of all tickets based on quantity desires
	float totalCost = totalCostPerTicket * quantity;

	// Get current user
	std::shared_ptr<User> attendee = nullptr;
	std::shared_ptr<User> organizer = nullptr;

	 for (const auto& user : users_) {
		if (user->GetUserID() == userID) {
			attendee = user;
		}
		if (user->GetUserID() == event->GetOrganizerID()) {
			organizer = user;
		}
	}

	// Check balance of attendee to ensure they have enough funds to cover desired quantity of tickets
	if (attendee->GetAccountBalance() < totalCost) {
		std::cout << "You do not have enough funds to cover this purchase";
		return;
	}

	// Process the transaction
	float organizerFee = base_price * 0.05f;
	float organizerPayout = (base_price - organizerFee)  * quantity;

	// Update both attendee and organizer accounts
	attendee->UpdateAccountBalance(totalCost);
  if (organizer) {
	  organizer->SetAccountBalance(organizer->GetAccountBalance() + organizerPayout);
    }

	// Update the number of tickets available
	event->SetSoldTickets(event->GetSoldTickets() + quantity);

	// Update Ticket Status if it applies
	if (event->GetSoldTickets() >= event->GetTotalTickets()) {
		event->SetTicketStatus("SoldOut");
		event->CloseEvent();
  } else if (event->GetTotalTickets() - event->GetSoldTickets() <= 20) {
	  event->SetTicketStatus("Limited");
  }

	// Display the transaction details
	std::cout << "\n--- Transaction Successful: ---\n";
	std::cout << "Event: " << event->GetEventName() << "\n";
	std::cout << "Quantity: " << quantity << "\n";
	std::cout << "Tier: " << tier << "\n";
	std::cout << "Ticket Price (each): $" << totalCostPerTicket << "\n";
	std::cout << "Service Fee (each): $" << attendeeFee << "\n";
	std::cout << "Total Cost: $" << totalCost << "\n";
	std::cout << "Remaining Balance: $" << attendee->GetAccountBalance() << "\n";
	std::cout << "Transaction ID: " << ++transactionID_ << "\n";
	std::cout << "-----------------------------\n";
}
	

/**
	Retrieves an event by ID
	
	@params event ID
	@returns event matching ID
*/
std::shared_ptr<Event> EventManager::GetEventByID(int id) {
	for (const auto& event : events_) {
		if (event->GetEventID() == id) {
			return event;
		}
  }
  return nullptr;
}

/**
	Generates an unique ID for an event

	@return a unique identifier for an event
*/
int EventManager::GenerateEventID() {
	int randomNum = rand() % 101;

	return randomNum;
}


/**
	Generates a transaction ID

	@return a unique identifier for a transaction 
*/
int EventManager::GenerateUserID() {
	int randomNum = rand() % 101;

	return randomNum;
}


/**
	Retrieve list of all users

	@return list of all users 
*/
std::vector<std::shared_ptr<User>> EventManager::GetAllUsers() const {
	return users_;
}

/**
	Retrieve list of all events

	@return list of all events 
*/
std::vector<std::shared_ptr<Event>> EventManager::GetAllEvents() const {
	return events_;
}

/**
	Update a user account

	@params userID, pointer to list of users 
*/
void EventManager::UpdateUser(int userID, const std::shared_ptr<User>& updatedUser) {
	for (auto& user : users_) {
		if (user->GetUserID() == userID) {
			user->SetEmail(updatedUser->GetEmail());
			user->SetUsername(updatedUser->GetUsername());
			user->SetPassword(updatedUser->GetPassword());
			user->SetAccountBalance(updatedUser->GetAccountBalance());
			break;
		}
	}
}