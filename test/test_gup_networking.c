#include "../src/guppy_networking.h"

#define TRUE 1
#define FALSE 0
#define true 1
#define false 0
typedef unsigned char bool;

#define SENDER_ADDR "192.168.0.42"
#define SENDER_PORT 1337
#define RECEIVER_ADDR "192.168.138.80"
#define RECEIVER_PORT 1338

bool is_tcp(const char *protocol) {
  return (
    strcmp("t", protocol)   == 0 ||
    strcmp("tcp", protocol) == 0
  );
}

bool is_udp(const char *protocol) {
  return (
    strcmp("u", protocol)   == 0 ||
    strcmp("udp", protocol) == 0
  );
}

bool is_server(const char *type) {
  return (
    strcmp("s", type)      == 0 ||
    strcmp("server", type) == 0
  );
}

bool is_client(const char *type) {
  return (
    strcmp("c", type)      == 0 ||
    strcmp("client", type) == 0
  );
}

int main(void) {
  char protocol_input_raw[4], protocol_str[4];
  char server_or_client_input_raw[7], server_or_client_str[7];
  char address_input_raw[256], address_str[256];
  int octets[4];
  bool is_ipv4 = false;

  { // Protocol
    printf("Enter protocol (t/cp, u/dp): ");
    if (fgets(protocol_input_raw, sizeof(protocol_input_raw), stdin) == NULL) {
      perror("Encountered error while reading keyboard input\n");
      exit(1);
    }
    
    sscanf(protocol_input_raw, "%3[^'\n']", protocol_str);
    if (!is_tcp(protocol_str) && !is_udp(protocol_str)) {
      printf("ERROR: Unrecognized protocol '%s'. Expected 't', 'tcp', 'u', or 'udp'.\n", protocol_str);
      exit(1);
    }
  }

  { // Server or client
    printf("Enter type (s/erver, c/lient): ");
    if (fgets(server_or_client_input_raw, sizeof(server_or_client_input_raw), stdin) == NULL) {
      perror("Encountered error while reading keyboard input\n");
      exit(1);
    }

    sscanf(server_or_client_input_raw, "%6[^'\n']", server_or_client_str);
    if (!is_server(server_or_client_str) && !is_client(server_or_client_str)) {
      printf("ERROR: Unrecognized type '%s'. Expected 's', 'server', 'c', or 'client'.\n", server_or_client_str);
      exit(1);
    }
  }

  { // Address
    printf("Enter address to bind to (192.168.0.42/localhost/[Enter for nothing]): ");
    if (fgets(address_input_raw, sizeof(address_input_raw), stdin) == NULL) {
      perror("Encountered error while reading keyboard input\n");
      exit(1);
    }

    if (sscanf(address_input_raw, "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2], &octets[3])) {
      is_ipv4 = true;
    }
    else if (sscanf(address_input_raw, "%255[^\n]", address_str)) {
      is_ipv4 = false;
    } else {
      printf("ERROR: Unrecognized address '%s'. Expected an ipv4 address or a domain name less than 256 characters.\n", address_input_raw);
      exit(1);
    }
  }

  { // Output state
    if (is_tcp(protocol_str)) { 
      printf("TCP ");
    } else if (is_udp(protocol_str)) {
      printf("UDP ");
    } else {
      exit(1);
    }

    if (is_server(server_or_client_str)) {
      printf("server ");
    } else if (is_client(server_or_client_str)) {
      printf("client ");
    } else {
      exit(1);
    }

    printf("running on ");
    if (is_ipv4) {
      printf("%d.%d.%d.%d\n", octets[0], octets[1], octets[2], octets[3]);
    } else {
      printf("%s\n", address_str);
    }
  }

  return 0;
}
