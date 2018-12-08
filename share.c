#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

int main(){
  int shmid = shmget(12345,200, 0644| IPC_CREAT);
  printf("shmid: %d\n",shmid);
  char * data = shmat(shmid, 0, 0);
  if (data == (char *)(-1)){
    printf("There has been an error with shmat\n");
    exit(1);
  }
  if (*data == '\0'){
    printf("You have just created this shared memory segment.\n");
  }
  else {
    printf("Contents:\n%s\n",data);
  }
  char change[100];
  int change_responded = 0;
  while(!change_responded){
    printf("Do you want to change the data in this shared segment? (y/n): ");
    fgets(change,100,stdin);
    change[strlen(change) - 1] = '\0';
    if (strcmp(change,"y") == 0){
      change_responded = 1;
      printf("Please input a string to write into that segment: ");
      fgets(data,200,stdin);
      data[strlen(data) - 1] = '\0';
      printf("\"%s\"\nhas been written to the shared memory!\n",data);
    }
    else if (strcmp(change,"n") == 0){
      change_responded = 1;
      printf("Ok, then we won't change it then.\n");
    }
    else{
      printf("Please enter \"y\" or \"n\" and then press <ENTER> please.\n");
    }
  }

  char delete[100];
  int delete_responded = 0;
  while (!delete_responded){
    printf("\nDo you want to delete the shared memory segment? (y/n):");
    fgets(delete,100,stdin);
    delete[strlen(delete) - 1] = '\0';
    if (strcmp(delete,"y") == 0){
      delete_responded = 1;
      shmctl(shmid, IPC_RMID, NULL);
      printf("The memory segment has been deleted!\n");
    }
    else if (strcmp(delete,"n") == 0){
      delete_responded = 1;
      printf("Ok, we won't delete it.\n");
      if (shmdt(data) == -1){
        printf("There has been an error with shmdt\n");
        exit(1);
      }
    }
    else{
      printf("Please enter \"y\" or \"n\" and then press <ENTER> please.\n");
    }
  }


  return 0;
}
