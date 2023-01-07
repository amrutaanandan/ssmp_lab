#include <stdio.h>
#include <stdlib.h>

int i=0, j=0, k=0, l=0, op, number, size[20], block[20], indexes[20];
char fname[20][10];

void sequential();
void linked();
void indexed();

void main(){
    
    do{
        printf("\n---< Menu >---\n");
        printf("\n1. Sequential\n2. Linked\n3. Indexed\n4. Exit\n");
        scanf("%d", &op);
        
        switch(op){
            case 1:{
                sequential();
                break;
            }
            case 2:{
                linked();
                break;
            }
            case 3:{
                indexed();
                break;
            }
        }
    }while(op!=4);
}

void sequential(){
    printf("\nEnter the number of files? ");
    scanf("%d", &number);
    
    for(i=0;i<number;i++){
        printf("\nEnter file name: ");
        scanf("%s", fname[i]);
        printf("\nEnter the block size: ");
        scanf("%d", &size[i]);
    }
    
    printf("File\tSize\tAllocated\n");
    
    k=0;
    
    for(i=0;i<number;i++){
        printf("%s\t",fname[i]);
        printf("%d\t",size[i]);
            
        if(size[i]>20-k){
            printf("Can't be allocated!");
        }
        else{
            for(j=0;j<size[i];j++){
                printf("%d ",k);
                k++;
            }
        }
        printf("\n");
    }
    
}

void linked(){
    int count = 0;
    
    for(i=0;i<20;i++){
        block[i]=0;
    }
   
    printf("\nEnter the number of files? ");
    scanf("%d", &number);
    
    for(i=0;i<number;i++){
        printf("\nEnter file name: ");
        scanf("%s", fname[i]);
        printf("\nEnter the block size: ");
        scanf("%d", &size[i]);
    }
    
    printf("File\tSize\tAllocated\n");
    
    for(i=0;i<number;i++){
        printf("%s\t",fname[i]);
        printf("%d\t",size[i]);
        
        if(size[i]>20-count){
            printf("Can't be allocated!");
        }
        else{
            for(j=0;j<size[i];j++){
                for(l=5;l>1;l++){
                    k=rand()%20;
                    if(block[k]==0){
                        printf("%d ",k);
                        block[k]=1;
                        count++;
                        break;
                    }
                }
            }
        }
        printf("\n");
    }
}

void indexed(){
    
    int count=0;
    
    for(i=0;i<20;i++){
        block[i]=0;
        indexes[i]=0;
    }
    
    printf("\nEnter the number of files? ");
    scanf("%d", &number);
    
    for(i=0;i<number;i++){
        printf("\nEnter file name: ");
        scanf("%s", fname[i]);
        printf("\nEnter the block size: ");
        scanf("%d", &size[i]);
    }
    
    printf("Index\tFile\tSize\tAllocated\n");
    
    for(i=0;i<number;i++){
        
        for(l=10; l>1; l++){
            k=rand()%20;
            if(block[k]==0){
                printf("%d\t",k);
                block[k]=1;
                count++;
                break;
            }
        }
        
        printf("%s\t", fname[i]);
        printf("%d\t", size[i]);
        
        if(size[i]>20-count){
            printf("Can't be allocated!");
        }
        else{
            for(j=0;j<size[i];j++){
                for(l=5;l>1;l++){
                    k=rand()%20;
                    if(block[k]==0){
                        printf("%d ",k);
                        block[k]=1;
                        count++;
                        break;
                    }
                }
            }
        }
        
        printf("\n");
    }
}
