# ===============================
# OPC UA Project Makefile (verified paths)
# ===============================

# Raspberry Pi connection info
PI_PWD  = /home/viny/Desktop/projeto11_di/opc_ua
PI_IP   = 10.42.0.143
PI_HOST = viny

# Compiler
CC = gcc

# Targets
SERVER_TARGET = opc_ua_server
CLIENT_TARGET = opc_ua_client

# Source files
SERVER_SRCS = opc_ua_server.c
CLIENT_SRCS = opc_ua_client.c

# open62541 include and library paths
OPEN62541_INC = ./open62541/build
OPEN62541_LIB = ./open62541/build/bin/libopen62541.a

# Compiler and linker flags
CFLAGS  = -I$(OPEN62541_INC)
LDFLAGS = $(OPEN62541_LIB) -lm -lpthread

# Default target
all: $(SERVER_TARGET) $(CLIENT_TARGET)

# Build OPC UA server
$(SERVER_TARGET): $(SERVER_SRCS)
	@echo "Compiling OPC UA Server..."
	$(CC) $(CFLAGS) $(SERVER_SRCS) -o $(SERVER_TARGET) $(LDFLAGS)

# Build OPC UA client
$(CLIENT_TARGET): $(CLIENT_SRCS)
	@echo "Compiling OPC UA Client..."
	$(CC) $(CFLAGS) $(CLIENT_SRCS) -o $(CLIENT_TARGET) $(LDFLAGS)

# Compile individually
compile_server: $(SERVER_TARGET)
compile_client: $(CLIENT_TARGET)

# Transfer project to Raspberry Pi
to_rasp:
	@echo "Transferring project to Raspberry Pi..."
	scp -r * $(PI_HOST)@$(PI_IP):$(PI_PWD)
	@echo "Transfer complete."

# Run server and client
server:
	@echo "Running OPC UA Server..."
	sudo ./$(SERVER_TARGET)

client:
	@echo "Running OPC UA Client..."
	./$(CLIENT_TARGET)

# Clean binaries
clean:
	@echo "Cleaning build files..."
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET)
