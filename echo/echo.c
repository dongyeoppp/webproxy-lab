# include "csapp.h"  

void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);    // rio 구조체 초기화 
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {      // rio_readlineb 함수가 EOF를 만날때까지 반복 // 데이터를 읽고 버퍼에 저장  
        printf("server received %d bytes\n", (int)n);
        Rio_writen(connfd, buf, n);     // 버퍼에 데이터를 client에 전송  
    }
}