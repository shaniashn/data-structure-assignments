#include <stdio.h>
#include <stdlib.h>


//variable declaration
long id[15];
char name[10][25];
int age[3];
int x;
int row=10;

//function declaration
void inputData();
void deleteData();
void showData();
void exitProgram();

void inputData(){
	if(id[x]==0){
		
		printf("\nID number: ");
	    scanf("%ld", &id[x]);
	    
	    printf("\nName: ");
	    scanf("%*c%[^\n]%*c", name[x]);
	    
	    printf("\nAge: ");
	    scanf("%d", &age[x]);
	    x++;
	}
	
    main();
}

void deleteData(){
	long search;
	int counter=0;
	printf("ID number: ");
	scanf("%ld", &search);
	
	for(x=0; x<row; x++){ 
		if(id[x]==search){
			counter++;
			id[x]=0;
    		printf("Data deleted.\n\n");
		}	
	}
    
	if(counter==0){
		printf("ID not found!\n\n");
	}
	main();
}

void exitProgram(){
	return 0;
}

void showDataList(){
	int y;
	printf("-------------------DATA LIST----------------------\n");
	printf("ID Customer\t\tName\t\tAge\n");
	printf("--------------------------------------------------\n");
	for(y=0; y<row; y++){
		if(id[y]!=0){
		printf("%ld\t\t\t%s\t\t%d\n", id[y], name[y], age[y]);
		}
	}
	main();
}

int main(){
    int inputnumber;
    printf("\n\nActivity\n");
    printf("1. Input new data\n");
    printf("2. Delete data\n");
    printf("3. Show data list\n");
    printf("4. Exit program\n");
    printf("Your choice: \n");
    scanf("%d", &inputnumber);
    
    if(inputnumber==1){
        inputData();
    }
    
    else if(inputnumber==2){
        deleteData();
    }
    
    else if(inputnumber==3){
    	showDataList();
	}
	
    else if(inputnumber==4){
        exitProgram();
    }

}
