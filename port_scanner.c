// another port scanner i made, but now in C (still needs some fixes)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// linux supported libraries, probably wont work on windows
#include <arpa/inet.h>
#include <netinet/in.h>

void scan_ports(const char *ip, int start_port, int end_port) {
    struct sockaddr_in target;
    int sock;

    memset(&target, 0, sizeof(target));
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = inet_addr(ip);

    for (int port = start_port; port <= end_port; port++) {
        target.sin_port = htons(port);

          // socket creation
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Socket creation failed");
            continue;
        }

          // connect attempt
        if (connect(sock, (struct sockaddr *)&target, sizeof(target)) == 0) {
            printf("[+] Port %d is open\n", port);
        }
        close(sock);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <IP> <start_port> <end_port>\n", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    int start_port = atoi(argv[2]);
    int end_port = atoi(argv[3]);

    if (start_port < 1 || end_port > 8080 || start_port > end_port) {  // scans the first 8080 ports, can be adjusted
        printf("Invalid port range\n");
        return 1;
    }
    printf("Scanning ports on %s from %d to %d\n", ip, start_port, end_port);
    scan_ports(ip, start_port, end_port);

    return 0;
}
