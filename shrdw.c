#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include<stdlib.h>

int main()
{
	char *buf, temp[25];
	int sid,val;
	
	// ftok to generate unique key
	key_t key = ftok("shmfile",5);
	

	// shmget returns an identifier in id
	sid = shmget(key,1024,0666|IPC_CREAT);

	//check error
	if (sid == -1)
	{
		write (1,"Shared memory Create Error",25);
		exit(0);
	}


	// shmat to attach to shared memory to the current process
	// void *shmat(int shmid, const void *shmaddr, int shmflg);

	buf = (char*) shmat(sid,(void*)0,0);
        
        //writing the value to be displayed in semaphore
        //storing it in val and reading them 
        
	write(1,"Enter details to shared memory",20);
	
	val=read(0,buf,20);
	
	write(1,"Details updated in shared memory",20);
	
	
	//detach from shared memory 
	//int shmdt(const void *shmaddr);
	val = shmdt(buf);
	
	//checking error
	
	if (val == -1)
	{
		write (1,"Shared memory Detach Error",15);
		exit(0);
	}
	return 0;
}
