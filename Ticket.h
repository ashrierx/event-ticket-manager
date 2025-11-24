// Ticket header file

#include <string>

class Ticket {
	public:
		// Get the ticket price 
		float GetTicketPrice();

		// set the ticket tier
		void SetTicketTier(std::string tier);

		// Get the status of a ticket
		std::string GetTicketStatus();

		// Calculate attenddee fee
		float CalculateAttendeeFee(std::string tier);

		// Calculate organizer fees
		float CalculateOrganizerFee(std::string tier);

	private:
		int ticketID_;
		int eventID_;
		std::string tier_;
		std::string status_;
		float ticket_price_;
};