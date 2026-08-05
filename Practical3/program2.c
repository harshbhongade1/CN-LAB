#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUF_SIZE 1098

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buffer[BUF_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr *)&server, sizeof(server));

    listen(server_fd, 5);

    client_fd = accept(server_fd, (struct sockaddr *)&client, &len);

    while (1) {
        memset(buffer, 0, BUF_SIZE);

        int n = read(client_fd, buffer, BUF_SIZE);
        if (n <= 0)
            break;

        printf("Client: %s", buffer);

        send(client_fd, buffer, n, 0);
    }

    close(client_fd);
    close(server_fd);

    return 0;
}
