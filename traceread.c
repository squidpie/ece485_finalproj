//===============================================
// traceread.c
//
// Reads traces from input file 
//===============================================

#include "traceread.h"

int open_trace(char *filename)
{
    if(!(tracestream = fopen(filename, "r")))
        return 0;
}

void close_trace(void)
{
    fclose(tracestream);
}

int next_trace(Trace* t)
{
    char* temp = 0;
    int x = 0;
    //Get next line from file
    x = fgets(tracebuffer, TRACELINELENGTH, tracestream);

    //Check if EOF reached
    if(feof(tracestream))
    {
        printf("EOF\n");
        return -1;
    }

    //zero trace values
    t->traceType = INVALID;
    t->address = 0; 

    strcpy(straddr, "\0");
    strcpy(straction, "\0");
    
    //Parse line into Trace
    //x = sscanf(tracebuffer, "%d%*[ \t]%x%*[\n]", (int*)&t->traceType, &t->address);

    temp = strtok(tracebuffer, tok_delim);
    if(temp)
        strcpy(straction, temp);

    debug_printf("*** straction: %s\n", straction);
    if(!strlen(straction))
        return 0;

    temp = strtok(NULL, tok_delim);
    if(temp)
        strcpy(straddr, temp);
    debug_printf("*** straddr: %s length: %d\n", straddr, strlen(straddr));
    
    if(strcmp("8", straction) 
        && strcmp("9", straction) 
        && !strlen(straddr))
        return 0;

    debug_printf("Action: %s Addr: %s\n", straction, straddr);
    sscanf(straction, "%d", (int*)&t->traceType);
    sscanf(straddr, "%x", (int*)&t->address);

    return 0;
}

