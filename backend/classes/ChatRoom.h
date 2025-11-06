#ifndef CHATROOM_H
#define CHATROOM_H

#include <string>
#include <vector>
#include <set>
#include "Message.h"

class ChatRoom {
private:
    std::string name;
    std::set<std::string> members;
    std::vector<Message> messages;
    int maxMessages;

public:
    ChatRoom(const std::string& name, int maxMessages = 100);
    
    std::string getName() const;
    void addMember(const std::string& username);
    void removeMember(const std::string& username);
    bool isMember(const std::string& username) const;
    std::set<std::string> getMembers() const;
    
    void addMessage(const Message& msg);
    std::vector<Message> getMessages() const;
    std::vector<Message> getRecentMessages(int count) const;
    
    std::string serializeMembers() const;
    void deserializeMembers(const std::string& data);
};

#endif