// User implementation file

#include "User.h"
#include <iostream>

/**
	Logs a user in
	
	@params email, password
	@returns true if user found, false if no user found
*/
bool User::Login(std::string email, std::string password) {
	if(email == email_ && password == password_) {
		return true;
	}
	return false;
}


/**
	Get the type of user logged in

	@returns type of user (attendee or organizer)
*/
std::string User::GetUserType() const {
	return user_type_;
}


/**
	Get account balance

	@returns current user account balance
*/
float User::GetAccountBalance() {
	return account_balance_;
}


/**
	Update account balance

	@params amount to deduct from account
*/
void User::UpdateAccountBalance(float amount) {
	account_balance_ -= amount;
}

/**
  Show transaction details after a ticket is purchased
*/		
void User::DisplayTransactionDetails() {
	std::cout << "Showing transaction details for " << username_ << std::endl;
}