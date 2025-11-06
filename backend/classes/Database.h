#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <map>
#include "User.h"
#include "Message.h"
#include "ChatRoom.h"

class Database {
private:
    std::string dataDir;
    std::string usersFile;
    std::string messagesFile;
    std::string roomsFile;

public:
    Database(const std::string& dataDirectory = "data");
    
    // User operations
    bool saveUser(const User& user);
    std::vector<User> loadUsers();
    User* findUser(const std::string& username, std::vector<User>& users);
    
    // Message operations
    bool saveMessage(const Message& msg);
    std::vector<Message> loadMessages();
    std::vector<Message> loadMessagesByRoom(const std::string& room);
    
    // Room operations
    bool saveRoom(const ChatRoom& room);
    std::map<std::string, ChatRoom> loadRooms();
    
    // Utility
    void ensureDataDirectory();
}