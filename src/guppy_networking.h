#include "guppy.h"

#if defined(_WIN32)
    #include <winsock2.h>
    #include <windows.h>
#elif defined(__APPLE__) || defined(__linux__)
    #include <sys/socket.h>
    #include <arpa/inet.h>
#endif

#include <errno.h>

#if defined(_WIN32)
    typedef struct {
        SOCKET socket_descriptor;
    } GupServer;
#elif defined(__APPLE__) || defined(__linux__)
    typedef struct {
        int socket_descriptor;
    } GupServer;
#endif

/**************************************************************************************************
 * Public API                                                                                     *
 **************************************************************************************************/

GupServer gup_server_udp_create(const char *address, const short port);
void      gup_server_udp_destroy(GupServer s);
void      gup_server_udp_send(GupServer s, const char *message, const char *address, const short port);
void      gup_server_udp_receive(GupServer s, char *message, size_t message_size);

/**************************************************************************************************
 * Internal implementation                                                                        *
 **************************************************************************************************/

GupServer gup_server_udp_create(const char *address, const short port) {
#if defined(_WIN32)
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);

    SOCKET socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);

    struct socketaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(address);
    addr.sin_port = htons(port);

    bind(socket_descriptor, &addr, sizeof(addr));

    return (GupServer) {
        .socket_descriptor = socket_descriptor,
    };
#elif defined(__APPLE__) || defined(__linux__)
    struct sockaddr_in server_addr;
  
    int socket_descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    gup_assert(socket_descriptor != 0);
  
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(address);
  
    // clear errno
    errno = 0;
  
    int bind_res = bind(socket_descriptor, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (bind_res != 0) {
        char *error_message = strerror(errno);
        printf("Error binding: %s\n", error_message);
        exit(1);
    }
  
    return (GupServer) {
        .socket_descriptor = socket_descriptor,
    };
#endif
}

void gup_server_udp_destroy(GupServer s) {
#if defined(_WIN32)
    // TODO
#elif defined(__APPLE__) || defined(__linux__)
    close(s.socket_descriptor);
#endif
}

void gup_server_udp_send(GupServer s, const char *message, const char *address, const short port) {
#if defined(_WIN32)
    // TODO
#elif defined(__APPLE__) || defined(__linux__)
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(address);

    gup_assert(sendto(s.socket_descriptor, message, strlen(message), 0, (struct sockaddr*)&(server_addr), sizeof(server_addr)) >= 0);
#endif
}

void gup_server_udp_receive(GupServer s, char *message, size_t message_size) {
#if defined(_WIN32)
    // TODO
#elif defined(__APPLE__) || defined(__linux__)
    struct sockaddr_in client_addr;
    socklen_t client_struct_length = sizeof(client_addr);

    gup_assert(recvfrom(s.socket_descriptor, message, message_size, 0, (struct sockaddr*)&client_addr, &client_struct_length) >= 0);

    printf("Received message from IP: %s and port: %i\n",
    inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
#endif
}
