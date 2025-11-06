#include "Server.h"
#include <iostream>
#include <limits>
#include <iomanip>

class ConsoleUI {
private:
    Server server;
    
    void clearScreen() {
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
    }
    
    void pause() {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    
    void printHeader(const std::string& title) {
        clearScreen();
        std::cout << "========================================\n";
        std::cout << "    " << title << "\n";
        std::cout << "========================================\n\n";
    }

public:
    void run() {
        while (true) {
            if (!server.getCurrentUser()) {
                if (!showAuthMenu()) break;
            } else {
                if (!showMainMenu()) break;
            }
        }
    }
    
    bool showAuthMenu() {
        printHeader("CHAT ROOM - Authentication");
        std::cout << "1. Login\n";
        std::cout << "2. Register\n";
        std::cout << "3. Exit\n";
        std::cout << "\nChoice: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1: return handleLogin();
            case 2: return handleRegister();
            case 3: return false;
            default:
                std::cout << "Invalid choice!\n";
                pause();
                return true;
        }
    }
    
    bool handleLogin() {
        printHeader("LOGIN");
        std::string username, password;
        
        std::cout << "Username: ";
        std::getline(std::cin, username);
        std::cout << "Password: ";
        std::getline(std::cin, password);
        
        if (server.loginUser(username, password)) {
            std::cout << "\n✓ Login successful! Welcome, " << username << "!\n";
            pause();
            return true;
        } else {
            std::cout << "\n✗ Invalid credentials!\n";
            pause();
            return true;
        }
    }
    
    bool handleRegister() {
        printHeader("REGISTER");
        std::string username, password;
        
        std::cout << "Username: ";
        std::getline(std::cin, username);
        std::cout << "Password: ";
        std::getline(std::cin, password);
        
        if (server.registerUser(username, password)) {
            std::cout << "\n✓ Registration successful! You can now login.\n";
            pause();
            return true;
        } else {
            std::cout << "\n✗ Username already exists!\n";
            pause();
            return true;
        }
    }
    
