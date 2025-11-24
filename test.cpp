// Test cases file
// Comprehensive list of tests for creating a singleton event, creating a new user, user login, creating an event, closing and reopening an event, purchasing tickets, updating ticket status, fee payouts, updating accout balances, retrieving correct events


#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "EventManager.h"
#include "User.h"
#include "Organizer.h"
#include "Attendee.h"
#include "Event.h"
#include "EventFactory.h"
#include <memory>

TEST_CASE("EventManager Singleton", "[EventManager]")
{
	SECTION("Single instance created") {
		EventManager* em1 = EventManager::GetInstance();
		EventManager* em2 = EventManager::GetInstance();
		REQUIRE(em1 == em2);
		REQUIRE(em1 != nullptr);
	}
}

TEST_CASE("User Registration", "[User][Registration]")
{
  EventManager* em = EventManager::GetInstance();
    
	SECTION("Register valid Attendee") {
		auto attendee = std::make_shared<Attendee>();
		int userID = em->GenerateUserID();
		attendee->SetUserID(userID);
		attendee->SetUsername("testuser");
		attendee->SetEmail("test@example.com");
		attendee->SetPassword("password123");
		attendee->SetUserType("Attendee");
		attendee->SetAccountBalance(1000.0f);
		
		em->RegisterUser(attendee);
		auto users = em->GetAllUsers();
		
		bool found = false;
		for (const auto& user : users) {
			if (user->GetUserID() == userID) {
				found = true;
				REQUIRE(user->GetUsername() == "testuser");
				REQUIRE(user->GetEmail() == "test@example.com");
				REQUIRE(user->GetUserType() == "Attendee");
				REQUIRE(user->GetAccountBalance() == 1000.0f);
			}
		}
			REQUIRE(found == true);
    }
    
    SECTION("Register valid Organizer") {
			auto organizer = std::make_shared<Organizer>();
			int userID = em->GenerateUserID();
			organizer->SetUserID(userID);
			organizer->SetUsername("eventorg");
			organizer->SetEmail("org@example.com");
			organizer->SetPassword("orgpass123");
			organizer->SetUserType("Organizer");
			organizer->SetAccountBalance(5000.0f);
			
			em->RegisterUser(organizer);
			auto users = em->GetAllUsers();
			
			bool found = false;
			for (const auto& user : users) {
					if (user->GetUserID() == userID) {
							found = true;
							REQUIRE(user->GetUsername() == "eventorg");
							REQUIRE(user->GetUserType() == "Organizer");
					}
			}
			REQUIRE(found == true);
    }
}

TEST_CASE("User Login", "[User][Login]")
{
	SECTION("Login with correct credentials") {
		auto user = std::make_shared<User>();
		user->SetEmail("login@test.com");
		user->SetPassword("correctpass");
		
		bool loginSuccess = user->Login("login@test.com", "correctpass");
		REQUIRE(loginSuccess == true);
	}
	
	SECTION("Login with incorrect password") {
		auto user = std::make_shared<User>();
		user->SetEmail("login@test.com");
		user->SetPassword("correctpass");
		
		bool loginFail = user->Login("login@test.com", "wrongpass");
		REQUIRE(loginFail == false);
	}
	
	SECTION("Login with incorrect email") {
		auto user = std::make_shared<User>();
		user->SetEmail("login@test.com");
		user->SetPassword("correctpass");
		
		bool loginFail = user->Login("wrong@test.com", "correctpass");
		REQUIRE(loginFail == false);
	}
	
	SECTION("Login with empty credentials") {
		auto user = std::make_shared<User>();
		user->SetEmail("login@test.com");
		user->SetPassword("correctpass");
		
		bool loginFail = user->Login("", "");
		REQUIRE(loginFail == false);
	}
}

