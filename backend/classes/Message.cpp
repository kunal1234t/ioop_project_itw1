#include "Message.h"
#include <sstream>
#include <iomanip>

Message::Message(const std::string& sender, const std::string& content, const std::string& room)
    : sender(sender), content(content), room(room), timestamp(time(nullptr)) {}

Message::Message(const std::string& sender, const std::string& content, const std::string& room, time_t timestamp)
    : sender(sender), content(content), room(room), timestamp(timestamp) {}

std::string Message::getSender() const { return sender; }
std::string Message::getContent() const { return content; }
std::string Message::getRoom() const { return room; }
time_t Message::getTimestamp() const { return timestamp; }

std::string Message::getFormattedTime() const {
    char buffer[80];
    struct tm* timeinfo = localtime(&timestamp);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buffer);
}

std::string Message::serialize() const {
    std::ostringstream oss;
    oss << sender << "|" << content << "|" << room << "|" << timestamp;
    return oss.str();
}

Message Message::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string sender, content, room;
    time_t timestamp;
    
    std::getline(iss, sender, '|');
    std::getline(iss, content, '|');
    std::getline(iss, room, '|');
    iss >> timestamp;
    
    return Message(sender, content, room, timestamp);
}