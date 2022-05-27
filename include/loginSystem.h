#ifndef LOGIN_SYSTEM_H
#define LOGIN_SYSTEM_H

#include <map>
#include <string>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <functional>

#include "./user.h"
#include "./userInput.h"

#include <json.hpp>
using json = nlohmann::json;

class LoginSystem
{
private:
    // usernames and the User instance
    std::map<std::string, std::shared_ptr<User>> users;

    std::string fileName;

    /**
     * @brief method that takes an already constructed user and adds it to the system
     *
     * @param newUser
     * @return true if the new user was added
     * @return false if the user was not added, username already taken
     */
    bool addUser(const User &newUser) noexcept;

    /**
     * @brief Take new user details
     *
     */
    void addNewUser() noexcept;

    /**
     * @brief method to remove a user from the map
     *
     * @param user the user to be removed
     */
    void removeUser(const userName_t &userName) noexcept;

    /**
     * @brief method that takes in a userName and userPassword and returns a shared pointer to the user
     *
     * @param userName the user name
     * @param userPassword the entered password
     * @return std::shared_ptr<User> if there is no such user or if the password is incorrect will return a nullptr
     */
    std::shared_ptr<User> userLogIn(const userName_t &userName, const userPassword_t &userPassword) noexcept;

    /**
     * @brief will display menu for the user and call relevant methods based on inputs
     *
     * @param user
     */
    void userMenu(std::shared_ptr<User> user);

    /**
     * @brief will display menu for the user and call relevant methods based on inputs
     *
     * @param user
     */
    void adminMenu(std::shared_ptr<User> user);

    /**
     * @brief will take user inputs and attempt to login, if successful it will then call the relevant menu
     *
     */
    void loginScreen() noexcept;

    /**
     * @brief Takes the current map of users constructs a Json representation and then writes this to a file
     */
    void saveToFile() noexcept;

    /**
     * @brief Tries to open the file that was designated at construction and pipe the contents of this file into a json object.
     * using this json object we then populate the users map. If this fails then the users map is left blank.
     */
    void loadFromFile() noexcept;

    /**
     * @brief Prints the usernames of everyone currently stored in the system
     */
    void listUsers() noexcept;

    /**
     * @brief Method that allows a user to change their password. It cant be the same as the previous password.
     *
     * @param user The user that is changing their password.
     */
    void changePassword(const std::shared_ptr<User> &user) noexcept;

    std::shared_ptr<User> selectUser() noexcept;

public:
    explicit LoginSystem(const std::string &fileName) : fileName(fileName) { loadFromFile(); };
    LoginSystem() : LoginSystem("users.json"){};
    ~LoginSystem() { saveToFile(); }
    LoginSystem(LoginSystem &&) = default;

    /**
     * @brief main loop of the program that takes user input and calls relevant methods
     *
     */
    void run();
};

#endif