TEST_CASE("Event Creation", "[Event][Creation]")
{
	EventManager* em = EventManager::GetInstance();
	
	SECTION("Create valid Music event") {
		auto event = em->CreateEvent("Music", "Rock Concert", 100.0f, 500, "Standard", 1);
		
		REQUIRE(event != nullptr);
		REQUIRE(event->GetEventName() == "Rock Concert");
		REQUIRE(event->GetCategory() == "Music");
		REQUIRE(event->GetBaseTicketPrice() == 100.0f);
		REQUIRE(event->GetTotalTickets() == 500);
		REQUIRE(event->GetSoldTickets() == 0);
		REQUIRE(event->GetTicketTier() == "Standard");
	}
	
	SECTION("Create valid Sports event") {
		auto event = em->CreateEvent("Sports", "Championship Game", 200.0f, 1000, "VIP", 2);
		
		REQUIRE(event != nullptr);
		REQUIRE(event->GetEventName() == "Championship Game");
		REQUIRE(event->GetCategory() == "Sports");
		REQUIRE(event->GetBaseTicketPrice() == 200.0f);
		REQUIRE(event->GetTotalTickets() == 1000);
	}
}

TEST_CASE("Event Factory Pattern", "[Event][Factory]")
{
	SECTION("Create Concert event") {
		auto event = EventFactory::CreateEvent(1, "Concert", "Rock Show", 100.0f, 500, "Standard", 1);
		REQUIRE(event != nullptr);
		REQUIRE(event->GetCategory() == "Music");
	}
	
	SECTION("Create Game event") {
		auto event = EventFactory::CreateEvent(2, "Game", "NBA Finals", 200.0f, 1000, "VIP", 2);
		REQUIRE(event != nullptr);
		REQUIRE(event->GetCategory() == "Sports");
	}
	
	SECTION("Create unknown event defaults to base Event") {
		auto event = EventFactory::CreateEvent(3, "Unknown", "Mystery Event", 50.0f, 100, "Standard", 3);
		REQUIRE(event != nullptr);
		REQUIRE(event->GetCategory() == "Unknown");
	}
}

TEST_CASE("Event Sales Status", "[Event][Sales]")
{
	SECTION("New event has active sales") {
		Event event(1, "Music", "Concert", 100.0f, 500, "Standard", 1);
		REQUIRE(event.isSalesActive() == true);
	}
	
	SECTION("Close event sales") {
		Event event(1, "Music", "Concert", 100.0f, 500, "Standard", 1);
		event.CloseEvent();
		REQUIRE(event.isSalesActive() == false);
	}
	
	SECTION("Reopen event sales") {
		Event event(1, "Music", "Concert", 100.0f, 500, "Standard", 1);
		event.CloseEvent();
		event.ReopenEvent();
		REQUIRE(event.isSalesActive() == true);
	}
}

TEST_CASE("Ticket Purchase - Valid Cases", "[Ticket][Purchase]")
{
	EventManager* em = EventManager::GetInstance();
	
	SECTION("Purchase single Standard ticket with sufficient funds") {
		// Create attendee
		auto attendee = std::make_shared<Attendee>();
		int userID = em->GenerateUserID();
		attendee->SetUserID(userID);
		attendee->SetUsername("buyer1");
		attendee->SetEmail("buyer1@test.com");
		attendee->SetPassword("pass");
		attendee->SetUserType("Attendee");
		attendee->SetAccountBalance(1000.0f);
		em->RegisterUser(attendee);
		
		// Create organizer
		auto organizer = std::make_shared<Organizer>();
		int orgID = em->GenerateUserID();
		organizer->SetUserID(orgID);
		organizer->SetUsername("seller1");
		organizer->SetEmail("seller1@test.com");
		organizer->SetPassword("pass");
		organizer->SetUserType("Organizer");
		organizer->SetAccountBalance(0.0f);
		em->RegisterUser(organizer);
		
		// Create event
		auto event = em->CreateEvent("Music", "Concert", 100.0f, 500, "Standard", orgID);
		int eventID = event->GetEventID();
		
		// Purchase ticket
		float initialBalance = attendee->GetAccountBalance();
		em->ProcessTicketPurchase(eventID, userID, 1, "Standard");
		
		// Verify ticket was sold
		auto updatedEvent = em->GetEventByID(eventID);
		REQUIRE(updatedEvent->GetSoldTickets() == 1);
			
		// Verify attendee balance decreased
		auto users = em->GetAllUsers();
		for (const auto& user : users) {
			if (user->GetUserID() == userID) {
				float expectedCost = 100.0f * 1.0f * 1.03f;
				REQUIRE(user->GetAccountBalance() < initialBalance);
				REQUIRE(user->GetAccountBalance() == Approx(initialBalance - expectedCost).epsilon(0.01));
			}
		}
	}
    
	SECTION("Purchase Premium tier tickets") {
		auto attendee = std::make_shared<Attendee>();
		int userID = em->GenerateUserID();
		attendee->SetUserID(userID);
		attendee->SetAccountBalance(1500.0f);
		em->RegisterUser(attendee);
		
		auto organizer = std::make_shared<Organizer>();
		int orgID = em->GenerateUserID();
		organizer->SetUserID(orgID);
		organizer->SetAccountBalance(0.0f);
		em->RegisterUser(organizer);
		
		auto event = em->CreateEvent("Theater", "Play", 100.0f, 200, "Premium", orgID);
		int eventID = event->GetEventID();
		
		em->ProcessTicketPurchase(eventID, userID, 2, "Premium");
		
		auto updatedEvent = em->GetEventByID(eventID);
		REQUIRE(updatedEvent->GetSoldTickets() == 2);
	}
}

