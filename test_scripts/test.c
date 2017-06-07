#include <stdio.h>              /* I/O lib         C89   */
#include <sys/types.h>          /* UNIX types      POSIX */
#include <errno.h>              /* error stf       POSIX */
#include <stdlib.h>             /* Standard Lib    C89   */
#include <sys/stat.h>           /* UNIX stat       POSIX */
#include <sys/file.h>           /* Locks           UNIX  */
#include <linux/unistd.h>
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>

#define SH 0
#define EX 1
#define SYS_kflock 329

int main(int argc, char *argv[]) {
  
  int FD;
  int i;
  
  int key = atoi(argv[1]);
  int type = (strcmp(argv[2],"SH") == 0)? SH : EX;
  int ret;
  
  char buf[50];
  	
  if((FD = open("file", O_WRONLY | O_CREAT | O_APPEND, S_IRWXU|S_IRWXG|S_IRWXO)) < 0) {
    perror("ERROR: File open");
    exit(0);
  } 

  char *lck = (type == SH)?strdup("SH"):strdup("EX");
  
/*
  LOCK_SH shared lock 
  LOCK_EX exclusive lock 
  LOCK_NB don't block when locking 
  LOCK_UN unlock 
*/

  printf("Lock Wait %s %d\n",lck,key);
  
  if(key != -1){
		// Key supplied Call kflock
		
		if(type == SH){
			ret = syscall(SYS_kflock ,FD, LOCK_SH , key);
		}
		else{
			ret = syscall(SYS_kflock ,FD, LOCK_EX , key);
		}
		
	  }	
   else{
		// No key Call Original Flock;
		if(type == SH){
			ret = syscall(SYS_flock ,FD, LOCK_SH);
		}
		else{
			ret = syscall(SYS_flock ,FD, LOCK_EX);
		}
	}	  
  
  printf("Lock Acquired %s %d\n",lck,key);
   	
  sleep(2);
  
  sprintf(buf,"Written with %s lock key:%d \n",lck,key);
  write(FD,buf,strlen(buf));
  
  sleep(3);

  printf("Lock Free %s %d\n",lck,key);
  
  flock(FD, LOCK_UN);

  close(FD);	
} /* end func main */

