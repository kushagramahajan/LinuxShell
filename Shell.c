#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<signal.h>
#include<unistd.h>
#include<time.h>
int pfds[2];
struct his
{
	char command[1024];
	struct his *next;
};
void gettoken(char words[],char token[][1024])
{
	int i,j=0,k=0;
	for(i=0;words[i]!='\0';i++)
	{
		if(words[i]==' '||words[i]=='\n')
		{
			token[j][k]='\0';
			k=0;
			j++;
		}
		else
		{
			token[j][k]=words[i];
			k++;
		}
	}
	token[j][k++]='\0';
}
int validcommand(char *tokens,char *valid[],int n)
{
	int check;
	int i=0;
	for(i=0;i<n;i++)
	{
		if(strcmp(tokens,valid[i])==0)
		{
			check=1;
			break;
		}
	}
	if(check!=1)
		return -1;
	else
		return check; 
}
void Execio(char token[][1024],int pos)
{
	int fd,fd1;
	int pid = fork();
	if(pid==0)
	{
		
	if(strcmp(token[pos],">")==0)
	{
		fd = creat(token[pos+1],0644);
		dup2(fd,STDOUT_FILENO);
		close(fd);		
	}
	else if(strcmp(token[pos],"<")==0)
	{
		fd1 = open(token[pos+1],0);
		dup2(fd1,STDIN_FILENO);
		close(fd1);
	}
	if(pos==1)
				{
					char path[50]="/home/rajeev/Desktop/OS/Shell/cmd/";		
					strcat(path,token[0]);
					if(execl(path,token[0],NULL)<0)
					{
						printf("Error:exec failed\n");
						exit(1);
					}
				}
				else if(pos==2)
				{
					char path[50]="/home/rajeev/Desktop/OS/Shell/cmd/";		
					strcat(path,token[0]);
					if(execl(path,token[0],token[1],NULL)<0)
					{
						printf("Error:exec failed\n");
						exit(1);
					}
				}
				else if(pos==3)
				{
					char path[50]="/home/rajeev/Desktop/OS/Shell/cmd/";		
					strcat(path,token[0]);
					if(execl(path,token[0],token[1],token[2],NULL)<0)
					{
						printf("Error:exec failed\n");
						exit(1);
					}
				}
	}
	else
	{
		wait(NULL);
	}
	
}
			