TEST_CASE("Ticket Purchase - Invalid Cases", "[Ticket][Purchase][Error]")
{
	EventManager* em = EventManager::GetInstance();
	
	SECTION("Purchase with insufficient funds") {
		auto attendee = std::make_shared<Attendee>();
		int userID = em->GenerateUserID();
		attendee->SetUserID(userID);
		attendee->SetAccountBalance(50.0f); // Not enough
		em->RegisterUser(attendee);
		
		auto organizer = std::make_shared<Organizer>();
		int orgID = em->GenerateUserID();
		organizer->SetUserID(orgID);
		em->RegisterUser(organizer);
		
		auto event = em->CreateEvent("Music", "Concert", 100.0f, 500, "Standard", orgID);
		int eventID = event->GetEventID();
		int initialSold = event->GetSoldTickets();
		
		em->ProcessTicketPurchase(eventID, userID, 1, "Standard");
		
		// Verify no tickets were sold
		auto updatedEvent = em->GetEventByID(eventID);
		REQUIRE(updatedEvent->GetSoldTickets() == initialSold);
	}
    
	SECTION("Purchase more tickets than available") {
		auto attendee = std::make_shared<Attendee>();
		int userID = em->GenerateUserID();
		attendee->SetUserID(userID);
		attendee->SetAccountBalance(10000.0f);
		em->RegisterUser(attendee);
		
		auto organizer = std::make_shared<Organizer>();
		int orgID = em->GenerateUserID();
		organizer->SetUserID(orgID);
		em->RegisterUser(organizer);
		
		auto event = em->CreateEvent("Sports", "Game", 100.0f, 10, "Standard", orgID);
		int eventID = event->GetEventID();
		
		em->ProcessTicketPurchase(eventID, userID, 20, "Standard"); // Try to buy 20, only 10 available
			
		// Verify no tickets were sold
		auto updatedEvent = em->GetEventByID(eventID);
		REQUIRE(updatedEvent->GetSoldTickets() == 0);
	}
    
	SECTION("Purchase from closed event") {
		auto attendee = std::make_shared<Attendee>();
		int userID = em->GenerateUserID();
		attendee->SetUserID(userID);
		attendee->SetAccountBalance(1000.0f);
		em->RegisterUser(attendee);
		
		auto organizer = std::make_shared<Organizer>();
		int orgID = em->GenerateUserID();
		organizer->SetUserID(orgID);
		em->RegisterUser(organizer);
		
		auto event = em->CreateEvent("Theater", "Play", 100.0f, 100, "Standard", orgID);
		int eventID = event->GetEventID();
		event->CloseEvent(); // Close sales
		
		em->ProcessTicketPurchase(eventID, userID, 1, "Standard");
		
		// Verify no tickets were sold
		REQUIRE(event->GetSoldTickets() == 0);
	}
    
	SECTION("Purchase from non-existent event") {
		auto attendee = std::make_shared<Attendee>();
		int userID = em->GenerateUserID();
		attendee->SetUserID(userID);
		attendee->SetAccountBalance(1000.0f);
		em->RegisterUser(attendee);
		
		int fakeEventID = 99999;
		
		em->ProcessTicketPurchase(fakeEventID, userID, 1, "Standard");
		
		REQUIRE(true);
	}
}

