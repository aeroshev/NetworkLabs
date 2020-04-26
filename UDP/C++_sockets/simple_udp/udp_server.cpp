/*
Программа UDP сервера
Гайд - https://rsdn.org/article/unix/sockets.xml
*/
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    //Создание сокета с UDP протоколом
    //0 - установка стандратного интерфейса UDP
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        std::cerr << "Error in create socket" << '\n';
        exit(1);
    }

    //Семейство адресов
    addr.sin_family = AF_INET;
    //Номер порта
    addr.sin_port = htons(3425);
    //IP - адрес
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //Связывание сокета с адресом
    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
        std::cerr << "Error in bind socket" << '\n';
        exit(1);
    }

    //Максимальный размер принимаемой датаграммы
    unsigned int optlen = sizeof(int);
    int optval;
    getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (int *)&optval, &optlen);
    std::cout << "Max size of message -> " << optval << '\n';

    while(1)
    {
        //Приём датаграмм
        bytes_read = recvfrom(sock, buf, 1024, 0, NULL, NULL);
        buf[bytes_read] = '\0';
        std::cout << buf << '\n';
    }

    return 0;
}