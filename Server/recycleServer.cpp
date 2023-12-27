#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

int main() {
    // ���� ����
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // �ּ� ����
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888); // ��Ʈ ����
    server_address.sin_addr.s_addr = INADDR_ANY;

    // ���ε�
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    // ���� ���
    listen(server_socket, 5);

    std::cout << "Server is listening..." << std::endl;

    // Ŭ���̾�Ʈ ���� ����
    int client_socket = accept(server_socket, nullptr, nullptr);

    char buffer[1024];
    while (true) {
        // Ŭ���̾�Ʈ�κ��� �޽��� ����
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            std::cout << "Client disconnected." << std::endl;
            break;
        }

        std::cout << "Client: " << buffer << std::endl;

        // Ŭ���̾�Ʈ���� �޽��� ���� (����)
        send(client_socket, buffer, bytes_received, 0);
    }

    // ���� �ݱ�
    close(server_socket);
    close(client_socket);

    return 0;
}
