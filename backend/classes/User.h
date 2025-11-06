#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;
    bool online;

public:
    User(const std::string& username, const std::string& password);
    
    std::string getUsername() const;
    std::string getPassword() const;
    bool isOnline() const;
    void setOnline(bool status);
    bool authenticate(const std::string& pass) const;
    std::string serialize() const;
    static User deserialize(const std::string& data);
};

#endif