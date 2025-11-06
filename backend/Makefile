CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iclasses
TARGET = chatroom
SRCDIR = classes
SOURCES = $(SRCDIR)/Message.cpp $(SRCDIR)/User.cpp $(SRCDIR)/ChatRoom.cpp $(SRCDIR)/Database.cpp $(SRCDIR)/Server.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -rf data

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run