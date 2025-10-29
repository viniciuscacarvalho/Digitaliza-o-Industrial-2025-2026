# Compiler
CC = gcc

# Output binary
TARGET = send_hello

# Source file
SRCS = send_hello.cpp

# Include directories
INCLUDES = -I /usr/local/include

# Library directories
LIB_DIRS =\
-I azure-iot-sdk-c/iothub_client/inc/\
-I azure-iot-sdk-c/deps/umock-c/inc/\
-I azure-iot-sdk-c/deps/azure-macro-utils-c/inc/azure_macro_utils/\
-L /usr/local/lib

# Libraries
LIBS = -liothub_client -liothub_client_mqtt_transport -lparson \
       -lpthread -lssl -lcrypto -lcurl -luuid

# Default target
all: $(TARGET)

# Build rule
$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(SRCS) -o $(TARGET) $(LIB_DIRS) $(LIBS)

# Clean
clean:
	rm -f $(TARGET)

