#include "net_impl.c"

void run_server() {
    int sockfd;
    char buffer[BUF_SIZE];
    ssize_t bytes_received;

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("Socket error (need root/sudo)");
        return;
    }

    printf("%sICMP server is listening...\n", HEAD);

    while (1) {
        bytes_received = recv(sockfd, buffer, BUF_SIZE, 0);

        if (bytes_received > 0) {
            struct iphdr *ip_header = (struct iphdr *)buffer;
            struct icmphdr *icmp_header = (struct icmphdr *)(buffer + (ip_header->ihl * 4));

            if (icmp_header->type == ICMP_ECHO) {
                char *payload = (char *)(icmp_header + 1);
                
                int payload_len = bytes_received - (ip_header->ihl * 4) - sizeof(struct icmphdr);

                if (payload_len > 0) {
                    if (payload_len > PAYLOAD_SIZE) payload_len = PAYLOAD_SIZE;
                    payload[payload_len] = '\0'; 

                    struct in_addr src_addr;
                    src_addr.s_addr = ip_header->saddr;

                    printf("%sReceived %s: %s\n", HEAD,  inet_ntoa(src_addr), payload);
                }
            }
        }
    }
    close(sockfd);
}

int main() {
    run_server();
    return 0;
}
