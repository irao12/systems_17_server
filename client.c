#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

void do_handshake(){
  int test;
  printf("Starting Handshake\n");
  //step -1: server creates pipe, waits for connection
  int fd = open("makeshift0", O_RDONLY);
  wait(1);
  //step 0: client creates pipe
  mkfifo("makeshift1", 0666);
  int fd1 = open ("makeshift1", O_WRONLY);
  //step 1: client sends to server
  test = 100;
  write(fd1, &test, sizeof(test));
  printf("client sent to server\n");
  //step 2: server sends to client
  read(fd, &test, sizeof(test));
  if (test == 200) printf("client received from server\n");
  //step 3: client sends to server
  char msg[] = "Handshake Complete\n\n";
  write(fd1, msg, sizeof(msg));
  printf("%s", msg);
  remove("makeshift1");

  return;
}

void sighandler(int signo){
  if (signo == SIGINT){
    remove("to_server");
    remove("to_client");
    exit(0);
  }
}

int main(){
  signal(SIGINT, sighandler);
  do_handshake();
  int buffer, cube;
  printf("This finds the volume of a cube\nEnter the side length\n");

    int fd = open("to_server", O_WRONLY);
    int fd1 = open("to_client", O_RDONLY);

  while(1){
    scanf("%d", &buffer);
    write(fd, &buffer, sizeof(buffer));
    read(fd1, &cube, sizeof(cube));
    printf("Volume: %d\n", cube);
  }

}
