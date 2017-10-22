#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main( void ) {

  pid_t pid;
  int child_status;

  pid = fork();
  if (pid < 0) {
    printf("Error occurred.\n");
	 return -1;
  } else if (pid == 0) {
    printf("Hello from the child process.\n");
    return 42;
  } else {
	 printf("This is the parent speaking.\n"); 
    wait( &child_status );
	 printf("Child returned %d\n", child_status );
  }

  printf("PID returned: %d\n", pid);

  return 0;
}

