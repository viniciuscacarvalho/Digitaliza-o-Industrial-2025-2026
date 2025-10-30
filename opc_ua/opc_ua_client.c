#include <open62541.h>
#include <stdio.h>

int main(void) {
    UA_Client *client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));

    UA_StatusCode status = UA_Client_connect(client, "opc.tcp://10.42.0.143:4840"); // Pi IP
    if(status != UA_STATUSCODE_GOOD) {
        printf("Could not connect to server, status code %s\n", UA_StatusCode_name(status));
        UA_Client_delete(client);
        return (int)status;
    }

    UA_Variant value; 
    UA_Variant_init(&value);

    // Read the variable node we created
    status = UA_Client_readValueAttribute(client, UA_NODEID_STRING(1, "myInteger"), &value);
    if(status == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_INT32])) {
        UA_Int32 val = *(UA_Int32*)value.data;
        printf("Value of MyInteger: %d\n", val);
    } else {
        printf("Failed to read node, status code %s\n", UA_StatusCode_name(status));
    }

    UA_Client_disconnect(client);
    UA_Client_delete(client);
    return 0;
}
