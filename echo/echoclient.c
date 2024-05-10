#include "csapp.h"

int main(int argc, char **argv) // argc: 입력 받은 인자 수 , argv : 입력받은 인자들의 배열  -> (./echoclient) (호스트 name or ip주소) (port 번호) 일 경우 argc ->3 이고 argv  배열에 인자들이 차례대로 들어간다.
{
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;

    if (argc != 3)
    { // 인자의 개수가 3이 아닐 경우 메시지 출력
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    host = argv[1]; // host 와 port 에 각각 ip주소와 port번호 저장
    port = argv[2];
    // open_clientfd 함수를 통해 socket()-> socket을 만들고, connect() 실행 
    clientfd = Open_clientfd(host, port); // host에서 돌아가면서 port에 연결 요청을 드는 서버와 연결을 설정한다. 준비된 열린 소켓 식별자를 리턴하여 clientfd에 저장
    Rio_readinitb(&rio, clientfd);        // rio 구조체를 초기화하고 clientfd에 대한 읽기 작업을 수행할 수 있도록 설정한다.

    while (Fgets(buf, MAXLINE, stdin) != NULL)  // eof 표준을 만나면 종료
    {                                           // while문을 통해 사용자로부터 입력을 buf에 저장
        Rio_writen(clientfd, buf, strlen(buf)); // client 식별자를 통해 buf에 저장된 데이터를 서버로 전송 (buf에 데이터를 server에 전송)
        Rio_readlineb(&rio, buf, MAXLINE);      // rio 구조체를 통해 읽어온 한 줄의 문자열을 buf에 저장 (리턴 코드가 0일 경우 eof 감지)
        Fputs(buf, stdout);                     // buf에 저장된 문자열을 출력 (받은 응답 화면에 출력)
    }
    Close(clientfd); // client 소켓 닫기
    exit(0);
}