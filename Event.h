// Event header file - FACTORY PATTERN TO CREATE EVENT OBJECT

#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
	public:
		Event() = default;

		Event(int id, 
			const std::string& category, 
			const std::string& name, 
			float base_price, 
			int total_tickets, 
			const std::string& tier, 
			int organizer_id);

		// Get category of event
		std::string GetEventCategory(int eventID);

		// Get ticket price of event
		float GetTicketPrice();

		// Are sales still active for event
		bool isSalesActive();

		// Close an event after date or no more tickets available
		void CloseEvent();

		// Reopen a currently closed event
		void ReopenEvent();

    int GetEventID() const { return event_id_; }
    std::string GetEventName() const { return event_name_; }
    std::string GetCategory() const { return category_; }
    int GetOrganizerID() const { return organizer_id_; }
    float GetBaseTicketPrice() const { return base_price_; }
    int GetTotalTickets() const { return total_tickets_; }
    int GetSoldTickets() const { return sold_tickets_; }
    std::string GetTicketTier() const { return ticket_tier_; }
    std::string GetTicketStatus() const { return ticket_status_; }
    int GetTicketsPurchased() const { return tickets_purchased_; }

    void SetEventID(int id) { event_id_ = id; }
    void SetEventName(const std::string& name) { event_name_ = name; }
    void SetCategory(const std::string& cat) { category_ = cat; }
    void SetOrganizerID(int id) { organizer_id_ = id; }
    void SetBaseTicketPrice(float price) { base_price_ = price; }
    void SetTotalTickets(int total) { total_tickets_ = total; }
    void SetSoldTickets(int sold) { sold_tickets_ = sold; }
    void SetTicketTier(const std::string& tier) { ticket_tier_ = tier; }
    void SetTicketStatus(const std::string& status) { ticket_status_ = status; }
    void SetTicketsPurchased(int purchased) { tickets_purchased_ = purchased; }

	private:
	  int event_id_;
    std::string event_name_;
    std::string category_;
    float base_price_; 
    int total_tickets_;
    int sold_tickets_;
    std::string ticket_tier_; 
    int organizer_id_; 
    std::string ticket_status_;
    int tickets_purchased_;
    int available_ticket_; 
    bool sales_active_ = true;
    bool is_completed_ = false;
};

#endif // EVENT_H