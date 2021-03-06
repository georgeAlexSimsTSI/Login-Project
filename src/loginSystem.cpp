#include "../include/loginSystem.h"

bool LoginSystem::addUser(const User &newUser) noexcept
{
    auto userName = newUser.getName().get();

    // check if there is already a user by this name in the map
    if (users.find(userName) != users.end()) // users . contains
    {
        return false;
    }

    users[userName] = std::make_shared<User>(newUser);

    return true;
}

void LoginSystem::addNewUser() noexcept
{
    system("cls");
    std::string userName, userPassword, userSecret;
    std::string userNamePrompt, userSecretPrompt;

    userNamePrompt = "Enter the user name: ";
    userSecretPrompt = "Enter your secret: ";

    userInput::validateInput(userName, userNamePrompt);

    size_t userPasswordHash = userInput::enterPassword(0);

    std::cout << userSecretPrompt << "\n";
    std::getline(std::cin, userSecret);

    User user = User(userName_t{userName}, userPassword_t{userPasswordHash}, userSecret_t{userSecret});

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

void LoginSystem::userMenu(std::shared_ptr<User> user) // may make changes to it later so for now its not const
{
    system("cls");
    // will add more options here later
    auto name = user->getName();
    auto secret = user->getSecret();

    while (true)
    {
        std::string inputMessage = "To display your secret enter 1: \nTo change your password enter 2: \nTo delete your account enter 3: \nTo logout enter 4: \nInput: ";
        int userInput = 0;
        userInput::validateInput(userInput, inputMessage);

        switch (userInput)
        {
        case 1:
            // get users secret
            std::cout << "User: " << name.get() << "'s great secret is: " << secret.get() << "\n";
            break;
        case 2:
            // change password
            changePassword(user);
            break;
        case 3:
            // delete account
            users.erase(name.get());
        case 4:
            // exit
            return;
        default:
            std::cout << "Unrecognized choice\n";
        }
    }
}

void LoginSystem::adminMenu(std::shared_ptr<User> user)
{
    system("cls");
    auto name = user->getName();
    auto secret = user->getSecret();

    while (true)
    {
        std::string inputMessage = "To switch to normal user mode enter 1: \nTo unlock another users account enter 2: \nTo get access another users account enter 3: \nTo reset users password enter 4: \nTo exit enter 5: \nEnter:  ";
        int userInput = 0;
        userInput::validateInput(userInput, inputMessage);

        switch (userInput)
        {
        case 1:
            userMenu(user);
            return;
        case 2:
            // unlock a user account
            // unimplemented
            break;
        case 3:
            // access other users account
            userMenu(selectUser());
            break;
        case 4:
            // reset another users password
            changePassword(selectUser());
            break;
        case 5:
            // exit
            return;
        default:
            std::cout << "Unrecognized choice\n";
        }
    }
}

void LoginSystem::loginScreen() noexcept
{
    system("cls");
    std::cout << "Welcome to the login screen: \n";
    std::string userName, userPassword;
    std::string namePrompt = "Please enter your username: ";
    std::string passwordPrompt = "Please enter your password: ";

    userInput::validateInput(userName, namePrompt);
    userInput::validateInput(userPassword, passwordPrompt);

    size_t userPasswordHash = userInput::hashPassword(userPassword);

    auto user = userLogIn(userName_t{userName}, userPassword_t{userPasswordHash});

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
    }
    std::cout << "Good bye";
}

void LoginSystem::saveToFile() noexcept
{
    json j;

    int i = 0;
    for (auto &[userName, user] : users)
    {
        auto password = user->getPassword().get();
        auto secret = user->getSecret().get();
        auto admin = user->isAdmin();
        j[i]["username"] = userName;
        j[i]["password"] = password;
        j[i]["secret"] = secret; // wanted to somehow encode and decrypt this using the password string but didn't have time
        j[i]["admin"] = admin;
        ++i;
    }

    std::ofstream outfile{fileName};
    outfile << j.dump(2);
    outfile.close();
}

void LoginSystem::loadFromFile() noexcept
{
    if (std::ifstream file{fileName})
    {
        try
        {
            json j;
            file >> j;

            for (int i = 0; i < j.size(); ++i)
            {
                auto tmp = j[i];
                auto name = static_cast<std::string>(j[i]["username"]);
                auto password = static_cast<size_t>(j[i]["password"]);
                auto secret = static_cast<std::string>(j[i]["secret"]);
                auto admin = static_cast<bool>(j[i]["admin"]);
                User user(userName_t{name}, userPassword_t{password}, userSecret_t{secret}, admin);
                addUser(user);
            }
        }
        catch (const nlohmann::detail::parse_error &e)
        {
            // this mainly occurs if the json file is blank
            std::cout << "Error loading in json file \n";
        }
        catch (...)
        {
            std::cout << "Unexpected error when loading in file \n";
        }
    }
    return;
}

void LoginSystem::listUsers() noexcept
{
    for (const auto &[userName, user] : users)
    {
        std::cout << userName << '\n';
    }
}

std::shared_ptr<User> LoginSystem::selectUser() noexcept
{
    if (users.size() == 0)
        return nullptr;
        
    while (true)
    {
        listUsers();
        std::string selectUserPrompt = "Enter the username: ", userName;
        userInput::validateInput(userName, selectUserPrompt);
        if (users.find(userName) == users.end())
        {
            std::cout << "No such user.\n";
            continue;
        }
        return users[userName];
    }
}

void LoginSystem::changePassword(const std::shared_ptr<User> &user) noexcept
{
    auto previousPassword = user->getPassword().get();
    auto newPassword = userInput::enterPassword(previousPassword);
    user->setPassword(userPassword_t{newPassword});
}