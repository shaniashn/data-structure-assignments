#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


char *infix;
int length;
char stackPrefix[100];
char stackPostfix[100];
int topPrefix;
int topPostfix;
int i,j,a;

int operator(char symbols){
    
    if(symbols == '*' || symbols == '/' || symbols == '+' || symbols == '-'){
        return 1;
    }
    
    else{
        return 0;
    }
}

int level(char symbols){
    if(symbols == '*' || symbols == '/'){
        return(2);
    }
    
    else if(symbols == '+' || symbols == '-'){
        return(1);
    }
    else{
        return(0);
    }
}

int pushPrefix(char pushthis){
    
    stackPrefix[topPrefix] = pushthis;
    topPrefix++;
    
    return 1;
}

char popPrefix(){
    char item;
    
    item = stackPrefix[--topPrefix];
    return(item);
    
}

int forReverse(char *save, char *infix){
    
    for(i=length-1; i>=0; i--){
        if(*(save+i) == '('){
            infix[j] = ')';
            j++;
        }
        
        else if(*(save+i)==')'){
            infix[j] = '(';
            j++;
        }
        
        else{
            infix[j] = *(save+i);
            j++;
        }
    }
    return 1;
}

int forPrefix(char *infix, char *result){
    char item;
    char x;
    int kurung = 0;
    
    pushPrefix('(');
    strcat(infix, ")");
    i=0;
    a=0;
    
    item = infix[i];
    
    while(i<=length+1){
       
        if(item=='\0'){
            
        }
       
        else if(item=='('){
            kurung = kurung + 1;
            pushPrefix(item);
        }
        
        else if(isalpha(item)){
            result[a] = item;
            a++;
        }
        
        else if(operator(item)==1){
            x = popPrefix();
            
            while(operator(x)==1 && level(x) >= level(item)){
                result[a] = x;
                a++;
                x = popPrefix();
            }
            
            pushPrefix(x);
            pushPrefix(item);
        }
        
        else if(item == ')'){
            kurung = kurung + 1;
            x = popPrefix();
            
            while(x != '('){
              
                result[a] = x;
                a++;
               
                x = popPrefix();
            }
    
        }
        
        else{
            
        }
        
        i++;
    
        item = infix[i];
        
    }
    
    for(a=length-kurung; a>=0; a--){
        printf("%c", result[a]);
    }
    
    return 1;
}

int pushPostfix(char pushthis){
    
    stackPostfix[topPostfix] = pushthis;
    topPostfix++;
    return 1;
}

char popPostfix(){
	
    char item;
    
    item = stackPostfix[--topPostfix];
    
    return(item);
}


int forPostfix(char *infix, char *result){
    char item;
    char x;
    int kurung = 0;
    
    pushPostfix('(');
    strcat(infix, ")");
    
    i=0;
    a=0;
    
    
    item = infix[i];
    
    while(i<=length){
        
        if(item=='\0'){
            
        }
       
        else if(item=='('){
        	kurung = kurung + 1;
            pushPostfix(item);
            
        }
        
        else if(isalpha(item)){
            result[a] = item;
            a++;
        }
        
        else if(operator(item)==1){
            
            x = popPostfix();
            
            while(operator(x)==1 && level(x) >= level(item)){
                result[a] = x;
                a++;
                x = popPostfix();
            }
        
            pushPostfix(x);
            pushPostfix(item);
        }
        
        else if(item == ')'){
           kurung = kurung + 1;
            
            x = popPostfix();
           
            while(x != '('){

                result[a] = x;
                a++;
                x = popPostfix();
                
            }

        }
        
        else{
            printf("Invalid expression.\n");
        }
        
        i++;
        
        item = infix[i];
        result[a] = '\0';
    }
    
    for(a=0; a<=length-kurung; a++){
        printf("%c", result[a]);
    }
    
    return 1;
}

int main(int argc, char **argv){
    
    char reverse[length];
    char prefixResult[length];
    char postfixResult[length];
    
    j = 0;
    length = (strlen(argv[1]));
    
    if(argc==1){
        printf("No arguments found.");
        return 1;
    }
    
    else{

        printf("Prefix answer \n");
        printf("2001020021 = ");
        forReverse(argv[1], reverse);
        forPrefix(reverse, prefixResult);
        
        printf("\n");
        printf("Postfix answer \n");
        printf("2001020021 = ");
        forPostfix(argv[1], postfixResult);
        
        
    }
    return 0;
}
