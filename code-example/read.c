#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main( int argc, char** argv ) {

  int fd = open( "filename.txt", O_RDONLY );
  printf( "Open returned %d\n", fd );
  char* buf[12]; 
  read(fd, buf, 12);
  printf("Read: %s\n", buf); 
  close(fd);

  return 0;

}
