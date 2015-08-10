#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define MAXARGS 512
#define MAXLINE 512


void eval(char* cmdline);
int parseline(char* buf, char** args);
int builtin_command(char** args);
void handler(int sig);
void checkRedirection(char** args);

int main ()
{
	signal(SIGINT, handler);
	signal(SIGTSTP, handler);
	char cmdline[MAXLINE];

	while (1){

	printf("> ");
	
	fgets(cmdline, MAXLINE, stdin);
	if (feof(stdin))
		exit(0);
	
	
	eval(cmdline);
	}

}// end main()



void handler(int sig)
{
	if (sig == 2)	
		printf("\nSIGINIT signal has been received.\n");
			
	else if (sig == 20)
		printf("\nSIGTSTP signal has been received.\n");
}




void checkRedirection(char** args){
	
	if(!strcmp(args[1],">")){		
		int file;
		if((file = open(args[2], O_CREAT |O_WRONLY | O_TRUNC, 0644)) < 0){
			perror(args[2]);
			exit(1);
		}
		dup2(file, 1);
		args[1] = NULL;
		
		if(execvp(args[0], args) < 0){
			printf("%s: Command not found.\n", args[0]);			
			exit(0);
		}	
		
		close(file);
		exit(0);
	}
	else if(!strcmp(args[1],"<")){		
				
		int file;
		if((file = open(args[2], O_RDONLY, 0644)) < 0){
			perror(args[2]);
			exit(1);
		}
		dup2(file, 0);
		args[1] = NULL;
		
		if(execvp(args[0], args) < 0){
			printf("%s: Command not found.\n", args[0]);			
			exit(0);
		}	
		
		close(file);
		exit(0);
	}
	else if(!strcmp(args[1],">>")){		
		int file;
		if((file = open(args[2], O_CREAT |O_WRONLY | O_APPEND, 0644)) < 0){
			perror(args[2]);
			exit(1);
		}
		dup2(file, 1);
		args[1] = NULL;
		
		if(execvp(args[0], args) < 0){
			printf("%s: Command not found.\n", args[0]);			
			exit(0);
		}	
		
		close(file);
		exit(0);
	}
	

}// end checkRedirection()




int builtin_command(char** args)
{
	// add support for I/O redirection "> >> <"	

	//if (!strcmp(args[0], "cd")){
		//chdir(args[1]);

	if (!strcmp(args[0], "exit"))
		exit(0);
 
	return 0;

} // end builtin_command()




int parseline( char* buf, char** args) // returns 1 if empty else 0
{
	char* delim;
	int numArgs;

	buf[strlen(buf)-1] = ' ';
	while (*buf && (*buf == ' '))
		buf++;

	//Build the args list	
	numArgs = 0;
	while ((delim = strchr(buf, ' '))){
		args[numArgs++] = buf;
		*delim = '\0';
		buf = delim+1;
		while(*buf && (*buf == ' ')) // ignore spaces
			buf++;
	}

	args[numArgs] = NULL;

	if(numArgs == 0)
		return 1; 
	else return 0;
}// end parseline()



void eval(char* cmdline)
{

	char* args[MAXARGS];
	char buf[MAXLINE];
	pid_t pid;
	int isEmpty;

	strcpy(buf, cmdline);
	// parseline returns whether command line was empty or not	
	isEmpty = parseline(buf, args);
	if (args[0] == NULL)
		return;

	if(!builtin_command(args)) {
		if ((pid = fork()) == 0){
			// set root to home		
			//chdir(getenv("HOME")); // find home on any user 		
			printf( "The PID of the child is: %d\n", getpid());		
			
			if (args[1] != NULL){
				if (!strcmp(args[1], ">") || !strcmp(args[1],">>") 
							  || !strcmp(args[1],"<")){			
					checkRedirection(args);
				}
			}
			//else 
			if(execvp(args[0], args) < 0){
				printf("%s: Command not found.\n", args[0]);			
				exit(0);
		    }	
		
	}

	if(!isEmpty){	
		int status;		
		if (waitpid(pid, &status, 0) < 0)
			printf("waitfg: waidpid error\n");			

		if (WIFEXITED(status))
        	printf("child %d terminated normally with exit status=%d\n",
               						pid, WEXITSTATUS(status));
		else        
			printf("Child %d terminated abnormally\n", pid);

		}
	}
} // end eval()

