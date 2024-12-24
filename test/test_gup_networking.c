#include "../src/guppy_networking.h"

#define SENDER_ADDR "192.168.0.206"
#define SENDER_PORT 1337
#define RECEIVER_ADDR "192.168.0.42"
#define RECEIVER_PORT 1338

int main(int argc, char **argv) {
  if (strcmp(argv[1], "sender") == 0) {
    GupServer server = gup_server_udp_create(SENDER_ADDR, SENDER_PORT);

    gup_server_udp_send(server, "zoo wee mama", RECEIVER_ADDR, RECEIVER_PORT);

    gup_server_udp_destroy(server);
  }

  if (strcmp(argv[1], "receiver") == 0) {
    GupServer server = gup_server_udp_create(RECEIVER_ADDR, RECEIVER_PORT);

    char message[1024] = {0};
    for (int i = 0; i < 3; i++) {
      gup_server_udp_receive(server, message, sizeof(message));
      printf("%s\n", message);
    }
    
    gup_server_udp_destroy(server);
  }

  return 0;
}