/*
	Sha Nia Siahaan
	2001020021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pStack;
int i;
char **kata;
int ruang;

int pop(){
    if(pStack != 0){
        printf("Pop => %s\n", kata[--pStack]);
        
        return 1;
    }
    
    else{
        printf("Stack empty!"); 
        
        return 0;
    }
    
}

void popAll(){
    while(pop()){
        
        
    }
}

int main(int argc, char**params){
	ruang=argc;

	kata = malloc(argc * sizeof(char**));
	
	for(i=0; i<argc; i++){
		kata[i] = malloc(4 * sizeof(char *));
	}
	
	if(argc <= 1){
        printf("Tidak ada inputan.\nFormat yang benar\n\t./stack.o kata1 kata2 kata3 ...");
        
        return 1;
    }
	
	for(i = 1; i < argc; i++){
	    kata = realloc (kata, ++ruang * sizeof(char**));
	    strcpy(kata[pStack], params[i]);
	    pStack++;
	}
	
	if(pStack != 0){
	      printf("Success created stack.\n");
	}
        
	popAll();

	return 0;
}
