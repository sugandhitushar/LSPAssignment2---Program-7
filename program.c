#include"program.h"

int main(int argc, char *argv[])
{
	int fd;
	pid_t pid1,pid2;
	int status1,status2;
	
	fd = open("count.txt", O_RDWR | O_CREAT | O_TRUNC);
		
	if(fd == -1)
	{
		perror("open: count.txt");
		exit(EXIT_FAILURE);
	}
	else
	{
		if(fork() == 0)
		{
			int fd1, count1=0, readBytes, i;
			char buf[1024];
			
			fd1 = open("demo.txt",O_RDONLY);
			
			if(fd1 == -1)
			{
				perror("open: demo.txt");
				exit(EXIT_FAILURE);
			}
			else
			{
				while((readBytes = read(fd1,buf,sizeof(buf))) > 0)
				{
					for(i=0; i<readBytes; i++)
					{
						if(buf[i]>=65 && buf[i]<=90)
							count1++;
					}
				}
				
				sprintf(buf,"Capital letters in demo.txt are %d.\n",count1);
				
				write(fd,buf,strlen(buf));
				
				if(close(fd1) == -1)
					perror("close: demo.txt");
			}
		}
		else
		{
			int fd2, count2=0, readBytes, i;
			char buf[1024];
			
			fd2 = open("hello.txt",O_RDONLY);
			
			if(fd2 == -1)
			{
				perror("open: hello.txt");
				exit(EXIT_FAILURE);
			}
			else
			{
				while((readBytes = read(fd2,buf,sizeof(buf))) > 0)
				{
					for(i=0; i<readBytes; i++)
					{
						if(buf[i]>=65 && buf[i]<=90)
							count2++;
					}
				}
				
				sprintf(buf,"Capital letters in hello.txt are %d.\n",count2);
				
				write(fd,buf,strlen(buf));
				
				if(close(fd2) == -1)
					perror("close: demo.txt");
			}
		}
		
		pid1 = wait(&status1);
		pid2 = wait(&status2);
				
		if(close(fd) == -1)
			perror("close: count.txt");
	}
}

