#include "process_list.h"
#include "parse_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include <unistd.h> 
           

struct my_buf ubuf[MAX_BUF_SIZE];

  int main () { 
	                                    
    int fd;                                         
    int data;                                        
    int cnt = 0;
    int i;
    
   
   //Open device process_list                           
   fd = open("/dev/process_list", O_RDONLY);

    if ( fd < 0 ) {                                 
      printf("failed to open device.\n");  
      exit(1);                                        
    } 

  //read device
   data =read(fd, ubuf, sizeof(ubuf)); 

   if ( data < 0 ) {   

      printf("failed to read from device.\n");
       
        exit(1);                              
    }   

  //interate through struct to print processes at user space
    while(cnt < data ){

       printf( "PID= %ld  PPID= %ld  CPU= %ld   STATE= %s\n",ubuf[cnt].pid , ubuf[cnt].ppid ,ubuf[cnt].cpu ,parseState(ubuf[cnt].state));  

       cnt++;
      
   }
                 
    close(fd);                                      
    return 0;                                       
  }
