#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <modbus/modbus.h>
#include <unistd.h>

static int running = 1;

void handle_signal(int sig) {
    printf("\nStopping server...\n");
    running = 0;
}

int main(void) {
    modbus_t *ctx;
    modbus_mapping_t *mb_mapping;
    int server_socket;

    // Handle Ctrl+C
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    ctx = modbus_new_tcp("0.0.0.0", 5020);
    if (ctx == NULL) {
        fprintf(stderr, "Unable to create Modbus context\n");
        return -1;
    }
    printf("Modbus context created.\n");

    mb_mapping = modbus_mapping_new(500, 500, 500, 500);
    if (mb_mapping == NULL) {
        fprintf(stderr, "Mapping allocation failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }
    printf("Memory mapping created.\n");

    server_socket = modbus_tcp_listen(ctx, 1);
    if (server_socket == -1) {
        fprintf(stderr, "Listen failed: %s\n", modbus_strerror(errno));
        modbus_mapping_free(mb_mapping);
        modbus_free(ctx);
        return -1;
    }
    printf("Server listening on port 5020\n");

    // Main loop
    while (running) {
        int client_socket;
        client_socket = modbus_tcp_accept(ctx, &server_socket);
        if (client_socket == -1) {
            continue;  // Wait for next client
        }

        printf("Client connected.\n");

        while (running) {
            uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
            int rc = modbus_receive(ctx, query);
            if (rc > 0) {
                modbus_reply(ctx, query, rc, mb_mapping);
            } else if (rc == -1) {
                printf("Client disconnected.\n");
                break;
            }
        }
    }

    printf("Shutting down server...\n");
    close(server_socket);
    modbus_mapping_free(mb_mapping);
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}
