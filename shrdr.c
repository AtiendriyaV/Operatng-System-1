#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include<stdlib.h>

int main()
{
	char *buf, temp[25];
	int sid,val;
	int *data;
	// ftok to generate unique key
	key_t key = ftok("shmfile",5);
	

	// shmget returns an identifier in id
	sid = shmget(key,1024,0666|IPC_CREAT);
        
        
        //checking value error
        
	if (sid == -1)
	{
		write (1,"Shared memory Access Error",25);
		exit(0);
	}

	write(1,"Shared memory Details",20);

	// shmat to attach to shared memory to the current process
	// void *shmat(int shmid, const void *shmaddr, int shmflg);
	
	//putting data in and attachig it to semaphore
	
	buf = (char*) shmat(sid,(void*)0,0);
	//data = (int*) shmat(sid,(void*)0,0)
	
	//writing the value in the variable in val
	val=write(1,buf,10);
	
	
	//detach from shared memory 
	//int shmdt(const void *shmaddr);
	
	val = shmdt(buf);
	
	//checking value error
	
	if (val == -1)
	{
		write (1,"Shared memory Detach Error", 26);
		exit(0);
	}
	return 0;
}
