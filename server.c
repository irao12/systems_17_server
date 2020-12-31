
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

static void do_handshake(){
  printf("Starting Handshake\n");
  //step -1: server creates pipe, waits for connection
  mkfifo("makeshift0", 0666);
  int fd = open("makeshift0", O_WRONLY);
  //step 1: client sends to server
  int fd1 = open("makeshift1", O_RDONLY);
  int test;
  read(fd1, &test, sizeof(test));
  if (test == 100) printf("server received from client\n");
  //step 2: server sends to client
  test = 200;
  write(fd, &test, sizeof(test));
  printf("server sent to client\n");
  //step 3: client sends to server
  char msg[100];
  read(fd1, msg, sizeof(msg));
  printf("%s", msg);
  remove("makeshift0");
  return;
}

static void sighandler(int signo){
  if (signo == SIGPIPE){
	do_handshake();
  }
}

int main(){
  signal(SIGPIPE, sighandler);
  do_handshake();
  int buffer;
  int cube;
  mkfifo("to_client", 0644);
  mkfifo("to_server", 0644);
  int fd = open("to_server", O_RDONLY);
  int fd1 = open("to_client", O_WRONLY);

  while(1){
    int hi = read(fd, &buffer, sizeof(buffer));
    if(hi)
    printf("cubing %d\n", buffer);
    cube = buffer * buffer * buffer;
    write(fd1, &cube, sizeof(cube));
  }

}
