#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int nim;
    char name[20];
    struct Node *left;
    struct Node *right;
    int height;
};

char answer;

int height(struct Node *N){
    if(N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b){
    return (a>b)? a:b;
}

struct Node *newNode(int key, char name[20]){
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    
    node->nim = key;
    strcpy(node->name, name);
    node->left = NULL;
    node->right = NULL;
    node->height = 1; //tinggi node setelah dibuat node baru
    
    return(node);
};

//alat untuk rotasi kanan subtree yg headnya y
struct Node* rightrotate(struct Node* y){
    struct Node *x = y->left;
    struct Node *T2 = x->right;
    
    //rotasi
    x->right = y;
    y->left = T2;
    
    //update tingginya
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
    
    
    return x;
}

struct Node *leftrotate(struct Node *x){
    struct Node *y = x->right;
    struct Node *T2 = y->left;
    
    //rotasi
    y->left = x;
    x->right = T2;
    
    //update tingginya
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
    
    return y;
}

int balancefactor(struct Node *N){
    if(N == NULL){
        return 0;
    }
    
    return height(N->left) - height(N->right);
}

struct Node* minimalValue(struct Node* node){
    struct Node* current = node;
 
    //mencari leaf yang paling kiri
    while (current->left != NULL){
        current = current->left;
    }
    return current;
}

struct Node* deleteNode(struct Node* head, int key){
    if (head == NULL){
        return head;
    }
    
    //jika nim yg akan dihapus lebih kecil dari headnya, ke kiri
    if ( key < head->nim ){
        head->left = deleteNode(head->left, key);
    }
 
    //sebaliknya jika lebih besar, ke kanan
    else if( key > head->nim ){
        head->right = deleteNode(head->right, key);
    }
 
    else{
        if( (head->left == NULL) || (head->right == NULL) ){
            struct Node *ref = head->left ? head->left : head->right;
 
            //jika tidak ada anak
            if(ref == NULL){
                ref = head;
                head = NULL;
            }
            
            //jika hanya 1 anak
            else{ 
             *head = *ref;
            }
            
            free(ref);
        }
        
        else{
            struct Node* ref = minimalValue(head->right);
 
            head->nim = ref->nim;
 
            head->right = deleteNode(head->right, ref->nim);
        }
    }
 
    //jika hanya ada 1 node
    if (head == NULL)
      return head;
 
    head->height = 1 + max(height(head->left), height(head->right));
 
    //mencari nilai dari balance factor
    int balance = balancefactor(head);
 
     
    //left left
    if (balance > 1 && balancefactor(head->left) >= 0)
        return rightrotate(head);
 
    //left right
    if (balance > 1 && balancefactor(head->left) < 0)
    {
        head->left =  leftrotate(head->left);
        return rightrotate(head);
    }
 
    //right right
    if (balance < -1 && balancefactor(head->right) <= 0)
        return leftrotate(head);
 
    // right left
    if (balance < -1 && balancefactor(head->right) > 0)
    {
        head->right = rightrotate(head->right);
        return leftrotate(head);
    }
 
    return head;
}

struct Node* insert(struct Node* node, int key, char name[20]){
    if(node == NULL){
        return(newNode(key, name));
    }
    else if(key < node->nim){
        node->left = insert(node->left, key, name);
    }
    else if(key > node->nim){
        node->right = insert(node->right, key, name);
    }
    else{
        printf("Input denied.\nStudent's ID Number already in the record.\n");
        return node;
    }
    
    node->height = 1 + max(height(node->left), height(node->right));
        
    //balance factor untuk mengecek apakah tree balance atau tidak
    int balance = balancefactor(node);
    
    //kasus ketika tree tidak balance yaitu:
    //1. left left
    if(balance > 1 && key < node->left->nim){
        return rightrotate(node);
    }
    //2. right right 
    if(balance < -1 && key > node->right->nim){
        return leftrotate(node);
    }
    //3. left right 
    if(balance > 1 && key > node->left->nim){
        node->left = leftrotate(node->left);
        return rightrotate(node);
    }
    
    //4. right left
    if(balance < -1 && key < node->right->nim){
        node->right = rightrotate(node->right);
        return leftrotate(node);
    }
    
    return node;
}

int search(struct Node* head, int key){
    struct Node* current = head;
    
    if(key == current->nim){
        printf("ID Number: %d\n", current->nim);
        printf("Name: %s\n", current->name);
        
        return(2);
    }
    
    else if(current->right != NULL && key > current->nim){
        search(head->right, key);
    }
    
    else if(current->left != NULL && key < current->nim){
        search(head->left, key);
    }
           
    else if(current->right == NULL || current->left == NULL){
        printf("ID not found.\n");
        
        return(1);
    }

}

int searchUpdate(struct Node* head, int key){
    struct Node* current = head;
    
    if(key == current->nim){
        return(2);
    }
    
    if(current->right != NULL && key > current->nim){
        printf("a");
        searchUpdate(head->right, key);
    }
    
    if(current->left != NULL && key < current->nim){
        printf("b");
        searchUpdate(head->left, key);
    }
           
    if(current->right == NULL || current->left == NULL){
        printf("c");
        return(3);
    }

}

void show(struct Node *head){
    
    if(head != NULL){
        printf("%d \t\t\t %s\n", head->nim, head->name);
        show(head->left);
        show(head->right);
    }
}

int main(){
    int x;
    
    int nim;
    char name[50];
    
    int update_nim;
    char update_name[20];
    
    struct Node* head = NULL;
    
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
                input:
                printf("Type Student's ID Number: ");
                scanf("%d", &nim);

                printf("Type Student's Name: ");
                scanf("%*c%[^\n]%*c", name);
                
                head = insert(head, nim, name);
                
                printf("\n Input another data? \n[Y/N]: ");
                scanf("%c", &answer);

                if(answer == 'Y' || answer == 'y'){
                    goto input;
                }

                else{
                    goto menu;           
                }
                
                goto menu;           
                break;
                
            case 2:
                search:
                printf("Type Student's ID Number to look for: ");
                scanf("%d", &nim);
                
                search(head, nim);
                
                printf(" Search again?\n[Y/N]: ");
                scanf("%*c%[^\n]", &answer);

                if(answer == 'Y' || answer == 'y'){
                    goto search;
                }

                else{
                    goto menu;
                }
                                                
                goto menu;
                break;
                
            case 3:
                update:
                printf("Type Student's ID Number to update: ");
                scanf("%d", &nim);

                if(search(head, nim) == 2){
                    printf("Type New Student's ID Number: ");
                    scanf("%d", &update_nim);
                    
                    printf("Type New Student's Name: ");
                    scanf("%s", update_name);
                
                    if(searchUpdate(head, update_nim) == 2){
                        printf("Update denied.\nThere is another same ID Number already in the record.\n");
                        
                    }
                    
                    else if(searchUpdate(head, update_nim) == 3){
                        
                        head = deleteNode(head, nim);
                        
                        head = insert(head, update_nim, update_name);
                        
                    }
                }
                
                printf("Update another data?\n[Y/N]: ");
                scanf("%*c%[^\n]", &answer);

                if(answer == 'Y' || answer == 'y'){
                    goto update;
                }

                else{
                    goto menu;
                }
                
                goto menu;
                break;
                
            case 4:
                printf("\nStudent ID \t\t Student Name\n");
                
                show(head);
                
                goto menu;
                break;
            case 5:
                delete:
                printf("Type Student's ID Number to be deleted: ");
                scanf("%d", &nim);
                
                search(head, nim);
                
                printf("Are you sure to delete this data?\n[Y/N]: ");
                scanf("%*c%[^\n]", &answer);

                if(answer == 'Y' || answer == 'y'){
                    head = deleteNode(head, nim);
                    
                    printf("Delete another data?\n[Y/N]: ");
                    scanf("%*c%[^\n]", &answer);

                    if(answer == 'Y' || answer == 'y'){
                        goto delete;
                    }

                    else{
                        goto menu;
                    }
                }

                else{
                    goto menu;
                }
                
                goto menu;
                break;
            default:
                printf("ERROR: The input is not valid.\n");
                break;
        }
    
    return 0;
}
