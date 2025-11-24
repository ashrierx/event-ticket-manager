// User header file - INHERITANCE

#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>

// Base class User
class User {
	public: 
		virtual ~User() = default;

		// Log a user in
		bool Login(std::string email, std::string password);

		// Get the type of user logged in
		std::string GetUserType() const;

		// Get account balance
		float GetAccountBalance();

		// Update a user account balance
		void UpdateAccountBalance(float amount);

		// Display Transaction details after a purchase
		void DisplayTransactionDetails();

		// Setters
    void SetUserID(int id) { userID_ = id; }
    void SetUsername(const std::string& name) { username_ = name; }
    void SetEmail(const std::string& email) { email_ = email; }
    void SetPassword(const std::string& password) { password_ = password; }
    void SetUserType(const std::string& type) { user_type_ = type; }
    void SetAccountBalance(float balance) { account_balance_ = balance; }

    // Getters
    int GetUserID() { return userID_; }
    std::string GetUsername() { return username_; }
    std::string GetEmail() { return email_; }
    std::string GetPassword() { return password_; }

	private: 
		int userID_;
		std::string username_;
		std::string email_;
		std::string password_;
		std::string user_type_;
		float account_balance_;
};

#endif // USER_H

