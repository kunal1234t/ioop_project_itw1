#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>
using namespace std;

class User {
    private:
        string username;
        string email;
        bool isOnline;
    public:
        User();
        User(const string& username, const string& password);
        string getUsername() const;
        void setUsername(const string& username);
        bool getIsOnline() const;
        void setIsOnline(bool status);

        bool login(const string& user, const string& pass);
        void logout();
        void siplayProfile();
        bool validatePasswrod(const string& pass) const;

        static bool registerUser(const string& username, const string& password);
        static User* authenticateUser(const string& username, const string& password);
        static bool userExists(const string& username);
};

#endif 