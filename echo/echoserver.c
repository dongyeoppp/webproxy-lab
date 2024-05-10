# include "csapp.h"
# include "echo.c"

void echo(int connfd);

int main(int argc, char **argv)

{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;     // clientaddr은 accept로 보내지는 소켓 주소 구조체  // sockaddr_storage 구조체는 모든 형태의 소켓 주소를 저장하기에 충분히 크며, 코드를 프로토콜 - 독립적으로 유지해준다.   
    char client_hostname[MAXLINE], client_port[MAXLINE];

    if (argc != 2) {        // 인자가 2개 아닐 경우 메시지 출력 
        fprintf(stderr, "usage: %s <port>\n", argv[0]); 
        exit(0);
    }
    
    listenfd = Open_listenfd(argv[1]);      // 듣기 식별자를 오픈한 후에 무한루프에 진입한다.  // Open_listenfd() 함수는 socket(), bind(), listen() 함수 실행  // connect 요청을 기다리는 상태  
    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);  // accept를 통해 client 연결 수락, client와의 통신을 위한 연결 소켓 식별자 'connfd'반환  // connect 요청을 accept를 통해 연결  
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);  //연결된 client 이름(호스트 이름)과 port번호 얻음   
        printf("Connected to (%s, %s)\n", client_hostname, client_port); // 연결된 client의 hostname과 port 번호 출력, client와 server가 연결되었음을 알림   
        echo(connfd);
        Close(connfd);
    }
    exit(0);
}