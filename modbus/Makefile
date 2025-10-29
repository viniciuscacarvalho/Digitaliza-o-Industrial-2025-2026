# Raspberry Pi connection info
PI_PWD = /home/viny/Desktop/projeto11_di/modbus_file
PI_IP = 10.42.0.143
PI_HOST = viny

# Compiler
CC = gcc

# Targets
SERVER_TARGET = modbus_server
CLIENT_TARGET = modbus_client

# Source files
SERVER_SRCS = modbus_server.c
CLIENT_SRCS = modbus_client.c

# Compiler flags for libmodbus
CFLAGS  = $(shell pkg-config --cflags libmodbus)
LDFLAGS = $(shell pkg-config --libs libmodbus)

# Default target
all: $(SERVER_TARGET) $(CLIENT_TARGET)

# Build Modbus server
$(SERVER_TARGET): $(SERVER_SRCS)
	@echo "Compiling Modbus Server..."
	$(CC) $(CFLAGS) $(SERVER_SRCS) -o $(SERVER_TARGET) $(LDFLAGS)

# Build Modbus client
$(CLIENT_TARGET): $(CLIENT_SRCS)
	@echo "Compiling Modbus Client..."
	$(CC) $(CFLAGS) $(CLIENT_SRCS) -o $(CLIENT_TARGET) $(LDFLAGS)

# Compile individually
compile_server: $(SERVER_TARGET)
compile_client: $(CLIENT_TARGET)

# Transfer project to Raspberry Pi
to_rasp:
	@echo "Transferring project to Raspberry Pi..."
	scp -r * $(PI_HOST)@$(PI_IP):$(PI_PWD)
	@echo "Transfer complete."

# Azure test placeholders
server:
	@echo "Server"
	./$(SERVER_TARGET)
client:
	@echo "Client"
	./$(CLIENT_TARGET)

# Clean binaries
clean:
	@echo "Cleaning build files..."
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET)