TEST_CASE("Event Status Updates", "[Event][Status]")
{
	EventManager* em = EventManager::GetInstance();
	
	SECTION("Event becomes SoldOut when all tickets purchased") {
		auto attendee = std::make_shared<Attendee>();
		int userID = em->GenerateUserID();
		attendee->SetUserID(userID);
		attendee->SetAccountBalance(10000.0f);
		em->RegisterUser(attendee);
		
		auto organizer = std::make_shared<Organizer>();
		int orgID = em->GenerateUserID();
		organizer->SetUserID(orgID);
		em->RegisterUser(organizer);
		
		auto event = em->CreateEvent("Music", "Small Show", 50.0f, 10, "Standard", orgID);
		int eventID = event->GetEventID();
		
		em->ProcessTicketPurchase(eventID, userID, 10, "Standard");
		
		auto updatedEvent = em->GetEventByID(eventID);
		REQUIRE(updatedEvent->GetTicketStatus() == "SoldOut");
		REQUIRE(updatedEvent->isSalesActive() == false);
	}
}

TEST_CASE("Organizer Payout", "[Transaction][Organizer]")
{
	EventManager* em = EventManager::GetInstance();
	
	SECTION("Organizer receives correct payout after sale") {
		auto attendee = std::make_shared<Attendee>();
		int userID = em->GenerateUserID();
		attendee->SetUserID(userID);
		attendee->SetAccountBalance(1000.0f);
		em->RegisterUser(attendee);
		
		auto organizer = std::make_shared<Organizer>();
		int orgID = em->GenerateUserID();
		organizer->SetUserID(orgID);
		organizer->SetAccountBalance(0.0f);
		em->RegisterUser(organizer);
		
		auto event = em->CreateEvent("Music", "Concert", 100.0f, 500, "Standard", orgID);
		int eventID = event->GetEventID();
		
		em->ProcessTicketPurchase(eventID, userID, 1, "Standard");
			
		auto users = em->GetAllUsers();
		for (const auto& user : users) {
				if (user->GetUserID() == orgID) {
						REQUIRE(user->GetAccountBalance() == Approx(95.0f).epsilon(0.01));
				}
		}
	}
}

TEST_CASE("Account Balance Updates", "[User][Balance]")
{
	SECTION("UpdateAccountBalance deducts correctly") {
		auto user = std::make_shared<User>();
		user->SetAccountBalance(1000.0f);
		
		user->UpdateAccountBalance(300.0f);
		REQUIRE(user->GetAccountBalance() == 700.0f);
	}
	
	SECTION("UpdateAccountBalance with full balance") {
		auto user = std::make_shared<User>();
		user->SetAccountBalance(500.0f);
		
		user->UpdateAccountBalance(500.0f);
		REQUIRE(user->GetAccountBalance() == 0.0f);
	}
	
	SECTION("SetAccountBalance updates correctly") {
		auto user = std::make_shared<User>();
		user->SetAccountBalance(1000.0f);
		REQUIRE(user->GetAccountBalance() == 1000.0f);
		
		user->SetAccountBalance(2000.0f);
		REQUIRE(user->GetAccountBalance() == 2000.0f);
	}
}

TEST_CASE("Event Retrieval", "[Event][Query]")
{
	EventManager* em = EventManager::GetInstance();
	
	SECTION("GetEventByID returns correct event") {
		auto event = em->CreateEvent("Music", "Test Concert", 100.0f, 500, "Standard", 1);
		int eventID = event->GetEventID();
		
		auto retrieved = em->GetEventByID(eventID);
		REQUIRE(retrieved != nullptr);
		REQUIRE(retrieved->GetEventID() == eventID);
		REQUIRE(retrieved->GetEventName() == "Test Concert");
	}
	
	SECTION("GetEventByID returns nullptr for invalid ID") {
		auto retrieved = em->GetEventByID(99999);
		REQUIRE(retrieved == nullptr);
	}
	
	SECTION("GetAllEvents returns all created events") {
		size_t initialCount = em->GetAllEvents().size();
		
		em->CreateEvent("Music", "Event 1", 50.0f, 100, "Standard", 1);
		em->CreateEvent("Sports", "Event 2", 75.0f, 200, "VIP", 1);
		em->CreateEvent("Theater", "Event 3", 90.0f, 150, "Premium", 1);
		
		auto allEvents = em->GetAllEvents();
		REQUIRE(allEvents.size() == initialCount + 3);
	}
}