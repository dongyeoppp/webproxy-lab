/* 두 개의 정수를 더하는 CGI 프로그램 */
#include "csapp.h"

int main(void)
{
  char *buf, *p, *new1_p, *new2_p;
  char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
  int n1 = 0, n2 = 0;

  /* Extract the two arguments */
  if ((buf = getenv("QUERY_STRING")) != NULL)
  {
    /* 숙제 11.10 */
    p = strchr(buf, '&'); // '&' 문자가 위치한 메모리 주소 저장
    *p = '\0';
    new1_p = strchr(buf, '='); // num1 = a 에서 '='을 기준으로 나눔 (new1_p +1 -> a)
    *new1_p = '\0';
    new2_p = strchr(p + 1, '='); // num2 = b 에서 '='을 기준으로 나눔 (new1_p +1 -> b)
    *new2_p = '\0';
    strcpy(arg1, new1_p + 1); // '&'를 기준으로 앞에 인자가 arg1
    strcpy(arg2, new2_p + 1); // '&를 기준으로 뒤에 인자가 arg2
    n1 = atoi(arg1);          // atoi()함수를 통해 문자열을 정수로 변환해준다.
    n2 = atoi(arg2);
  }

  /* Make the response body */
  sprintf(content, "QUERY_STRING=%s", buf);
  sprintf(content, "Welcome to add.com: ");
  sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
  sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>",
          content, n1, n2, n1 + n2);
  sprintf(content, "%sThanks for visiting!\r\n", content);

  /* Generate the HTTP response */
  // 클라이언트 터미널에 출력
  printf("Connection: close\r\n");
  printf("Content-length: %d\r\n", (int)strlen(content));
  printf("Content-type: text/html\r\n\r\n");
  if (strcmp(getenv("REQUEST_METHOD"), "HEAD")) // 메서드가 'HEAD'일 경우 content의 내용을 출력하지 않음  // QUERY_METHOD로 method 값 가져오기
    printf("%s", content);                      // content에 담은 내용을 출력
  fflush(stdout);                               // 출렦 버퍼를 비워주는 역할. 출력 버퍼에 있는 데이터를 목적지(터미널이나 파일 등)로 보내고 버퍼를 비워준다.

  exit(0);
}
/* $end adder */
