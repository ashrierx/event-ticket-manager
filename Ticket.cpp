// Ticket implemntation file

#include "Ticket.h"
#include <string>

/**
	Get the price of a ticket  based on tier

	@returns price of one ticket
*/
float Ticket::GetTicketPrice() {
	// TODO: adjust price based on tier
	return ticket_price_;
}

/**
	Sets the tier of a ticket

	@params ticket tier
*/
void Ticket::SetTicketTier(std::string tier) {
	tier_ = tier;
}

/**
	Get the current status of a ticket

	@returns status of one ticket
*/
std::string Ticket::GetTicketStatus() {
	return status_;
}

/**
    Calculate the fees associated with the ticket for the attendee to pay

		@params basePrice
*/
// float CalculateAttendeeFee(std::string tier) {
// 	// service fee of 3%
// 	return ticket_price_ * .03f; 
// }

// /**
//     Calculate net price owed to organizer after ticket purchase

// 		@params basePrice
// */
// float CalculateOrganizerFee(std::string tier) {
// 	return ticket_price_ - .03f;
// }