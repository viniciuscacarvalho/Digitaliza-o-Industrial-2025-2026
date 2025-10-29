#include <stdio.h>
#include <stdlib.h>
#include <errno.h>          
#include <modbus/modbus.h>

int main(void) {
    modbus_t *ctx;
    uint16_t tab_reg[10];
    int rc;
    int i;

    // Replace with your Raspberry Pi’s IP
    const char *pi_ip = "10.42.0.143";

    ctx = modbus_new_tcp(pi_ip, 5020);
    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }

    printf("Connected to Modbus server at %s\n", pi_ip);

    // Write 10 values to holding registers starting at address 0
    for (i = 0; i < 10; i++) tab_reg[i] = i + 100;
    rc = modbus_write_registers(ctx, 0, 10, tab_reg);
    if (rc == -1) {
        fprintf(stderr, "Write failed: %s\n", modbus_strerror(errno));
    } else {
        printf("Wrote 10 registers successfully.\n");
    }

    // Read back the same registers
    rc = modbus_read_registers(ctx, 0, 10, tab_reg);
    if (rc == -1) {
        fprintf(stderr, "Read failed: %s\n", modbus_strerror(errno));
    } else {
        printf("Read %d registers:\n", rc);
        for (i = 0; i < rc; i++) {
            printf("Register %d = %d\n", i, tab_reg[i]);
        }
    }

    modbus_close(ctx);
    modbus_free(ctx);
    return 0;
}
