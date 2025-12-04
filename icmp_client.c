#include "net_impl.c"

void run_client(const char *dest_ip, const char *message) {
    int sockfd;
    char packet[sizeof(struct icmphdr) + PAYLOAD_SIZE];
    struct sockaddr_in dest_addr;
    struct icmphdr *icmp_header = (struct icmphdr *)packet;

    // IPPROTO_ICMP permet au système de gérer l'en-tête IP, nous gérons ICMP.
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); 
    if (sockfd < 0) {
        perror("Socket error (need root/sudo)");
        return;
    }

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, dest_ip, &dest_addr.sin_addr) <= 0) {
        perror("Invalid IP adress");
        close(sockfd);
        return;
    }

    // Type : 8 (Echo Request)
    icmp_header->type = ICMP_ECHO;
    // Code : 0
    icmp_header->code = 0;
    icmp_header->un.echo.id = 0;
    icmp_header->un.echo.sequence = 0;

    int data_len = strlen(message);
    if (data_len > PAYLOAD_SIZE) {
        data_len = PAYLOAD_SIZE; // Tronque si trop long
    }
    char *payload = (char *)(icmp_header + 1);
    memcpy(payload, message, data_len);
    
    int packet_len = sizeof(struct icmphdr) + data_len;
    icmp_header->checksum = 0; // Réinitialiser avant le calcul
    icmp_header->checksum = checksum(packet, packet_len);

    if (sendto(sockfd, packet, packet_len, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        perror("Sendto error");
    } else {
        printf("%sAn ICMP packet has been sent to %s\n", HEAD, dest_ip);
    }

    close(sockfd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "%sUsage: %s <destination IP> <message>\n", HEAD, argv[0]);
        return 1;
    }
    run_client(argv[1], argv[2]);
    return 0;
}
