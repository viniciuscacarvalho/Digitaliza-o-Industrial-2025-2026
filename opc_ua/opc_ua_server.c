#include <open62541.h>
#include <signal.h>

static UA_Boolean running = true;

static void stopHandler(int sig) {
    running = false;
}

int main(void) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_Server *server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    // Add a simple variable node
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Int32 myInteger = 42;
    UA_Variant_setScalar(&attr.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);
    attr.displayName = UA_LOCALIZEDTEXT("en-US","MyInteger");

    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "myInteger");
    UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1, "MyInteger");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);

    UA_Server_addVariableNode(server, myIntegerNodeId, parentNodeId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              myIntegerName, UA_NODEID_NULL, attr, NULL, NULL);

    UA_StatusCode status = UA_Server_run(server, &running);

    UA_Server_delete(server);
    return status == UA_STATUSCODE_GOOD ? 0 : 1;
}
