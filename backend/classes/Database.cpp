#include "Database.h"
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <iostream>

#ifdef _WIN32
#include <direct.h>
#define mkdir(dir, mode) _mkdir(dir)
#endif

Database::Database(const std::string& dataDirectory)
    : dataDir(dataDirectory),
      usersFile(dataDirectory + "/users.txt"),
      messagesFile(dataDirectory + "/messages.txt"),
      roomsFile(dataDirectory + "/rooms.txt") {
    ensureDataDirectory();
}

void Database::ensureDataDirectory() {
    struct stat info;
    if (stat(dataDir.c_str(), &info) != 0) {
        mkdir(dataDir.c_str(), 0755);
    }
}

bool Database::saveUser(const User& user) {
    std::vector<User> users = loadUsers();
    bool found = false;
    
    for (auto& u : users) {
        if (u.getUsername() == user.getUsername()) {
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::ofstream file(usersFile, std::ios::app);
        if (file.is_open()) {
            file << user.serialize() << std::endl;
            file.close();
            return true;
        }
    }
    return false;
}

std::vector<User> Database::loadUsers() {
    std::vector<User> users;
    std::ifstream file(usersFile);
    std::string line;
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            users.push_back(User::deserialize(line));
        }
    }
    file.close();
    return users;
}

User* Database::findUser(const std::string& username, std::vector<User>& users) {
    for (auto& user : users) {
        if (user.getUsername() == username) {
            return &user;
        }
    }
    return nullptr;
}

bool Database::saveMessage(const Message& msg) {
    std::ofstream file(messagesFile, std::ios::app);
    if (file.is_open()) {
        file << msg.serialize() << std::endl;
        file.close();
        return true;
    }
    return false;
}

std::vector<Message> Database::loadMessages() {
    std::vector<Message> messages;
    std::ifstream file(messagesFile);
    std::string line;
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            messages.push_back(Message::deserialize(line));
        }
    }
    file.close();
    return messages;
}

std::vector<Message> Database::loadMessagesByRoom(const std::string& room) {
    std::vector<Message> allMessages = loadMessages();
    std::vector<Message> roomMessages;
    
    for (const auto& msg : allMessages) {
        if (msg.getRoom() == room) {
            roomMessages.push_back(msg);
        }
    }
    return roomMessages;
}

bool Database::saveRoom(const ChatRoom& room) {
    std::map<std::string, ChatRoom> rooms = loadRooms();
    rooms[room.getName()] = room;
    
    std::ofstream file(roomsFile);
    if (file.is_open()) {
        for (const auto& pair : rooms) {
            file << pair.first << "|" << pair.second.serializeMembers() << std::endl;
        }
        file.close();
        return true;
    }
    return false;
}

std::map<std::string, ChatRoom> Database::loadRooms() {
    std::map<std::string, ChatRoom> rooms;
    std::ifstream file(roomsFile);
    std::string line;
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            std::istringstream iss(line);
            std::string roomName, members;
            
            std::getline(iss, roomName, '|');
            std::getline(iss, members);
            
            ChatRoom room(roomName);
            room.deserializeMembers(members);
            rooms[roomName] = room;
        }
    }
    file.close();
    return rooms;
}