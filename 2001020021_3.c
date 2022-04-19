/*
	Sha Nia Siahaan
	2001020021
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    int nim;
    char name[50];
    struct Node* next;
};

char answer;

int inputRecord(struct Node** ref, int new_nim, char new_name[50]){
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    struct Node *last = *ref; 
           
    new_node->nim = new_nim;
    strcpy(new_node->name, new_name);
    new_node->next = NULL; 
      
    if(last->next != NULL){
        if(last->nim == new_nim){
            printf("Input denied.\nStudent's ID Number already in the record.");
            return 1;
        }
    }    

    while(last->next != NULL){ //last contains the previous node
        last = last->next; 
        
        if(last->nim == new_nim){
            printf("Input denied.\nStudent's ID Number already in the record.");
            return 1;
        }
    }
    
    last->next = new_node;

    return 1;
}

int input(struct Node *head){
    int nim;
    char name[50];
    
    printf("Type Student's ID Number: ");
    scanf("%d", &nim);
        
    printf("Type Student's Name: ");
    scanf("%*c%[^\n]%*c", name);
    
    inputRecord(&head, nim, name);
    
    printf("\n Input another data? \n[Y/N]: ");
    scanf("%c", &answer);
    
    if(answer == 'Y' || answer == 'y'){
        input(&(*head));
    }

    else{
        return 1;
    }
}

int searchRecordbyNIM(struct Node **ref_nim, int search_nim){
    struct Node *current_nim = *ref_nim;
   
    printf("Student ID \t\t Student Name\n");
    while(current_nim != NULL){
        current_nim = current_nim->next;
        
        printf("crrnt nim %d\n", current_nim->nim);
        if(current_nim->nim == search_nim){
                       
            printf("%d \t\t\t %s\n", current_nim->nim, current_nim->name);
        }
                
        while(current_nim->next == NULL){
            return 1;
        }
    }
    
    return 1;
}

int searchRecordbyName(struct Node **ref_name, char search_name[50]){
    struct Node *current_name = *ref_name;
        
    int result;

    result = strcmp(current_name->name, search_name);
        
    if(result == 0){
        return(1);
    }
    else{
        return(0);
    }  
    
   return 1;
}

int search(struct Node *head){
    struct Node *current_name;
    current_name = head;
    
    int Found;
    int nim;
    char name[50];
    
    
    printf("Search based on ID [I] or name [N]?\n{I/N]: ");
    scanf("%*c%[^\n]", &answer);
    
    if(answer == 'I' || answer == 'i'){
        printf("Type Student's ID Number to look for: ");
        scanf("%d", &nim);
        
        searchRecordbyNIM(&head, nim);
    }
    
    else if(answer == 'N' || answer == 'n'){
        
        printf("Type Student's Name to look for: ");
        scanf("%s", name);
        
        printf("\nStudent ID \t\t Student Name\n");
        while(current_name->next != NULL){
            current_name = current_name->next;
            
            if(searchRecordbyName(&current_name, name) == 1){
                Found++;
                
                printf("%d \t\t\t %s\n", current_name->nim, current_name->name);
            }   
        }
        
        if(Found == 0){
            printf("Name not found.\n");
        }
    }
    
    else{
        printf("ERROR: Unable recognize input.");
        
        return 1;
    }
    
    printf(" Search again?\n[Y/N]: ");
    scanf("%*c%[^\n]", &answer);
    
    if(answer == 'Y' || answer == 'y'){
        search(&(*head));
    }
    
    else{
        return 1;
    }
    
}

int update(struct Node *ref){
    struct Node *current = ref;
    struct Node *check;
    int nim;
    int NIMfound = 0; //for searching not found NIM
    int update_nim;
    char update_name[50];
    int counter = 0;
    
    printf("Type Student's ID Number to update: ");
    scanf("%d", &nim);
    
    while(current->next != NULL){
        counter++;
        
        current = current->next;

        if(current->nim == nim){
            printf("ID Number : %d\n", current->nim);
            printf("Name : %s\n", current->name);

            printf("Type New Student's ID Number: ");
            scanf("%d", &update_nim);

            printf("Type New Student's Name: ");
            scanf("%s", update_name);
            
            check = ref;
            
            while(check->next != NULL){
                check = check->next;
                
                printf("checknim %d\n", check->nim);
                printf("updt nim %d\n", update_nim);
                
                if(check->nim == update_nim){
                    NIMfound++;
                }
            }
            
            check->next = NULL;
            
            if(NIMfound >= 1){
                printf("Update denied.\nThere is another same ID Number already in the record.\n");
                
                return 1;
                
            }
          
            current->nim = update_nim;
            strcpy(current->name, update_name);
        }
    }
    
    if(counter == 0){
        printf("ID not found.\n");
    }
    
    printf("Update another data?\n[Y/N]: ");
    scanf("%*c%[^\n]", &answer);
    
    if(answer == 'Y' || answer == 'y'){
        update(&(*ref));
    }

    else{
        return 1;
    }
}

int deleteRecord(struct Node** ref, int key){
    struct Node *delnode = *ref, *prevnode;
    delnode = delnode->next;
        
    if(delnode != NULL && delnode->nim == key){
       *ref = delnode->next;
        free(delnode);
        
        return 1;
    }
    
    while(delnode != NULL && delnode->nim != key){
        prevnode = delnode;
        delnode = delnode->next;
    }
    
    if(delnode == NULL){
        return 1;
    }
    
    prevnode->next = delnode->next;
    
    free(delnode);
    
    return 1;
}

int delete(struct Node *head){
    struct Node *current;
    current = head;
    
    int key;
    int IDfound = 0;
    
    printf("Type Student's ID Number to be deleted: ");
    scanf("%d", &key);
    
    while(current->next != NULL){
        current = current->next;
        
        if(current->nim == key){
            IDfound++;
            printf("ID Number : %d\n", current->nim);
            printf("Name : %s\n", current->name);
            
            printf("Are you sure to delete this data?\n [Y/N]: ");
            scanf("%*c%[^\n]", &answer);
                        
            if(answer == 'Y' || answer == 'y'){
                deleteRecord(&head, key);
            }

            else{
                return 1;
            }
        }
    }
    
    if(IDfound == 0){
        printf("ID Number not found.\n");
    }
    return 1;
    
    printf("Delete another data?\n[Y/N]: ");
    scanf("%*c%[^\n]", &answer);
    
    if(answer == 'Y' || answer == 'y'){
        delete(&(*head));
    }
    
    else{
        return 1;
    }
}

int show(struct Node *ref){
    struct Node *current;
    current = ref;
           
    if(current->next == NULL ){
        printf("No records found.\n");
        return 1;
    }
    
    printf("\nStudent ID \t\t Student Name\n");
    while(current->next != NULL){
        current = current->next;
        printf("%d \t\t\t %s\n", current->nim, current->name);
    }
           
    return 1;
}

int main(){
    int x;
    struct Node* head = (struct Node*) malloc(sizeof(struct Node));
    
    menu:
        printf("\nSTUDENT RECORD SYSTEM\n");
        printf("1. Input New Record\n");
        printf("2. Search Record\n");
        printf("3. Update Record\n");
        printf("4. Show Records\n");
        printf("5. Delete Record\n");
        printf("Your choice: ");
        scanf("%d", &x);

        switch(x){
            case 1:
                input(head);
                goto menu;           
                break;
            case 2:
                search(head);
                goto menu;
                break;
            case 3:
                update(head);
                goto menu;
                break;
            case 4:
                show(head);
                goto menu;
                break;
            case 5:
                delete(head);
                goto menu;
                break;
            default:
                printf("ERROR: The input is not valid.\n");
                break;
        }
    
    return 0;
}
