// Attendee header file - INHERITANCE

#ifndef ATTENDEE_H
#define ATTENDEE_H

#include "User.h"
#include <vector>

// Derived Attendee class
class Attendee : public User {
	public: 
		// Main menu interface for attendee
		void ShowAttendeeInterface();

		// Purchase a ticket to an event
		void PurchaseTicket(int eventID, int quantity, std::string tier);

		// view all tickets past and present
		void ViewTickets(int attendeeID);

		// view transaction history of tickets with breakdown of costs
		void ViewTransactionHistory(int attendeeID);

		// Display users tickets and account balance
		void DisplayDashboard(int attendeeID);

	private:
		std::vector<int> ticketIDs_;
		bool has_tickets_ = false;
		int attendeeID_;
		void DisplayAttendeeMenu();
};

#endif // ATTENDEE_H