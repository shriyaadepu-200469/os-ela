# 🗨️ Chat Application using UNIX and Internet Sockets

##  Overview
This project is a simple **multi-client chat application** that supports **both UNIX domain sockets and Internet domain sockets**. The server can handle multiple clients and broadcast messages between them.

## Features
- Supports **both UNIX domain sockets** (local IPC) and **Internet sockets** (TCP networking).
- Multi-client chat functionality using `select()`.
- Simple command-line interface.
- Supports **Linux/macOS** (for UNIX & Internet sockets) and **Windows (Internet sockets only).**

---

##  Installation & Compilation

### ** Requirements**
- `gcc` (C compiler)
- Linux/macOS (for UNIX & Internet sockets) or Windows with **WSL** (for full support)

### ** Clone the Repository**
```bash
git clone https://github.com/yourusername/chat-app.git
cd chat-app
