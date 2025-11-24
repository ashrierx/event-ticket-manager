# event-ticket-manager
The Event Management System is a comprehensive C++ application that simulates a ticket booking platform similar to Ticketmaster or Eventbrite. The system allows organizers to create and manage events while attendees can browse and purchase tickets with a transparent fee structure.

## Features 
User Management:
- Two User Types: Attendees (ticket buyers) and Organizers (event creators)
- User Registration: Create new accounts with username, email, password, and starting balance
- User Authentication: Secure login system with email and password validation
- Account Updates: Modify email, username, or password
Balance Management: Track fictional account balances for transactions

Event Management: 
- Event Creation: Organizers can create events with custom pricing and capacity
- Event Categories: Support for 5+ categories (Music, Sports, Theater, Conference, Outdoors)
- Event Types: Multiple specific event types (Concert, Festival, Game, Tournament, Play, Musical, etc.)
- Ticket Tiers: Standard, Premium, and VIP pricing options
- Sales Control: Organizers can open/close event sales
- Event Status: Automatic status updates (Available, Limited, SoldOut, Closed)

Ticket Purchasing:
- Browse Events: View all available events with details
- Multi-Ticket Purchase: Buy multiple tickets in a single transaction
- Tier Selection: Choose from Standard (1x), Premium (1.5x), or VIP (2x) pricing
- Real-Time Validation: Check ticket availability and user balance

*For now, the roles are CASE SENSITIVE when logging in - ensure you use 'Attendee' or 'Organizer'*

## System Architecture

#### Singleton Pattern
The EventManager class implements the Singleton pattern, ensuring only one instance manages all events and users throughout the application.

#### Factory Pattern
The EventFactory creates appropriate event objects based on category, implementing three levels of inheritance:

- Level 1: Base Event class
- Level 2: Category classes (Music, Sports, Theater, Conference, Outdoors)
- Level 3: Specific event types (ConcertEvent, GameEvent, PlayEvent, etc.)

#### Inheritance 
User system uses inheritance with a base User class and derived Attendee and Organizer classes, each with specialized functionality.


## Installation 
Prerequisites:

- C++ compiler with C++17 support (g++, clang++)
Make build system
- Catch2 testing framework (included as catch.hpp)

#### Build Instructions

- Clone or download the repository
- run `make` to build
- run `./main` to run the application 
- run `make test` `./test_runner` to run tests
- run `make clean` to clean build files 


## Future Enhancements
Potential features for future versions:

🔄 Persistent storage (save changes to CSV)<br />
🎫 Ticket resale marketplace<br />
📅 Event date/time management<br />
🔍 Advanced event search and filtering<br />
📊 Analytics dashboard for organizers<br />
💳 Multiple payment methods<br />
🎟️ Ticket refund system<br />
⭐ Event ratings and reviews<br />
📧 Email notifications<br />
🌐 Web interface<br />