#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

int main() {
    // 소켓 생성
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 주소 설정
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888); // 포트 설정
    server_address.sin_addr.s_addr = INADDR_ANY;

    // 바인딩
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    // 수신 대기
    listen(server_socket, 5);

    std::cout << "Server is listening..." << std::endl;

    // 클라이언트 연결 수락
    int client_socket = accept(server_socket, nullptr, nullptr);

    char buffer[1024];
    while (true) {
        // 클라이언트로부터 메시지 수신
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            std::cout << "Client disconnected." << std::endl;
            break;
        }

        std::cout << "Client: " << buffer << std::endl;

        // 클라이언트에게 메시지 전송 (에코)
        send(client_socket, buffer, bytes_received, 0);
    }

    // 소켓 닫기
    close(server_socket);
    close(client_socket);

    return 0;
}
