Perfect! I can edit your README so it matches your **echo server** project instead of a “local time server,” keeping the polished style and structure. Here’s the **updated version**:

---

# Minimal TCP Echo Web Server (C)

This project is a **minimal TCP-based web server written in C**.
It implements enough of the HTTP/1.1 protocol to respond to a browser or `curl` request by **echoing a user-provided message**.

The purpose of this project is **educational**: to understand how web servers work at the socket level without frameworks or abstractions.

---

## What This Is

- A **TCP server** using the Berkeley sockets API
- A **minimal HTTP server** implemented manually on top of TCP
- Cross-platform:
  - Windows (Winsock)
  - Linux / macOS (POSIX sockets)

Browsers or HTTP clients can connect because the server sends correctly formatted HTTP response headers over a TCP connection.

---

## How It Works

1. Prompts the user to enter a message to echo
2. Initializes the socket API (Winsock on Windows)
3. Creates a TCP socket
4. Binds to port **8080**
5. Listens for incoming connections
6. Accepts a single client connection
7. Reads the client’s HTTP request
8. Sends an HTTP response containing the user’s message
9. Closes the connection

All HTTP handling is done manually by sending text over the TCP socket.

---

## Example HTTP Response

If the user entered `Hello, world!`, the response will look like:

```http
HTTP/1.1 200 OK
Connection: close
Content-Type: text/plain

Echo: Hello, world!
```

> Note: The server may receive the full HTTP request, including headers, which can be larger than the original message.

---

## Building

### Using Make

A simple `Makefile` can be used:

```make
main: ./src/main2.c
	gcc -Wall  ./src/main2.c -o main -lws2_32

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
gcc -Wall main2.c -o main
```

#### Windows (MinGW)

```sh
gcc -Wall main2.c -o main -lws2_32
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

You should receive a plain-text response containing the message you entered when the server started.

---

## Project Structure

```
.
├── main2.c
├── include/
│   └── include.h
└── Makefile
```

---

## Key Concepts Demonstrated

- TCP socket programming (`socket`, `bind`, `listen`, `accept`)
- Cross-platform networking in C
- Manual HTTP response construction
- Handling a single client request
- Understanding how HTTP runs on top of TCP

---

## Possible Extensions

- Handle multiple clients in a loop
- Parse HTTP request lines and headers
- Support multiple routes (`/`, `/echo`, etc.)
- Add `Content-Length` support
- Use `select()` / `poll()` or threads
- Add IPv6 support
- Implement HTTPS using TLS

---

## License

This project is provided for educational purposes.
Use it, modify it, and experiment to learn how networking works.

---
