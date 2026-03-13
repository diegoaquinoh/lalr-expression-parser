CXX = g++
CXXFLAGS = -Wall -std=c++17

SRCS = main.cpp automate.cpp etat.cpp lexer.cpp symbole.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = parser

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
