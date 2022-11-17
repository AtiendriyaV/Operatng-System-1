#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>


//declation of union structure
union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
           }a;

    //binary semaphore allocation
    int binarySemaphoreAllocation(key_t key, int semFlags)
    {
    return semget(key, 1, semFlags);
    }
 



void printInt(int val)
{
	char buf[6];
	int len;
	len =sprintf(buf," %d",val);
	write(1,buf,len);
}

int main(int argc, char *argv[])
{       

//value for semmget val 
	int id,val,i;
	//unsigned short arr[]={1,1,1,1,1};
	//unsigned short val=1;
	
	
	key_t k = 100;	//key
	a.val=1; 
	//a.array=arr;	
	
	//creation of semaphore
	id= semget(k,  1, IPC_CREAT|0777);
	
	if (id == -1)
	{
		write(1, "Create Error", 12);
		exit(0);
	}
	 
	 //initialization of semaphore
	val= semctl(id, 0, SETVAL, a);

	if (val <0 )
	{
		write(1, "Init Error", 10);
		exit(0);
	}
	
	//contrl the value of semaphore
	val= semctl(id,0, GETVAL, a);
	if (val <0 )
	{
		write(1, "Get Error", 9);
		exit(0);
	}
         
         //assigning value at 0th index	
	write(1,"Sem value at zeorth Index :", 28);
	printInt(val);	
  
    

}
        
