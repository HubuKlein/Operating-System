#include <stdio.h>
#include <unistd.h>

#define LOOP 3

int main()
{
	pid_t pid;
	int i;

	for (i = 0; i < LOOP; i++) {
		pid = fork();

		if (pid == 0) 
			printf("Child Process: PID = %d		My parent is %d\n", getpid(), getppid());
		// else if (pid > 0) {
		// 	printf("Parent Process: PID = %d\n", getpid());
		// } else {
		// 	printf("Fork Error!\n");
		// }
	}

	return 0;
}