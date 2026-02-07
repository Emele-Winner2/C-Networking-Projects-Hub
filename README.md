# C Networking Projects Hub

This repository is a **collection of networking projects written in C**.
Its goal is to help you experiment with and learn different aspects of networking, including TCP/UDP, HTTP, embedded systems networking, and other protocols. Each project demonstrates low-level networking concepts using the **Berkeley sockets API** and cross-platform C code.

---

## 📌 Purpose

This repository is intended for:

- Learning **network programming** in C
- Exploring **different network protocols**
- Building **cross-platform networking applications**:
  - Desktop: Linux, macOS, Windows
  - Embedded devices: IoT, microcontrollers

- Practicing **TCP, UDP, HTTP, and custom protocols**
- Experimenting with **servers, clients, and network tools**

---

## 🗂️ Repository Structure

```
.
├── projects/
│   ├── TCP_Web_Server/       # Minimal web server example
│   ├── UDP_chat/             # UDP client/server experiments
│   ├── embedded_network/     # Network examples for microcontrollers
│   └── ...                   # Future projects
├── include/                  # Shared headers
├── Makefile                  # Optional global build script
└── README.md
```

Each subfolder contains **self-contained projects** with its own source files, headers, and possibly a local Makefile.

---

## ⚡ Example Projects

- **Minimal TCP Web Server** – A simple HTTP server returning local time
- **UDP Chat** – A basic UDP client/server for sending messages
- **Embedded Network Example** – Networking for microcontrollers using C and sockets
- **Custom Protocol Demo** – Experimenting with custom TCP or UDP protocols

> More projects will be added as experimentation continues.

---

## 🛠️ Building Projects

Each project may include its own **Makefile** or instructions.

Example for building a project:

```make
# Inside a project folder
main: main.c ../include/include.h
	gcc -Wall -I../include main.c -o main -lws2_32
```

Then run:

```sh
make
./main
```

> Adjust `-I../include` if your header paths are different.

---

## ▶️ Running Projects

Most projects are **command-line programs**:

- **Servers**: Run first to listen on a TCP/UDP port
- **Clients**: Connect to the server or send messages

Example usage:

```sh
# Run server
./server

# Connect from client
./client
```

---

## 📚 Key Concepts Covered

- TCP and UDP socket programming
- Client/Server architecture
- Manual HTTP handling
- Embedded networking concepts
- Cross-platform C networking (Winsock + POSIX)
- Low-level networking debugging and analysis

---

## 🤝 Contributing / Extending

This repository is designed to **grow over time**:

- Add new networking experiments
- Add comments, documentation, or diagrams
- Refactor existing projects for robustness
- Share custom protocols, simulations, or IoT networking experiments

---

## 📄 License

This project is for **educational purposes**.
You are free to use, modify, and experiment with the code.

---
