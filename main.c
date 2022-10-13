/**
 * First Student: Ammar Khan (id: 991439943)
 * Second Student: Muhammad Usman Shahid (id: 991446409)
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <ctype.h>

int sum;
int linesToRd;
int linesToRd1;
int count_1;
int count_2;
int count_3;
int count_4;
int lines;
int charCnt; 
char chToRead;                  /* this data is shared by the thread(s) */

void *runner(void *param); /* the thread will begin execution in the function*/
/*void *squareIt(void *param);*/
int countlines(char *filename);

void partition(char *filename, int count, char file1[4][1000]);

void *thread2task(void *param);
void *thread3task(void *param);
void *thread4task(void *param);

int main(int argc, char *argv[])
{

  	
  pthread_t tid;           /* the thread identifier */
  pthread_t tid2;
  pthread_t tid3;
  pthread_t tid4;
  chToRead = tolower(argv[2][0]);
  
  
  pthread_attr_t attr;     /* set of attributes for the thread */

  
  if (argc < 2) 
  {
	fprintf(stderr,"usage: a.out <file name> <letter to find>\n");
	return -1;
  }

  if (atoi(argv[1]) < 0) 
  { 
	fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
	return -1;
  }
  
  lines = countlines(argv[1]);
  linesToRd = floor(lines/4);
  linesToRd1 = lines - linesToRd * 3;
 
  char file1[4][1000];
  
  
  
  
  
  partition(argv[1], charCnt, file1);
 
  

  
  pthread_attr_init(&attr);

  /* create the thread */
  pthread_create(&tid,&attr,runner,file1[0]);
  pthread_create(&tid2,&attr,thread2task,file1[1]);
  pthread_create(&tid3,&attr,thread3task,file1[2]);
  pthread_create(&tid4,&attr,thread4task,file1[3]);
  
  /* now parent thread waits for the child thread to exit */
 pthread_join(tid,NULL);
 pthread_join(tid2,NULL);
 pthread_join(tid3,NULL);
 pthread_join(tid4,NULL);
  printf("The Thread 1 count_1 for letter ‘%c/%c’ value is: %d\n" , chToRead,toupper(chToRead),count_1);
  printf("The Thread 2 count_2 for letter ‘%c/%c’ value is: %d\n" , chToRead,toupper(chToRead),count_2);
  printf("The Thread 3 count_3 for letter ‘%c/%c’ value is: %d\n" , chToRead,toupper(chToRead),count_3);
  printf("The Thread 4 count_4 for letter ‘%c/%c’ value is: %d\n" , chToRead,toupper(chToRead),count_4);
  sum = count_1 + count_2 + count_3 + count_4;
  
  printf("The Main Thread count_total for letter '%c/%c' , value is %d\n",chToRead,toupper(chToRead),sum);  // parent thread continues and prints this output
}





int countlines(char *filename)
{
  // count the number of lines in the file called filename                                    
  FILE *fp = fopen(filename,"r");
  int ch=0;
  int lines=0;
  if (fp == NULL)
  {
     printf("file was not found\n"); 	
     return 0;
  }
 
  
  
  while(!feof(fp))
  {
    ch = fgetc(fp);
    charCnt++;
    if(ch == '\n')
    {
      lines++;
    }
  }
  fclose(fp);
  return lines;
}

void partition(char *filename, int count, char file1[4][1000])
{
  int j = 0;
  int counter = linesToRd;
     
	    FILE *fp = fopen(filename,"r");
	    char ch;
	    int n = 0;
	    int lines=0;
	    
	    if (fp == NULL)
	    {
	       printf("file was not found\n"); 	
	       
	    }
 
  
         
	  while(!feof(fp))
	  {
	    ch = fgetc(fp);
	    
	    if(ch == '\n')
	    {
	      lines++;
	      if (lines == counter)
	      {
	         j++;
	         if (j == 3)
	         {
	            counter  = -1;
	           
	         }
	         n = 0;
	         lines = 0;
	      }
	    }
	    else
	    {
	       file1[j][n++]=(char)ch;
	    }
	   
	  }
	  fclose(fp);
  	
}

void *runner(void *param) 
{
  
	char *lines = (char *)param;
	for(int i=0;i<strlen(lines);i++)
	{
	  char ch = lines[i];
	  if(ch == '\n')
	    {
	      
	      pthread_exit(0);
	    }
	    else
	    {
	       if(chToRead == tolower((char)ch))
	       {
	         count_1++;
	       }
	    }
	}  
       
}

void *thread2task(void *param)
{
  char *lines = (char *)param;
  for(int i=0;i<strlen(lines);i++)
	{
	  char ch = lines[i];
	  if(ch == '\n')
	    {
	      
	      pthread_exit(0);
	    }
	    else
	    {
	       if(chToRead == tolower((char)ch))
	       {
	         count_2++;
	       }
	    }
	}    
  
}

void *thread3task(void *param)
{
   char *lines = (char *)param;
   
	for(int i=0;i<strlen(lines);i++)
	{
	  char ch = lines[i];
	  if(ch == '\n')
	    {
	      
	      pthread_exit(0);
	    }
	    else
	    {
	       if(chToRead == tolower((char)ch))
	       {
	         count_3++;
	       }
	    }
	}  
}

void *thread4task(void *param)
{
   char *lines = (char *)param;  
   
	    
	for(int i=0;i<strlen(lines);i++)
	{
	  char ch = lines[i];
	  if(ch == '\n')
	    {
	      
	      pthread_exit(0);
	    }
	    else
	    {
	       if(chToRead == tolower((char)ch))
	       {
	         count_4++;
	       }
	    }
	}  
}
