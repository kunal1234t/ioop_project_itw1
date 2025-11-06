#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include <map>
#include "User.h"
#include "ChatRoom.h"
#include "Database.h"

class Server {
private:
    Database db;
    std::vector<User> users;
    std::map<std::string, ChatRoom> chatRooms;
    User* currentUser;

public:
    Server();
    
    // User management
    bool registerUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password);
    void logoutUser();
    User* getCurrentUser();
    std::vector<User> getOnlineUsers();
    
    // Chat room management
    bool createRoom(const std::string& roomName);
    bool joinRoom(const std::string& roomName);
    bool leaveRoom(const std::string& roomName);
    std::vector<std::string> getRoomList();
    ChatRoom* getRoom(const std::string& roomName);
    
    // Message handling
    bool sendMessage(const std::string& roomName, const std::string& content);
    std::vector<Message> getRoomMessages(const std::string& roomName, int count = 20);
    
    // Initialization
    void loadData();
    void saveData();
};

#endif