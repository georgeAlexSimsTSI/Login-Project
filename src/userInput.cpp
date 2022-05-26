#include "../include/userInput.h"

namespace userInput
{
    bool validPassword(const std::string &password)
    {
        bool alphas = std::any_of(password.begin(), password.end(), isalpha);
        bool digit = std::any_of(password.begin(), password.end(), isxdigit);
        bool upper = std::any_of(password.begin(), password.end(), isupper);
        bool lower = std::any_of(password.begin(), password.end(), islower);
        return alphas && digit && upper && lower;
    }

    size_t hashPassword(const std::string &password)
    {
        return std::hash<std::string>{}(password);
    }

    size_t enterPassword(const size_t &previous)
    {
        while (true)
        {
            std::string password;
            validateInput(password, "Password must be of length greater than 6, must contain Upper case and Lower case letters and at least one number\nEnter your password: ");
            if (!validPassword(password))
            {
                std::cout << "Invalid password\n";
                continue;
            }
            auto value = hashPassword(password);
            if (value == previous)
            {
                std::cout << "Password cant be the same as previous\n";
                continue;
            }
            return value;
        }
    }
}