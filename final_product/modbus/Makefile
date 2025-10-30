# Paths
PI_PWD = /home/viny/Desktop/projeto11_di/final_product
PI_IP = 10.42.0.143
PI_HOST = viny

# Compiler
CXX = g++

# Output binary
TARGET = output

# Source files
SRCS = main.c mqtt_paho.c fsm_code/fsm/fsm.cpp

# Libraries
LIBS = -lpaho-mqtt3cs -lssl -lcrypto

# Include directories
INCLUDES = -I.

# Object files
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.cpp=.o)

# Default target
all: $(TARGET)

# Compile C and C++ files
%.o: %.c
	$(CXX) $(INCLUDES) -c $< -o $@

%.o: %.cpp
	$(CXX) $(INCLUDES) -c $< -o $@

# Link everything with g++
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Run
send: $(TARGET)
	./$(TARGET)

# Transfer to Raspberry Pi
to_rasp:
	scp -r * $(PI_HOST)@$(PI_IP):$(PI_PWD)
	@echo "Done"

# Clean
clean:
	rm -f $(TARGET) $(OBJS)
