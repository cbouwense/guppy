// Windows ---------------------------------------------------------------------------------------------------------------------
#if defined(_WIN32)
    #include <winsock2.h>
    #include <Ws2tcpip.h>
    // #include <windows.h>
    #pragma comment(lib, "Ws2_32.lib")
// -----------------------------------------------------------------------------------------------------------------------------

// POSIX -----------------------------------------------------------------------------------------------------------------------
#elif defined(__APPLE__) || defined(__linux__)
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
// -----------------------------------------------------------------------------------------------------------------------------

#endif

#include <stdio.h>
#include <errno.h>

// Windows ---------------------------------------------------------------------------------------------------------------------
#if defined(_WIN32)
    typedef struct {
        SOCKET socket_descriptor;
    } GupServer;
// -----------------------------------------------------------------------------------------------------------------------------

// POSIX -----------------------------------------------------------------------------------------------------------------------
#elif defined(__APPLE__) || defined(__linux__)
    typedef struct {
        int socket_descriptor;
    } GupServer;
// -----------------------------------------------------------------------------------------------------------------------------

#endif

/**************************************************************************************************
 * Public API                                                                                     *
 **************************************************************************************************/

GupServer gup_server_udp_create(const char* address, const short port);
void      gup_server_udp_destroy(GupServer s);
void      gup_server_udp_send(GupServer s, const char* message, const char* address, const short port);
void      gup_server_udp_receive(GupServer s, char* message, size_t message_size);

/**************************************************************************************************
 * Internal implementation                                                                        *
 **************************************************************************************************/

GupServer gup_server_udp_create(const char* address, const short port) {
// Windows ---------------------------------------------------------------------------------------------------------------------
#if defined(_WIN32)
    WSADATA wsadata;
    int res = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (res != NO_ERROR) {
        printf("WSAStartup failed with error %d\n", res);
        exit(1);
    }

    SOCKET socket_descriptor = INVALID_SOCKET;
    socket_descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socket_descriptor == INVALID_SOCKET) {
        printf("socket failed with error %d\n", WSAGetLastError());
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(address);
    addr.sin_port = htons(port);

    if (bind(socket_descriptor, (SOCKADDR *)&addr, sizeof(addr))) {
        printf("bind failed with error %d\n", WSAGetLastError());
        exit(1);
    }

    return (GupServer) {
        .socket_descriptor = socket_descriptor,
    };
// -----------------------------------------------------------------------------------------------------------------------------

// POSIX -----------------------------------------------------------------------------------------------------------------------
#elif defined(__APPLE__) || defined(__linux__)
    struct sockaddr_in server_addr;
  
    int socket_descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socket_descriptor == 0) {
        exit(1);
    }
  
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(address);
  
    // clear errno
    errno = 0;
  
    int bind_res = bind(socket_descriptor, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (bind_res != 0) {
        char* error_message = strerror(errno);
        printf("Error binding: %s\n", error_message);
        exit(1);
    }
  
    return (GupServer) {
        .socket_descriptor = socket_descriptor,
    };
// -----------------------------------------------------------------------------------------------------------------------------

#endif
}

void gup_server_udp_destroy(GupServer s) {
// Windows ---------------------------------------------------------------------------------------------------------------------
#if defined(_WIN32)
    closesocket(s.socket_descriptor);
// -----------------------------------------------------------------------------------------------------------------------------

// POSIX -----------------------------------------------------------------------------------------------------------------------
#elif defined(__APPLE__) || defined(__linux__)
    close(s.socket_descriptor);
// -----------------------------------------------------------------------------------------------------------------------------

#endif
}

void gup_server_udp_send(GupServer s, const char* message, const char* address, const short port) {
// Windows ---------------------------------------------------------------------------------------------------------------------
#if defined(_WIN32) 
    struct sockaddr_in receiver_addr;
    int receiver_addr_size = sizeof (receiver_addr);
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(port);
    receiver_addr.sin_addr.s_addr = inet_addr(address);

    int send_buf_len = (int)strlen(message);
    int send_result = sendto(s.socket_descriptor, message, send_buf_len, 0, (SOCKADDR *)&receiver_addr, receiver_addr_size);
    if (send_result == SOCKET_ERROR) {
        printf("Sending datagram error: %d\n", WSAGetLastError());
    }
// -----------------------------------------------------------------------------------------------------------------------------

// POSIX -----------------------------------------------------------------------------------------------------------------------
#elif defined(__APPLE__) || defined(__linux__)
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(address);

    if (sendto(s.socket_descriptor, message, strlen(message), 0, (struct sockaddr*)&(server_addr), sizeof(server_addr)) < 0) {
        perror("Error sending datagram\n");
        exit(1);
    }
// -----------------------------------------------------------------------------------------------------------------------------

#endif
}

void gup_server_udp_receive(GupServer s, char* message, size_t message_size) {
// Windows ---------------------------------------------------------------------------------------------------------------------
#if defined(_WIN32)
    int bytes_received;

    struct sockaddr_in sender_addr;
    int sender_addr_size = sizeof(sender_addr);

    printf("waiting for datagram...\n");
    bytes_received = recvfrom(s.socket_descriptor, message, message_size-1, 0, (SOCKADDR *)&sender_addr, &sender_addr_size);
    if (bytes_received == SOCKET_ERROR) {
        printf("recvfrom failed with error %d\n", WSAGetLastError());
        exit(1);
    }
    printf("bytes_received: %d\n", bytes_received);
    message[bytes_received] = '\0';
// -----------------------------------------------------------------------------------------------------------------------------

// POSIX -----------------------------------------------------------------------------------------------------------------------
#elif defined(__APPLE__) || defined(__linux__)
    struct sockaddr_in client_addr;
    socklen_t client_struct_length = sizeof(client_addr);

    if (recvfrom(s.socket_descriptor, message, message_size, 0, (struct sockaddr*)&client_addr, &client_struct_length) < 0) {
        exit(1);
    }

    printf("Received message from IP: %s and port: %i\n",
    inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
// -----------------------------------------------------------------------------------------------------------------------------

#endif
}
