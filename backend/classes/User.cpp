#include "User.h"
#include <sstream>

User::User(const std::string& username, const std::string& password)
    : username(username), password(password), online(false) {}

std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
bool User::isOnline() const { return online; }
void User::setOnline(bool status) { online = status; }

bool User::authenticate(const std::string& pass) const {
    return password == pass;
}

std::string User::serialize() const {
    std::ostringstream oss;
    oss << username << "|" << password;
    return oss.str();
}

User User::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string username, password;
    
    std::getline(iss, username, '|');
    std::getline(iss, password, '|');
    
    return User(username, password);
}