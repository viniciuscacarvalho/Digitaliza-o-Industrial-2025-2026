#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <MQTTClient.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#include "mqtt_paho.h"

// Configurações do IoT Hub
#define ADDRESS "ssl://test-0-viny.azure-devices.net:8883" // Endereço do IoT Hub
#define CLIENTID "test_0_viny_device"                      // ID do dispositivo
#define USERNAME "test-0-viny.azure-devices.net/test_0_viny_device/?api-version=2021-04-12"
#define TOPIC "devices/test_0_viny_device/messages/events/" // Tópico para envio de mensagens
#define QOS 1
#define TIMEOUT 10000L

// Chave primária ou secundária do dispositivo
#define DEVICE_KEY "ut7kR4A68i26FvgphSaPPwFFf1i3IAKK2QP5sUtK4dE=" // Substitua pela sua chave primária ou secundária

// Função para codificar em Base64
char* base64_encode(const unsigned char* input, int length) {
    BIO *bmem, *b64;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char* buff = (char*)malloc(bptr->length + 1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;

    BIO_free_all(b64);

    return buff;
}

// Função para gerar o Token SAS
char* generate_sas_token(const char* resource_uri, const char* key, int expiry) {
    char string_to_sign[256];
    snprintf(string_to_sign, sizeof(string_to_sign), "%s\n%d", resource_uri, expiry);

    unsigned char* decoded_key;
    int key_len;
    decoded_key = (unsigned char*)malloc(strlen(key));
    key_len = EVP_DecodeBlock(decoded_key, (const unsigned char*)key, strlen(key));

    unsigned char* digest;
    digest = HMAC(EVP_sha256(), decoded_key, key_len, (unsigned char*)string_to_sign, strlen(string_to_sign), NULL, NULL);

    char* signature = base64_encode(digest, 32);

    char* token = (char*)malloc(512);
    snprintf(token, 512, "SharedAccessSignature sr=%s&sig=%s&se=%d", resource_uri, signature, expiry);

    free(decoded_key);
    free(signature);

    return token;
}

int send_mqtt_package(char* payload_string_to_send){
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    // Gerar o Token SAS
    const char* resource_uri = "test-0-viny.azure-devices.net/devices/test_0_viny_device";
    int expiry = time(NULL) + 3600; // Token válido por 1 hora
    char* sas_token = generate_sas_token(resource_uri, DEVICE_KEY, expiry);
    printf("Token SAS gerado: %s\n", sas_token);

    // Criar o cliente MQTT
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    // Configurar as opções de ligação
    conn_opts.keepAliveInterval = 60;
    conn_opts.cleansession = 1;
    conn_opts.username = USERNAME;
    conn_opts.password = sas_token; // Usar o Token SAS gerado

    // Configurar SSL/TLS
    MQTTClient_SSLOptions ssl_opts = MQTTClient_SSLOptions_initializer;
    ssl_opts.enableServerCertAuth = 1;  // Validar o certificado do servidor
    conn_opts.ssl = &ssl_opts;

    // Tentar ligar ao IoT Hub
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("Falha ao conectar ao IoT Hub, código de retorno: %d\n", rc);
        free(sas_token); // Liberar memória do Token SAS
        exit(EXIT_FAILURE);
    }
    printf("Conexão estabelecida com sucesso ao IoT Hub!\n");

    // Configurar a mensagem a enviar
    pubmsg.payload = (char*)payload_string_to_send;
    pubmsg.payloadlen = (int)strlen(payload_string_to_send);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    // Publicar a mensagem
    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    printf("A aguardar confirmação de publicação da mensagem: %s\n", payload_string_to_send);

    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Mensagem entregue com sucesso, código de retorno: %d\n", rc);

    // Desligar o cliente
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);

    // Liberar memória do Token SAS
    free(sas_token);

    return rc;
}
