
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){

  int buffer;
  int total = 0;
  mkfifo("pipe", 0644);
  while(1){
    int fd = open("pipe", O_RDONLY);
    read(fd, &buffer, sizeof(buffer));
    close(fd);
    printf("adding %d\n", buffer);
    total += buffer; 
    int fd1 = open("pipe", O_WRONLY);
    write(fd1, &total, sizeof(total));
    close(fd1);
  }

}
