// EventManager header file - SINGLETON

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "User.h"
#include "Event.h"
#include <vector>
#include <memory>


class EventManager {
	public: 
		// public static method to access single EventManager instance
		static EventManager* GetInstance() {
			if (instance == nullptr) {
				instance = new EventManager();
			}
			return instance;
		}

		// adds a new user to the system
		void RegisterUser(std::shared_ptr<User> user);

		// Add a new event to the system
		void AddEvent(std::shared_ptr<Event> event);

		// creates a new event
		std::shared_ptr<Event> CreateEvent(std::string category, std::string name, float basePrice, int totalTickets, std::string tier, int organizerID);

		// Load users
		void LoadUsers();

		// Load transactions
		void LoadEvents();

		// processes a ticket purchase 
		void ProcessTicketPurchase(int eventID, int userID, int quantity, std::string tier);

		// Retrieve a specific event by ID
		std::shared_ptr<Event> GetEventByID(int id);

		// // Generate a unique ID for an event
		int GenerateEventID();

		// // Generate a unique ID for a transaction
		int GenerateUserID();

		// return the list of users
		std::vector<std::shared_ptr<User>> GetAllUsers() const;

		// return list of all events
		std::vector<std::shared_ptr<Event>> GetAllEvents() const;

		// Update a user
		void UpdateUser(int userID, const std::shared_ptr<User>& updatedUser);

	private:
		static EventManager* instance;
		// EventManager() : eventID_(0), transactionID_(0) {};
		EventManager();
		int eventID_;
		int transactionID_;
		std::vector<std::shared_ptr<Event>> events_;
		std::vector<std::shared_ptr<User>> users_;
};

#endif // EVENTMANAGER_H
