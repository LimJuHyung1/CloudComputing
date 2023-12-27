#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

int main() {
    // ���� ����
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // �ּ� ����
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888); // ���� ��Ʈ
    server_address.sin_addr.s_addr = INADDR_ANY;

    // ������ ����
    connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    std::cout << "Connected to server." << std::endl;

    char message[1024];
    while (true) {
        std::cout << "Enter message: ";
        std::cin.getline(message, sizeof(message));

        // ������ �޽��� ����
        send(client_socket, message, strlen(message), 0);

        // �����κ��� �޽��� ����
        memset(message, 0, sizeof(message));
        int bytes_received = recv(client_socket, message, sizeof(message), 0);
        if (bytes_received <= 0) {
            std::cout << "Server disconnected." << std::endl;
            break;
        }

        std::cout << "Server: " << message << std::endl;
    }

    // ���� �ݱ�
    close(client_socket);

    return 0;
}
