#include "ChatRoom.h"
#include <sstream>
#include <algorithm>

ChatRoom::ChatRoom(const std::string& name, int maxMessages)
    : name(name), maxMessages(maxMessages) {}

std::string ChatRoom::getName() const { return name; }

void ChatRoom::addMember(const std::string& username) {
    members.insert(username);
}

void ChatRoom::removeMember(const std::string& username) {
    members.erase(username);
}

bool ChatRoom::isMember(const std::string& username) const {
    return members.find(username) != members.end();
}

std::set<std::string> ChatRoom::getMembers() const {
    return members;
}

void ChatRoom::addMessage(const Message& msg) {
    messages.push_back(msg);
    if (messages.size() > maxMessages) {
        messages.erase(messages.begin());
    }
}

std::vector<Message> ChatRoom::getMessages() const {
    return messages;
}

std::vector<Message> ChatRoom::getRecentMessages(int count) const {
    int start = std::max(0, (int)messages.size() - count);
    return std::vector<Message>(messages.begin() + start, messages.end());
}

std::string ChatRoom::serializeMembers() const {
    std::ostringstream oss;
    for (auto it = members.begin(); it != members.end(); ++it) {
        if (it != members.begin()) oss << ",";
        oss << *it;
    }
    return oss.str();
}

void ChatRoom::deserializeMembers(const std::string& data) {
    std::istringstream iss(data);
    std::string member;
    members.clear();
    while (std::getline(iss, member, ',')) {
        if (!member.empty()) {
            members.insert(member);
        }
    }
}