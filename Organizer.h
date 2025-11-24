// Organizer header file - INHERITANCE - FACTORY PATTERN TO CREATE EVENT OBJECT

#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "User.h"
#include <vector>
#include <memory>

class Event;
class EventManager;

// Derived Organizer class
class Organizer : public User {
	public:
    // Main menu interface for organizer
    void ShowOrganizerInterface();

		// Create a new event (Factory pattern)
		std::shared_ptr<Event> CreateNewEvent(const std::string& category, const std::string& name, float basePrice, int totalTickets, const std::string& tier);

		// Close an event after date or tickets sell out
		void CloseEvent(int eventID);

		// Reopen an event if more tickets become available after closing
		void ReopenEvent(int eventID);

		// View a list of all events, past and present
		void ViewAllEvents();

		// View menu options to choose from
		void DisplayDashboard();


	private:
		std::vector<int> eventIDs_;
		// bool has_active_event_;
		void DisplayOrganizerMenu();
};

#endif // ORGANIZER_H
