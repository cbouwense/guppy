#include <sys/socket.h>

#include "../src/guppy_networking.h"

#define SENDER_PORT 1337
#define RECEIVER_PORT 9001

int main(int argc, char **argv) {
  if (strcmp(argv[1], "sender") == 0) {
    GupServer server = gup_server_udp_create("127.0.0.1", SENDER_PORT);

    gup_server_udp_send(server, "zoo wee mama", "127.0.0.1", RECEIVER_PORT);

    gup_server_udp_destroy(server);
  }

  if (strcmp(argv[1], "receiver") == 0) {
    GupServer server = gup_server_udp_create("127.0.0.1", RECEIVER_PORT);

    char message[1024];
    gup_server_udp_receive(server, message, sizeof(message));
    printf("%s\n", message);
    
    gup_server_udp_destroy(server);
  }

  return 0;
}