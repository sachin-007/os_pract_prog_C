/*Write a program to implement a toy shell (Command Interpreter). It has its own prompt say “MyShell $”. Any normal shell command is executed from this shell (MyShell$) by starting a child process to execute the system program corresponding to the command. It should additionally interpret the following commands: 
list f dirname : To print names of all the files in current directory 
list n dirname : To print the number of all entries in the current directory.
list i dirname : To print names and inodes of the files in the current directory. */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void make_toks(char *s, char *tok[])
{
 int i=0;
 char *p;

 p = strtok(s,"");
 while(p!=NULL)
 {
  tok[i++]=p;
  p=strtok(NULL,"");
 }

 tok[i]=NULL;
}

void list(char *dn, char op)
{
 DIR *dp;
  //DIR *fdopendir(int fd);
 struct dirent *entry;
 int dc=0,fc=0;

 dp = opendir(dn);
 if(dp==NULL)
 {
  printf("Dir %s not found.\n",dn);
  return;
 }

 switch(op)
 {
 case 'f':
  while(entry=readdir(dp))
  {
   if(entry->d_type==DT_REG)
    printf("%s\n",entry->d_name);
  }
  break;
 case 'n':
  while(entry=readdir(dp))
  {
   if(entry->d_type==DT_DIR) dc++;
   if(entry->d_type==DT_REG) fc++;
  }
 
  printf("%d Dir(s)\t%d File(s)\n",dc,fc);
  break;
 case 'i':
  while(entry=readdir(dp))
  {
   if(entry->d_type==DT_REG)
    printf("%s\t%d\n",entry->d_name,entry->d_fileno);
  }
 }

 closedir(dp);
}

int main()
{
 char buff[80],*args[10];
 int pid;

 while(1)
 {
  printf("myshell$");
  fflush(stdin);
  fgets(buff,80,stdin);
  buff[strlen(buff)-1]='\0';
  make_toks(buff,args);
  if(strcmp(args[0]= opendir(".") ,"list")==0)
   list(args[2],args[1][0]);
  else
  {
   pid = fork();
   if(pid>0)
    wait();
   else
   {
    if(execvp(args[0],args)==-1)
     printf("Bad command.\n");
   }
  }
 }

 return 0;
}