    bool showMainMenu() {
        printHeader("CHAT ROOM - Main Menu");
        User* user = server.getCurrentUser();
        std::cout << "Logged in as: " << user->getUsername() << "\n\n";
        
        std::cout << "1. List Chat Rooms\n";
        std::cout << "2. Create Chat Room\n";
        std::cout << "3. Join Chat Room\n";
        std::cout << "4. View My Rooms\n";
        std::cout << "5. Enter Chat Room\n";
        std::cout << "6. Logout\n";
        std::cout << "\nChoice: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1: listRooms(); return true;
            case 2: createRoom(); return true;
            case 3: joinRoom(); return true;
            case 4: viewMyRooms(); return true;
            case 5: enterChatRoom(); return true;
            case 6:
                server.logoutUser();
                std::cout << "\nLogged out successfully!\n";
                pause();
                return true;
            default:
                std::cout << "Invalid choice!\n";
                pause();
                return true;
        }
    }
    
    void listRooms() {
        printHeader("ALL CHAT ROOMS");
        std::vector<std::string> rooms = server.getRoomList();
        
        if (rooms.empty()) {
            std::cout << "No chat rooms available.\n";
        } else {
            for (size_t i = 0; i < rooms.size(); i++) {
                ChatRoom* room = server.getRoom(rooms[i]);
                std::cout << i + 1 << ". " << rooms[i] 
                         << " (" << room->getMembers().size() << " members)\n";
            }
        }
        pause();
    }
    
    void createRoom() {
        printHeader("CREATE CHAT ROOM");
        std::string roomName;
        
        std::cout << "Room Name: ";
        std::getline(std::cin, roomName);
        
        if (server.createRoom(roomName)) {
            std::cout << "\n✓ Room '" << roomName << "' created successfully!\n";
        } else {
            std::cout << "\n✗ Room already exists!\n";
        }
        pause();
    }
    
    void joinRoom() {
        printHeader("JOIN CHAT ROOM");
        std::vector<std::string> rooms = server.getRoomList();
        
        if (rooms.empty()) {
            std::cout << "No rooms available to join.\n";
            pause();
            return;
        }
        
        for (size_t i = 0; i < rooms.size(); i++) {
            std::cout << i + 1 << ". " << rooms[i] << "\n";
        }
        
        std::cout << "\nEnter room name: ";
        std::string roomName;
        std::getline(std::cin, roomName);
        
        if (server.joinRoom(roomName)) {
            std::cout << "\n✓ Joined room '" << roomName << "'!\n";
        } else {
            std::cout << "\n✗ Could not join room!\n";
        }
        pause();
    }
    
    void viewMyRooms() {
        printHeader("MY CHAT ROOMS");
        std::vector<std::string> rooms = server.getRoomList();
        User* user = server.getCurrentUser();
        bool found = false;
        
        for (const auto& roomName : rooms) {
            ChatRoom* room = server.getRoom(roomName);
            if (room && room->isMember(user->getUsername())) {
                std::cout << "• " << roomName 
                         << " (" << room->getMembers().size() << " members)\n";
                found = true;
            }
        }
        
        if (!found) {
            std::cout << "You haven't joined any rooms yet.\n";
        }
        pause();
    }
    
    void enterChatRoom() {
        printHeader("ENTER CHAT ROOM");
        std::vector<std::string> rooms = server.getRoomList();
        User* user = server.getCurrentUser();
        
        // Show only rooms user is a member of
        std::vector<std::string> myRooms;
        for (const auto& roomName : rooms) {
            ChatRoom* room = server.getRoom(roomName);
            if (room && room->isMember(user->getUsername())) {
                myRooms.push_back(roomName);
            }
        }
        
        if (myRooms.empty()) {
            std::cout << "You haven't joined any rooms. Join a room first!\n";
            pause();
            return;
        }
        
        for (size_t i = 0; i < myRooms.size(); i++) {
            std::cout << i + 1 << ". " << myRooms[i] << "\n";
        }
        
        std::cout << "\nEnter room name: ";
        std::string roomName;
        std::getline(std::cin, roomName);
        
        ChatRoom* room = server.getRoom(roomName);
        if (room && room->isMember(user->getUsername())) {
            chatInRoom(roomName);
        } else {
            std::cout << "\n✗ Invalid room or you're not a member!\n";
            pause();
        }
    }
    
    void chatInRoom(const std::string& roomName) {
        while (true) {
            printHeader("CHAT: " + roomName);
            
            // Display recent messages
            std::vector<Message> messages = server.getRoomMessages(roomName, 10);
            if (messages.empty()) {
                std::cout << "[No messages yet]\n\n";
            } else {
                for (const auto& msg : messages) {
                    std::cout << "[" << msg.getFormattedTime() << "] "
                             << msg.getSender() << ": " << msg.getContent() << "\n";
                }
                std::cout << "\n";
            }
            
            // Show members
            ChatRoom* room = server.getRoom(roomName);
            std::cout << "Members: ";
            auto members = room->getMembers();
            for (auto it = members.begin(); it != members.end(); ++it) {
                if (it != members.begin()) std::cout << ", ";
                std::cout << *it;
            }
            std::cout << "\n\n";
            
            std::cout << "Options: [1] Send Message [2] Refresh [3] Leave Room [4] Back\n";
            std::cout << "Choice: ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            if (choice == 1) {
                std::cout << "\nMessage: ";
                std::string content;
                std::getline(std::cin, content);
                
                if (!content.empty()) {
                    if (server.sendMessage(roomName, content)) {
                        std::cout << "✓ Message sent!\n";
                    } else {
                        std::cout << "✗ Failed to send message!\n";
                    }
                }
            } else if (choice == 2) {
                continue;
            } else if (choice == 3) {
                server.leaveRoom(roomName);
                std::cout << "\nLeft room '" << roomName << "'.\n";
                pause();
                break;
            } else if (choice == 4) {
                break;
            }
        }
    }
};