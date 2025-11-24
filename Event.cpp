// Event implementation file

#include "Event.h"
#include <string>

Event::Event(int id, 
	 const std::string& category, 
	 const std::string& name, 
	 float base_price, 
	 int total_tickets, 
	 const std::string& tier, 
	 int organizer_id)
	: event_id_(id), 
		event_name_(name), 
		category_(category), 
		base_price_(base_price),
		total_tickets_(total_tickets), 
		sold_tickets_(0),
		ticket_tier_(tier),
		organizer_id_(organizer_id),
		ticket_status_("Active"),
		tickets_purchased_(0),
		available_ticket_(total_tickets), 
		sales_active_(true),
		is_completed_(false)
{
	
}

#include "Event.h"

/**
	Get the category type of the event

	@params eventID
	@returns the category type
*/
std::string Event::GetEventCategory(int eventID) {
	return category_;
}

/**
	Get the category type of the event

	@returns the base ticket price
*/
float Event::GetTicketPrice() {
	return base_price_;
}

/**
	Checks if ticket sales are still active

	@returns true if tickets are still being sold, false if not
*/
bool Event::isSalesActive() {
	return sales_active_;
}


/**
  Close a currently active event
*/
void Event::CloseEvent() {
	sales_active_ = false;
}


/**
  Reopens a currently closed event
*/
void Event::ReopenEvent() {
	sales_active_ = true;
}