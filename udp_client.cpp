/*
Программа UDP клиента
Гайд - https://rsdn.org/article/unix/sockets.xml
*/
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//Библиотека необходимая для MacOS
//Link - https://github.com/pocoproject/poco/issues/46
#include <unistd.h>


char msg1[] = "Hello there!\n";
char msg2[] = "Obi van!\n";

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in addr;

    //создание сокета с UDP протоколом
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        std::cerr << "Error create socket" << '\n';
        exit(1);
    }

    //Семейство адресов
    addr.sin_family = AF_INET;
    //Номер порта
    addr.sin_port = htons(3425);
    //IP - адрес
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    //Максимальный размер отправляемой датаграммы
    unsigned int optlen = sizeof(int);
    int optval;
    getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (int *)&optval, &optlen);
    std::cout << "Max size of message -> " << optval << '\n';

    //Отправка первой датаграммы
    sendto(sock, msg1, sizeof(msg1), 0, (struct sockaddr *) &addr, sizeof(addr));

    //Установка соедения
    connect(sock, (struct sockaddr *) &addr, sizeof(addr));
    send(sock, msg2, sizeof(msg2), 0);

    //Закрытие сокета
    close(sock);

    return 0;
}