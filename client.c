#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){

  int buffer, total;
  printf("This is an addition calculator\nEnter one number at a time\n");
  mkfifo("pipe", 0644);
  while(1){
    int fd = open("pipe", O_WRONLY);
    scanf("%d", &buffer);
    write(fd, &buffer, sizeof(buffer));
    close (fd);
    int fd1 = open("pipe", O_RDONLY);
    read(fd, &total, sizeof(total));
    printf("Total: %d\n", total);
  }

}
