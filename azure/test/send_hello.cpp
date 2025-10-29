#include "iothub_device_client.h"
#include "iothub_transport_mqtt_client.h"
#include "iothub_message.h"
#include <stdio.h>
#include <stdlib.h>

static const char* conn_str = "HostName=test-0-viny.azure-devices.net;DeviceId=test_0_viny_device;SharedAccessKey=wbJAkkpKfJJ1b3JRqm+rn0fkeAVRaUlOBgOky2tVbtY=";


int main(void)
{
        IOTHUB_DEVICE_CLIENT_HANDLE client = IoTHubDeviceClient_CreateFromConnectionString(conn_str, MQTT_Protocol);
    if (!client) { printf("Failed to create client\n"); return -1; }

    IOTHUB_MESSAGE_HANDLE msg = IoTHubMessage_CreateFromString("Hello World");
    IoTHubDeviceClient_SendEventAsync(client, msg, NULL, NULL);

    IoTHubMessage_Destroy(msg);
    IoTHubDeviceClient_Destroy(client);
    IoTHub_Deinit();
    printf("Message sent!\n");
    return 0;
}
