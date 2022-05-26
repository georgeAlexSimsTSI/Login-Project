#ifndef USER_H
#define USER_H

#include "./namedType.h"

#include <string>

using userName_t = named_type<std::string, struct userName>;
using userPassword_t = named_type<size_t, struct userPassword>;
using userSecret_t = named_type<std::string, struct userSecret>;

class User
{
private:
    userName_t name;
    userSecret_t secret;
    userPassword_t password;
    bool admin;

public:
    User(const userName_t &name, const userPassword_t &password, const userSecret_t &secret, const bool &admin) : name(name), secret(secret), password(password), admin(admin) {}
    User(const userName_t &name, const userPassword_t &password, const userSecret_t &secret) : name(name), secret(secret), password(password), admin(false) {}
    User() : User(userName_t{""}, userPassword_t{0}, userSecret_t{""}){};

    bool logIn(const userPassword_t &enteredPassword) const noexcept;

    bool isAdmin() const noexcept;

    userSecret_t getSecret() const noexcept;

    userName_t getName() const noexcept;

    userPassword_t getPassword() const noexcept;

    // any password verification will be handled before this point
    void setPassword(const userPassword_t &newPassword) noexcept;

    void promote() noexcept;

    void demote() noexcept;
};

#endif