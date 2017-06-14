#ifndef PARSE_FILE_H
#define PARSE_FILE_H

//function to parse file states
char * parseState(long state){

   char* str;

   int  i;

    switch(state){
      case 0 :
            str = "RUNNING";
          break;
      case 1 :
           str = "TASK_INTERRUPTIBLE";
          break;
      case 2 :
          str = "TASK_UNINTERRUPTIBLE";
         break;
      case 4 :
            str = "__TASK_STOPPED";
         break;
      case 8 :
            str = "__TASK_TRACED";
         break;
      case 16:
            str = "EXIT_DEAD";
          break;
      case 32 :
            str = "EXIT_ZOMBIE";
             break;
      case 32 | 16 :
            str = "EXIT_TRACE";
             break;
      case 64:
            str = "TASK_DEAD";
            break;
      case 128:
          str = "TASK_WAKEKILL";
          break;
      case 256:
          str = "TASK_WAKING";
          break;
      case 512:
          str = "TASK_PARKED";
          break;
      case 1024:
          str = "TASK_NOLOAD";
          break;
      case 2048:
          str = "TASK_NEW";
          break;
      case 4096:
          str = "TASK_STATE_MAX";
          break;
      case 128 | 2:
          str = "TASK_KILLABLE";
          break;
      case 128 | 4:
          str = "TASK_STOPPED";
          break;
      case 128 | 8:
          str = "TASK_TRACED";
          break;
      case  2 | 1024:
          str = "TASK_IDLE";
          break;
      case 1 | 2:
          str = "TASK_NORMAL";
          break;
      case 1 | 2 | 4 | 8:
          str = "TASK_ALL";
          break;
      case 0 | 1 | 2 |4 | 8 | 32 | 16 :
          str = "TASK_REPORT";
          break;
      default : 
         break; 
    }
       return str;
}

#endif