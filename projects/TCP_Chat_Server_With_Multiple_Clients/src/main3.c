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
    // initialized Server address
    struct addrinfo Server_adress;
    memset(&Server_adress, 0, sizeof(Server_adress));
    Server_adress.ai_flags = AI_PASSIVE;
    Server_adress.ai_family = AF_INET; // for now I am making it only able to accept ipv4 connections
    Server_adress.ai_socktype = SOCK_STREAM;
    Server_adress.ai_protocol = 0;
    struct addrinfo *pointer_address;
    if (getaddrinfo(NULL, "8080", &Server_adress, &pointer_address) != 0)
    {
        fprintf(stderr, "getaddrinfo failed\n");
        return 1;
    }

    SOCKET main2 = socket(pointer_address->ai_family, pointer_address->ai_socktype, pointer_address->ai_protocol);
    // checking if socket was initialized successfully....
    if (!ISVALIDSOCKET(main2))
    {
        printf("SOCKET WAS INITIALIZED UNSUCCESSFULLY ,ERROR:%d\n", GETSOCKETERRNO());
        return 1;
    }

    // Bind the socket and checking for success to the listening address and port no....
    if (bind(main2, pointer_address->ai_addr, pointer_address->ai_addrlen))
    {
        printf("THE SOCKET BINDING WAS UNSUCCESSFUL ,ERROR:%d\n", GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(pointer_address); // freeing the previous pointer to addrinfo

    // The server is in a state of listening
    if (listen(main2, SOMAXCONN))
    {
        printf("Listening failed ERROR:%d", GETSOCKETERRNO());
        return 1;
    }

    struct sockaddr_storage User;
    int len = sizeof(User);
    // initialize the client socket with the accept() function
    SOCKET client = accept(main2, (struct sockaddr *)&User, &len);
    if (!ISVALIDSOCKET(client))
    {
        printf("socket initialization failed error:%d\n", GETSOCKETERRNO());
        return 1;
    }
    // Receiving HTTP request from browser
    char buffer[1024];
    int bytes = (recv(client, buffer, 1024, 0));
    printf("%d of 1024 bytes received\n", bytes);
    // Error Check
    if (bytes <= 0)
    {
        printf("failed to process http request from browser\n");
        return 1;
    }

    if (strstr(buffer, "Upgrade: websocket"))
    { // Did not implement the Websocket upgrade myself used an already available implementation. sigh....
        // Extract Sec-WebSocket-Key
        char *key_header = strstr(buffer, "Sec-WebSocket-Key:");
        if (key_header)
        {
            char key[256] = {0};
            sscanf(key_header, "Sec-WebSocket-Key: %255s", key);

            // Calculate Sec-WebSocket-Accept from key
            char accept_key[256];
            // You need to SHA1 + Base64 the key here
            // For now, just use a placeholder (not a valid WS handshake)
            snprintf(accept_key, sizeof(accept_key), "<calculated-value>");

            char ws_response[512];
            snprintf(ws_response, sizeof(ws_response),
                     "HTTP/1.1 101 Switching Protocols\r\n"
                     "Upgrade: websocket\r\n"
                     "Connection: Upgrade\r\n"
                     "Sec-WebSocket-Accept: %s\r\n\r\n",
                     accept_key);

            send(client, ws_response, strlen(ws_response), 0);

            // Now WebSocket is open and you can start sending/receiving frames
            printf("WebSocket handshake complete\n");
            // Implement frame-based message handling here
        }
    }
    else
    {
        // --- Serve HTML page ---
        char *html_response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<!DOCTYPE html>"
            "<html lang=\"en\">"
            "<head>"
            "<meta charset=\"UTF-8\">"
            "<title>Chat Room</title>"
            "<style>"
            "body{margin:0;padding:0;font-family:Segoe UI,Arial,sans-serif;"
            "background:linear-gradient(135deg,#1d2671,#c33764);"
            "height:100vh;display:flex;justify-content:center;"
            "align-items:center;color:#fff;}"

            /* ADD THIS */
            ".connect-btn{position:absolute;top:15px;left:15px;"
            "padding:8px 14px;border:none;border-radius:20px;"
            "background:linear-gradient(135deg,#1d2671,#c33764);color:#000;font-weight:bold;cursor:pointer;}"
            ".connect-btn:hover{background:#16a085;}"

            /* existing UI */
            ".chat-container{width:360px;background:#111;border-radius:16px;"
            "box-shadow:0 20px 40px rgba(0,0,0,.4);display:flex;"
            "flex-direction:column;overflow:hidden;}"
            ".chat-header{padding:16px;background:#1f1f1f;text-align:center;"
            "font-weight:bold;letter-spacing:1px;border-bottom:1px solid #333;}"
            ".chat-messages{flex:1;padding:16px;font-size:14px;"
            "color:#aaa;overflow-y:auto;}"
            ".chat-messages p{margin:0 0 10px;}"
            ".chat-input{display:flex;padding:12px;background:#1f1f1f;"
            "border-top:1px solid #333;}"
            ".chat-input input{flex:1;padding:10px 12px;border-radius:20px;"
            "border:none;outline:none;font-size:14px;}"
            ".chat-input button{margin-left:10px;padding:10px 16px;"
            "border-radius:20px;border:none;background:#c33764;color:#fff;"
            "font-weight:bold;cursor:pointer;}"
            ".chat-input button:hover{background:#ff4f8b;}"
            "</style>"
            "<script>"
            "const ws = new WebSocket('ws://10.208.91.39:8080/chat');"   // Connect to your C server"
            "ws.onopen = () => { console.log('Connected to server'); };" // Connection opened"
            "ws.onmessage = (event) => {"                                // Incoming message"
            "   const messages = document.querySelector('.chat-messages');"
            "   const p = document.createElement('p');"
            "   p.textContent = event.data;"
            "   messages.appendChild(p);"
            "};"
            "ws.onclose = () => { console.log('Disconnected from server'); };"
            "ws.onerror = (err) => { console.error('WebSocket error:', err); };"
            "const sendBtn = document.querySelector('.chat-input button');"
            "const input = document.querySelector('.chat-input input');"
            "sendBtn.onclick = () => {"
            "   if (input.value) {"
            "       ws.send(input.value);"
            "       input.value = '';"
            "   }"
            "};"
            "</script>"
            "</head>"
            "<body>"

            /* ADD THIS */
            "<button class=\"connect-btn\" onclick=\"connectDevice()\">Connect</button>"

            "<div class=\"chat-container\">"
            "<div class=\"chat-header\">💬 COOL CHAT ROOM</div>"
            "<div class=\"chat-messages\">"
            "<p>✨ Welcome to the chat!</p>"
            "<p>👋 Say hi and start typing…</p>"
            "</div>"
            "<div class=\"chat-input\">"
            "<input type=\"text\" placeholder=\"Type your message…\" />"
            "<button>Send</button>"
            "</div>"
            "</div>"
            "</body>"
            "</html>";
        send(client, html_response, strlen(html_response), 0);
    }
    printf("THE PROGRAM RAN SUCCESSFULLY");
    CLOSESOCKET(main2);
    CLOSESOCKET(client);
#if defined(_WIN32)
    WSACleanup();
#endif
}