#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>

#define SOCKET_PATH "/tmp/chat_socket"
#define BUFFER_SIZE 256

// Function to handle exiting server
void handle_exit(int signum) {
    unlink(SOCKET_PATH);
    printf("\nServer shutting down...\n");
    exit(0);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUFFER_SIZE];

    // Handle Ctrl+C to remove socket file on exit
    signal(SIGINT, handle_exit);

    // Create socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);

    unlink(SOCKET_PATH); // Remove existing socket file if any

    // Bind socket
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 5) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("🚀 Server listening on %s...\n", SOCKET_PATH);

    while (1) {
        client_len = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd == -1) {
            perror("Accept failed");
            continue;
        }

        pid_t pid = fork();
        if (pid == 0) {  // Child process handles client
            close(server_fd);
            printf("✅ New client connected!\n");

            while (1) {
                memset(buffer, 0, BUFFER_SIZE);
                read(client_fd, buffer, BUFFER_SIZE);
                if (strcmp(buffer, "exit\n") == 0) break;

                printf("\n💬 Client: %s", buffer);

                printf("📝 You: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                write(client_fd, buffer, strlen(buffer));
            }

            printf("🚪 Client disconnected.\n");
            close(client_fd);
            exit(0);
        } else {
            close(client_fd);  // Parent doesn't need the client socket
        }
    }

    close(server_fd);
    return 0;
}
