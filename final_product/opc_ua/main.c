#include "mqtt_azure/mqtt_paho.h"
#include "fsm_code/fsm/fsm.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* fsm_execute_loop (void* arg);

void* azure_mqtt_coms (void* arg);

int main()
{
    setup_fsm();

    pthread_t fsm_thread, azure_thread;
    int ret;

        // Create first thread
    ret = pthread_create(&fsm_thread, NULL, fsm_execute_loop, NULL);
    if (ret) {
        fprintf(stderr, "Error creating thread 1\n");
        exit(EXIT_FAILURE);
    }
    printf("FSM thread Created\n");

    // Create second thread
    ret = pthread_create(&azure_thread, NULL, azure_mqtt_coms, NULL);
    if (ret) {
        fprintf(stderr, "Error creating thread 2\n");
        exit(EXIT_FAILURE);
    }
    printf("Azure thread Created\n");


    pthread_join(fsm_thread,NULL);
    pthread_join(azure_thread,NULL);  

    printf("Program Ended.\n");

    return 0;
}


void* fsm_execute_loop (void* arg)
{
    printf("FSM thread.\n");
    pthread_exit(NULL);
    execute_fsm();
}

void* azure_mqtt_coms (void* arg)
{
    printf("Azure thread.\n");
    send_mqtt_package(
        "{\"deviceId\",4,\"temperature\": 24.7,\"angle\": 35.2,\"timestamp\": \"2025-10-29T12:00:00Z\"}"
    );
    pthread_exit(NULL);
}