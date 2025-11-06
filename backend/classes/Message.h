#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <ctime>

class Message {
private:
    std::string sender;
    std::string content;
    std::string room;
    time_t timestamp;

public:
    Message(const std::string& sender, const std::string& content, const std::string& room);
    Message(const std::string& sender, const std::string& content, const std::string& room, time_t timestamp);
    
    std::string getSender() const;
    std::string getContent() const;
    std::string getRoom() const;
    time_t getTimestamp() const;
    std::string getFormattedTime() const;
    std::string serialize() const;
    static Message deserialize(const std::string& data);
};

#endif