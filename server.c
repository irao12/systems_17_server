
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

static void do_handshake(){
  printf("Starting Handshake, waiting for connection\n");
  //step -1: server creates pipe, waits for connection
  mkfifo("makeshift0", 0666);
  int fd = open("makeshift0", O_WRONLY);
  sleep(1);
  //step 1: client sends to server
  int fd1 = open("makeshift1", O_RDONLY);
  char buffer[100];
  read(fd1, &buffer, sizeof(buffer));
  printf("server received from client, client's pid: %s\n", buffer);
  remove("makeshift0");
  //step 2: server sends to client
  sprintf(buffer, "%d", getpid());
  write(fd, &buffer, sizeof(buffer));
  printf("server sent to client, server's pid: %s\n", buffer);
  //step 3: client sends to server
  char msg[100];
  read(fd1, msg, sizeof(msg));
  printf("%s", msg);
  close(fd);
  close(fd1);
  return;
}

void sighandler(int signo){
  if (signo == SIGINT){
    remove("makeshift0");
    exit(0);
  }
}

int main(){
  signal(SIGINT, sighandler);
  while (1){

  do_handshake();
  long buffer, cube;
  mkfifo("to_client", 0644);
  int fd = open("to_server", O_RDONLY);
  int fd1 = open("to_client", O_WRONLY);
  while(1){
    int hi = read(fd, &buffer, sizeof(buffer));
    if (buffer == -1221) break;
    if(hi)
    printf("cubing %ld\n", buffer);
    cube = buffer * buffer * buffer;
    write(fd1, &cube, sizeof(cube));
  }
  close (fd);
  close(fd1);
  }
  return 0;
}
