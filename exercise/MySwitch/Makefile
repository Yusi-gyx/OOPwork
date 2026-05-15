CXX = g++
TARGET = main
SRCS = $(wildcard *.cpp)
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)