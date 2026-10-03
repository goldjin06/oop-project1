CXX = g++
CXXFLAGS = -std=c++14 -Wall
TARGET = a.exe
SRCS = $(wildcard src/*.cpp)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)