#rasp pwd
PI_PWD = /home/viny/Desktop/projeto11_di/final_product
PI_IP = 10.42.0.143
PI_HOST = viny
# Compiler
CC = gcc

# Output binary
TARGET = output

# Source file
SRCS = main.c mqtt_paho.c

# Libraries
LIBS = -lpaho-mqtt3cs -lssl -lcrypto

LIB_DIRS = -I.

# Default target
all: $(TARGET)

# Build rule
$(TARGET):
	@echo "Compiling"
	@$(CC) $(INCLUDES) $(SRCS) -o $(TARGET) $(LIB_DIRS) $(LIBS) 
compile:
	@echo "Compiling"
	$(CC) $(INCLUDES) $(SRCS) -o $(TARGET) $(LIB_DIRS) $(LIBS)
monitor:
	@echo "Monitor"
	az iot hub monitor-events --hub-name test-0-viny --device-id test_0_viny_device

send: all
	@echo "Sending"
	./$(TARGET)
	
to_rasp:
	@echo "Transfering"
	@scp -r * $(PI_HOST)@$(PI_IP):$(PI_PWD)
	@echo "Done"

# Clean
clean:
	@echo "Reset"
	rm -f $(TARGET)

