#include "../include/include.h"
int main()
{
#if defined(_WIN32)
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d))
    {
        fprintf(stderr, "Failed to initialize.\n");
        return 1;
    }
#endif
    printf("what message do you wanna echo pls dont exceed 100 character\n"); // this is prolly not safe right now but lets roll with it.
    char message[100];
    scanf("%[^\n]", message);
    struct addrinfo helloworld;
    memset(&helloworld, 0, sizeof(helloworld));
    helloworld.ai_flags = AI_PASSIVE;
    helloworld.ai_protocol = 0;
    helloworld.ai_socktype = SOCK_STREAM;
    helloworld.ai_family = PF_INET;
    struct addrinfo *point;
    getaddrinfo(0, "8080", &helloworld, &point);
    // initialized the server address

    printf("creating socket....\n");
    SOCKET sock = socket(point->ai_family, point->ai_socktype, point->ai_protocol);

    if (!ISVALIDSOCKET(sock))
    {
        printf("socket initialization failed error:%d\n", GETSOCKETERRNO());
    }

    printf("binding the socket\n");
    if (bind(sock, point->ai_addr, point->ai_addrlen))
    {
        printf("binding the socket failederror:%d\n", GETSOCKETERRNO());
    }
    freeaddrinfo(point);
    printf("Listening...\n");
    if (listen(sock, 10) < 0)
    {
        printf("the socket failed at listening error: %d\n", GETSOCKETERRNO());
    }

    printf("Accepting...\n");
    struct sockaddr_storage clientaddr;
    socklen_t client_len = sizeof(clientaddr);
    SOCKET client = accept(sock, (struct sockaddr *)&clientaddr, &client_len); // the server has accepted connection from client
    if (!ISVALIDSOCKET(client))
    {
        printf("socket initialization failed error:%d\n", GETSOCKETERRNO());
    }
    char sen[1024];
    int x = recv(client, sen, 1024, 0);
    printf("receive %d bytes", x);
    // sending response
    const char *response =
        // a simple HTTP header
        "HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-Type: text/plain\r\n\r\n"
        "Echo: ";
    send(client, response, strlen(response), 0);
    int bytes = send(client, message, strlen(message), 0);
    printf("bytes sent: %d of %d\n", bytes, (int)strlen(message));
    printf("closing sockets\n");
    CLOSESOCKET(client);
    CLOSESOCKET(sock);
    printf("program has ran successfully");
#if defined(_WIN32)
    WSACleanup();
#endif
}