void Exec(char token[][1024],int pos)
{	
	int pid1,pid2,status,status2;	
	pipe(pfds);
	if((pid1=fork())<0)
	{
		printf("ERROR:forking child process failed\n");
	}
	if(pid1==0)
	{
		close(1);
		dup(pfds[1]);
		close(pfds[0]);
		{
			{
				if(pos==1)
				{
					char path[50]="/home/rajeev/Desktop/OS/Shell/cmd/";		
					strcat(path,token[0]);
					if(execl(path,token[0],NULL)<0)
					{
						printf("Error:exec failed\n");
						exit(1);
					}
				}
				else if(pos==2)
				{
					char path[50]="/home/rajeev/Desktop/OS/Shell/cmd/";		
					strcat(path,token[0]);
					if(execl(path,token[0],token[1],NULL)<0)
					{
						printf("Error:exec failed\n");
						exit(1);
					}
				}
				else if(pos==3)
				{
					char path[50]="/home/rajeev/Desktop/OS/Shell/cmd/";		
					strcat(path,token[0]);
					if(execl(path,token[0],token[1],token[2],NULL)<0)
					{
						printf("Error:exec failed\n");
						exit(1);
					}
				}
			}
		}
	}
	else if((pid2=fork())==0)
	{
		close(0);
		dup(pfds[0]);
		close(pfds[1]);
		{
			{
				if(strcmp(token[1+(pos+1)],"")==0&&strcmp(token[2+(pos+1)],"")==0)
				{			
					char path[50]="/home/rajeev/Desktop/OS/Shell/cmd/";		
					strcat(path,token[0+(pos+1)]);	
					if(execl(path,token[0+(pos+1)],NULL)<0)
					{
						printf("Error:exec failed\n");
						exit(1);
					}

				
				}
				else if(strcmp(token[1+(pos+1)],"")!=0&&strcmp(token[2+(pos+1)],"")==0)
				{							
					char path[50]="/home/rajeev/Desktop/OS/Shell/cmd/";
					strcat(path,token[0+(pos+1)]);
					if(execl(path,token[0+(pos+1)],token[1+(pos+1)],NULL)<0)
					{
						printf("Error:exec failed\n");
						exit(1);
					}
			
				}
				else if(strcmp(token[1+(pos+1)],"")!=0&&strcmp(token[2+(pos+1)],"")!=0)
				{							
					char path[50]="/home/rajeev/Desktop/OS/Shell/cmd/";		
					strcat(path,token[0+(pos+1)]);	
					if(execl(path,token[0+(pos+1)],token[1+(pos+1)],token[2+(pos+1)],NULL)<0)
					{
						printf("Error:exec failed\n");
						exit(1);
					}
				}
				
			}
		}
	}
	else
	{
		close(pfds[0]);
		close(pfds[1]);
		while(wait(&status)!=pid1);
		while(wait(&status2)!=pid2);
	}
	return ;
}		
void Execute(char token[][1024])
{
	int pid= fork();
	if(pid==0)
	{		
		if(strcmp(token[1],"")==0&&strcmp(token[2],"")==0)
		{
			
			char path[50]="/home/rajeev/Desktop/OS/Shell/cmd/";		
			strcat(path,token[0]);	
			if(execlp(path,token[0],NULL)<0)
			{
				printf("Error:exec failed\n");
				exit(1);
			}
				
		}
		else if(strcmp(token[1],"")!=0&&strcmp(token[2],"")==0)
		{							
			char path[50]="/home/rajeev/Desktop/OS/Shell/cmd/";
			strcat(path,token[0]);
			if(execlp(path,token[0],token[1],NULL)<0)
			{
				printf("Error:exec failed\n");
				exit(1);
			}
			
		}
		else if(strcmp(token[1],"")!=0&&strcmp(token[2],"")!=0)
		{							
			char path[50]="/home/rajeev/Desktop/OS/Shell/cmd/";		
			strcat(path,token[0]);	
			if(execlp(path,token[0],token[1],token[2],NULL)<0)
			{
				printf("Error:exec failed\n");
				exit(1);
			}
		}
	}
	else
	{	
		wait(NULL);
	}
}		
int main()
{
	signal(SIGINT,SIG_IGN);		
	time_t current_time;
	char* c_string;
	char word[1024];
	char tokens[10][1024];
	char *ValidCmd[17] ={"cat","cp","cd","gedit","ls","pwd","mkdir","rmdir","rm","top","exit","help","clear","history","kill","grep","fgrep"};
	int n=17;
	FILE *fp;
	struct his *history=NULL;
	while(1)
	{
			
		char dir[100];
		getcwd(dir,100*sizeof(char));
		printf("%s>>",dir);		
		printf("rajeev@RShell$ ");
		fgets(word,1024,stdin); 
		fp  = fopen("/home/rajeev/Desktop/OS/Shell/Hist.txt","a");
		if(history==NULL)
		{
			history = (struct his*)malloc(sizeof(struct his));			
			strcpy(history->command,word);
			current_time=time(NULL);
			c_string = ctime(&current_time);
			fprintf(fp,"%s->%s\n",c_string,history->command);
			history->next=NULL;
		}
		else
		{
			struct his* temp;
			temp = (struct his*)malloc(sizeof(struct his));
			strcpy(temp->command,word);
			current_time=time(NULL);
			c_string = ctime(&current_time);
			fprintf(fp,"%s->%s\n",c_string,temp->command);
			temp->next = history;
			history = temp;
		}
		gettoken(word,tokens);
		int i=0, pos = 0;
		int flag=0;
		for(i=0;i<strlen(word);i++)
		{
			if(word[i]=='|')
				{
					flag=1;
					break;
				}
                       if( (word[i]==' ') && (flag == 0) )  
                       {
                           pos++;    
                       }
		}
		int flag1 = 0;
		i =0;
		int pos1=0;
		for(i=0;i<strlen(word);i++)
		{
			if(word[i]=='>'||word[i]=='<')
			{
				flag1 = 1;
				break;
			}
			if((word[i]==' ')&&(flag1==0))
			{
				pos1++;
			}
		}		
		if(flag==0&&flag1==0)
		{				
		if(strcmp(tokens[0],"exit")==0)
			exit(0);
		else if(strcmp(tokens[0],"\0")==0||strcmp(tokens[0],"\n")==0||strcmp(tokens[0],"\t")==0)
			continue;
		else if(validcommand(tokens[0],ValidCmd,n)==-1)
		{
			printf("Invalid Command. Type help command for valid commands");
				continue;
		}
		else if(strcmp(tokens[0],"help")==0)
		{
			int i=0;
			for(i=0;i<n;i++)
			{
				printf("%s  ",ValidCmd[i]);
			}
			printf("\n");
			continue;
		}
		else if(strcmp(tokens[0],"cd")==0)
		{
			chdir(tokens[1]);
		}	
		else if(strcmp(tokens[0],"history")==0)
		{
			printf("\nCommands which you have previously used:\n\n");
			if(fork()==0)
			{
				execl("/home/rajeev/Desktop/OS/Shell/cmd/cat","cat","/home/rajeev/Desktop/OS/Shell/Hist.txt",NULL);
			}
			else
			{
				wait(NULL);
			}			
			
		}		
		else
		{							
			Execute(tokens);
		}
		}
		else if(flag==1&&flag1==0)
		{
			Exec(tokens,pos);
			
		}
		else if(flag==0&&flag1==1)
		{			
			Execio(tokens,pos1);
		}
		strcpy(word,"");
		strcpy(tokens[0],"");
			strcpy(tokens[1],"");
			strcpy(tokens[2],"");
			strcpy(tokens[3],"");
			strcpy(tokens[4],"");
			strcpy(tokens[5],"");
			strcpy(tokens[6],"");
			strcpy(tokens[7],"");
			strcpy(tokens[8],"");
			strcpy(tokens[9],"");
		fclose(fp);	
				
	}
	return 0;
}
