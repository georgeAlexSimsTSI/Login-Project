#include "../include/user.h"

bool User::logIn(const userPassword_t &enteredPassword) const noexcept
{
    return enteredPassword.get() == this->password.get();
}

bool User::isAdmin() const noexcept { return this->admin; }

userSecret_t User::getSecret() const noexcept { return this->secret; }

userName_t User::getName() const noexcept { return this->name; }

// any password verification will be handled before this point
void User::setPassword(const userPassword_t &newPassword) noexcept { this->password = newPassword; }

void User::promote() noexcept { this->admin = true; }

void User::demote() noexcept { this->admin = false; }