#include <iostream>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <unistd.h>  
#include <cstring>  
  
#define PORT 8080  
  
int main() {  
    int server_fd, new_socket;  
    struct sockaddr_in address;  
    int addrlen = sizeof(address);  
    char buffer[1024] = {0};  
    int opt = 1;  
    int addrlen_size;  
  
    // 创建 socket 文件描述符  
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
  
    // 绑定 socket 到 localhost 和端口 8080  
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons(PORT);  
  
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
  
    // 监听端口  
    if (listen(server_fd, 3) < 0) {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
  
    // 接受连接  
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {  
        perror("accept");  
        exit(EXIT_FAILURE);  
    }  
  
    // 读取数据  
    read(new_socket, buffer, 1024);  
    std::cout << "Message from client: " << buffer << std::endl;  
  
    // 发送数据  
    send(new_socket, buffer, strlen(buffer), 0);  
    std::cout << "Hello message sent\n";  
  
    // 关闭socket  
    close(server_fd);  
    return 0;  
}