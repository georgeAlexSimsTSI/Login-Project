#include "../include/loginSystem.h"

bool LoginSystem::addUser(const User &newUser) noexcept
{
    auto userName = newUser.getName().get();

    // check if there is already a user by this name in the map
    if (users.find(userName) != users.end())
    {
        return false;
    }

    users[userName] = std::make_shared<User>(newUser);

    return true;
}

// redo this later to add password requirement checks
void LoginSystem::addNewUser() noexcept
{
    system("cls");
    std::string userName, userPassword, userSecret;
    std::string userNamePrompt, userPasswordPrompt, userSecretPrompt;

    userNamePrompt = "Enter the user name: ";
    userPasswordPrompt = "Enter your password: ";
    userSecretPrompt = "Enter your secret: ";

    userInput::validateInput(userName, userNamePrompt);
    userInput::validateInput(userPassword, userPasswordPrompt);
    userInput::validateInput(userSecret, userSecretPrompt);

    User user = User(userName_t{userName}, userPassword_t{userPassword}, userSecret_t{userSecret});

    if (addUser(user))
    {
        std::cout << "Account has been created \n";
    }
    else
    {
        std::cout << "User name already in use \n";
    }
}

void LoginSystem::removeUser(const userName_t &userName) noexcept
{
    auto name = userName.get();
    users.erase(name); // if there is no such user nothing will happen
}

std::shared_ptr<User> LoginSystem::userLogIn(const userName_t &userName, const userPassword_t &userPassword) noexcept
{
    auto userNameString = userName.get();

    // check if there is already a user by this name in the map
    if (users.find(userNameString) == users.end())
    {
        std::cout << "No such user exists " << '\n'; // may remove this for security reasons
        return nullptr;
    }

    auto user = users[userNameString];

    if (user.get()->logIn(userPassword))
    {
        return user;
    }

    std::cout << "Incorrect Password \n";
    return nullptr;
}

void LoginSystem::userMenu(std::shared_ptr<User> &user) // may make changes to it later so for now its not const
{
    system("cls");
    // will add more options here later
    auto name = user->getName();
    auto secret = user->getSecret();
    std::cout << "User: " << name.get() << "'s great secret is: " << secret.get() << "\n";
}

void LoginSystem::adminMenu(std::shared_ptr<User> &user)
{
    // unimplemented
}

void LoginSystem::loginScreen()
{
    system("cls");
    std::cout << "Welcome to the login screen: \n";
    std::string userName, userPassword;
    std::string namePrompt = "Please enter your username: ";
    std::string passwordPrompt = "Please enter your password: ";

    userInput::validateInput(userName, namePrompt);
    userInput::validateInput(userPassword, passwordPrompt);

    auto user = userLogIn(userName_t{userName}, userPassword_t{userPassword});

    if (user == nullptr)
    {
        return;
    }

    if (user->isAdmin())
        adminMenu(user);
    else
        userMenu(user);
}

void LoginSystem::run()
{
    std::cout << "Welcome to the secret database: \n";

    bool loopCondition = true;
    while (loopCondition)
    {
        system("cls");
        std::string inputMessage = "To attempt a login enter 1: \nTo add a new user enter 2: \nTo exit the application enter 3: \nInput: ";
        int userInput = 0;
        userInput::validateInput(userInput, inputMessage);

        switch (userInput)
        {
        case 1:
            loginScreen();
            break;
        case 2:
            addNewUser();
            break;
        case 3:
            loopCondition = false;
            break;
        default:
            std::cout << "Unrecognized choice\n";
        }
        system("pause"); // for output formatting, will change later        
    }
    std::cout << "Good bye";
}
