#rasp pwd
PI_PWD = /home/viny/Desktop/projeto11_di/mqtt_paho
PI_IP = 10.42.0.143
PI_HOST = viny
# Compiler
CC = gcc

# Output binary
TARGET = test_code_paho

# Source file
SRCS = test_code_paho.c

# Libraries
LIBS = -lpaho-mqtt3cs -lssl -lcrypto
# Default target
all: $(TARGET)

# Build rule
$(TARGET):
	@echo "Compiling"
	$(CC) $(INCLUDES) $(SRCS) -o $(TARGET) $(LIBS)

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

