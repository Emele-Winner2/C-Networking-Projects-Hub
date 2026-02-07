# Minimal TCP Web Server (C)

This project is a **minimal TCP-based web server written in C**.
It implements just enough of the HTTP/1.1 protocol to respond to a browser or `curl` request with the local system time.

The purpose of this project is **educational**: to understand how web servers work at the socket level without frameworks or abstractions.

---

## What This Is

- A **TCP server** using the Berkeley sockets API
- A **minimal HTTP server** implemented manually on top of TCP
- Cross-platform:
  - Windows (Winsock)
  - Linux / macOS (POSIX sockets)

Browsers can connect because the server sends correctly formatted HTTP response headers over a TCP connection.

---

## How It Works

1. Initializes the socket API (Winsock on Windows)
2. Creates a TCP socket
3. Binds to port **8080**
4. Listens for incoming connections
5. Accepts a single client
6. Reads the HTTP request
7. Sends an HTTP response containing the local system time
8. Closes the connection

HTTP handling is done manually by sending text over the TCP socket.

---

## Example HTTP Response

```http
HTTP/1.1 200 OK
Connection: close
Content-Type: text/plain

Local time is: Tue Feb  6 14:23:01 2026
```

---

## Building

### Using Make

A simple `Makefile` is provided.

```make
main: ./src/main.c
	gcc -Wall  ./src/main.c -o main -lws2_32

```

Build the project:

```sh
make
```

> On Windows (MinGW), `-lws2_32` is required to link against Winsock.
> On Linux/macOS, you may remove `-lws2_32` if it is not needed.

---

### Manual Build

#### Linux / macOS

```sh
gcc -Wall main.c -o main
```

#### Windows (MinGW)

```sh
gcc -Wall main.c -o main -lws2_32
```

---

## Running

```sh
./main
```

Then connect using a browser or `curl`:

```sh
curl http://localhost:8080
```

You should receive a plain-text response containing the local time.

---

## Project Structure

```
.
├── main.c
├── include/
│   └── include.h
└── Makefile
```

---

## Key Concepts Demonstrated

- TCP socket programming (`socket`, `bind`, `listen`, `accept`)
- Cross-platform networking in C
- Manual HTTP response construction
- Basic request/response handling
- Understanding how HTTP runs on top of TCP

---

## Possible Extensions

- Handle multiple clients in a loop
- Parse HTTP request lines and headers
- Support multiple routes (`/`, `/time`, etc.)
- Add `Content-Length`
- Use `select()` / `poll()` or threads
- Add IPv6 support
- Implement HTTPS using TLS

---

## License

This project is provided for educational purposes.
Use it, modify it, and break it to learn how networking works.

---
