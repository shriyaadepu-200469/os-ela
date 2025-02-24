# UNIX Domain Socket Chat Application

This project is a simple chat application using **UNIX domain sockets** in C. It consists of a **server** (`server.c`) and a **client** (`client.c`) that communicate over a UNIX socket file.

## Features
- Uses **AF_UNIX (PF_LOCAL)** socket communication.
- Supports **bi-directional** chat between client and server.
- Allows multiple clients to connect to the server.
- Uses **non-blocking I/O** for interactive messaging.
- Ensures **graceful termination** upon disconnection.

## Prerequisites
- A Linux-based operating system (**Red Hat Linux recommended**).
- **GCC compiler** installed.
- Basic understanding of **sockets and inter-process communication (IPC)**.

## Compilation
To compile the server and client programs, run:
```sh
make
```
Or manually compile using:
```sh
gcc server.c -o server
gcc client.c -o client
```

## Usage
### Start the Server
Run the server first:
```sh
./server
```
By default, it listens on the UNIX socket file: `/tmp/chat_socket`.

### Start the Client
Open another terminal and run the client:
```sh
./client
```
This will connect the client to the server.

### Chatting
- The server and client can now exchange messages.
- To exit, type `exit` and press Enter.

## Example Session
```
Server:
$ ./server
Server listening on /tmp/chat_socket...
Client connected!
Client: Hello, Server!
You: Hi, Client!
```

```
Client:
$ ./client
Connected to server. Type 'exit' to quit.
You: Hello, Server!
Server: Hi, Client!
```

## Code Explanation
### `server.c`
- Creates a **UNIX domain socket**.
- Binds to `/tmp/chat_socket`.
- Waits for a client to connect.
- Reads messages from the client and responds.
- Closes the connection upon receiving `exit`.

### `client.c`
- Connects to the **UNIX domain socket**.
- Sends messages to the server.
- Reads responses from the server.
- Exits on `exit` command.

## Cleanup
After running the server, manually remove the socket file to avoid conflicts:
```sh
rm -f /tmp/chat_socket
```

## Troubleshooting
### **Permission Denied for Socket File**
Run:
```sh
chmod 666 /tmp/chat_socket
```

### **Port Already in Use**
If you see `Bind failed: Address already in use`, remove the existing socket file:
```sh
rm /tmp/chat_socket
```
# 🗨️ Internet Domain Socket Chat Application  

This project is a simple **client-server chat application** using **Internet domain sockets (TCP/IP)** in C. The server can handle multiple clients and broadcast messages between them.

## Features  
- Uses **AF_INET (TCP/IP)** socket communication.  
- Supports **multiple clients** using `select()`.  
- Allows **real-time bi-directional messaging**.  
- Ensures **graceful termination** on client disconnect.  

---

## Prerequisites  
- **Linux/macOS** (or **Windows with WSL**).  
- **GCC compiler** installed.  
- Basic understanding of **network programming** and **sockets**.  

---

## License
This project is open-source and available under the **MIT License**.

## Authors
[saipradhamkanth(23071A3218),rithika(23071A3219),shriya(23071A3202),bhanu(23071A3204)] - Created this project for learning and demonstration purposes.

---
Feel free to contribute, open issues, or fork this project! 🚀
