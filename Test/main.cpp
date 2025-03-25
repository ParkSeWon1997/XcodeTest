#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[])
{
    
    const char* serverIP[1];
    int hSocket;
    char message[30] = {};
    struct sockaddr_in servAddr;

    // 소켓 생성
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (hSocket == -1) {
        perror("[Fail] socket()");
        return -1;
    }

    // 서버 주소 설정
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr("000.000.000.000");  // 로컬 테스트
    servAddr.sin_port = htons(8888);

    // 연결 시도
    if (connect(hSocket, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1) {
        perror("[Fail] connect()");
        close(hSocket);
        return -1;
    }

    // 데이터 수신
    int strLen = recv(hSocket, message, sizeof(message) - 1, 0);
    if (strLen == -1) {
        perror("[Fail] recv()");
        close(hSocket);
        return -1;
    }

    message[strLen] = 0;
    printf("Message from server: %s\n", message);

    close(hSocket);
    return 0;
}
