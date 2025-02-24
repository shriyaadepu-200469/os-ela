#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>

#define SOCKET_PATH "/tmp/chat_socket"

void handle_client(int client_fd) {
    char buffer[256];

    printf("Client connected!\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        if (read(client_fd, buffer, sizeof(buffer)) <= 0) {
            perror("Read failed or client disconnected");
            break;
        }

        if (strcmp(buffer, "exit\n") == 0 || strcmp(buffer, "exit") == 0) {
            printf("Client disconnected.\n");
            break;
        }

        printf("Client: %s\n", buffer);

        printf("You: ");
        fgets(buffer, sizeof(buffer), stdin);
        write(client_fd, buffer, strlen(buffer));
    }

    close(client_fd);
    exit(0);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len;

    // Create socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Configure socket address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);
    
    unlink(SOCKET_PATH); // Remove existing socket file

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
    
    printf("Server listening on %s...\n", SOCKET_PATH);

    // Accept multiple client connections
    while (1) {
        client_len = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd == -1) {
            perror("Accept failed");
            continue;
        }

        // Fork a new process to handle the client
        pid_t pid = fork();
        if (pid == -1) {
            perror("Fork failed");
            close(client_fd);
        } else if (pid == 0) {  // Child process
            close(server_fd);   // Child doesn't need server socket
            handle_client(client_fd);
        } else {  // Parent process
            close(client_fd);  // Parent closes client socket, handled by child
        }
    }

    close(server_fd);
    unlink(SOCKET_PATH);
    return 0;
}
