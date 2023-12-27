#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

int main() {
    // 소켓 생성
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 주소 설정
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888); // 서버 포트
    server_address.sin_addr.s_addr = INADDR_ANY;

    // 서버에 연결
    connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    std::cout << "Connected to server." << std::endl;

    char message[1024];
    while (true) {
        std::cout << "Enter message: ";
        std::cin.getline(message, sizeof(message));

        // 서버로 메시지 전송
        send(client_socket, message, strlen(message), 0);

        // 서버로부터 메시지 수신
        memset(message, 0, sizeof(message));
        int bytes_received = recv(client_socket, message, sizeof(message), 0);
        if (bytes_received <= 0) {
            std::cout << "Server disconnected." << std::endl;
            break;
        }

        std::cout << "Server: " << message << std::endl;
    }

    // 소켓 닫기
    close(client_socket);

    return 0;
}
