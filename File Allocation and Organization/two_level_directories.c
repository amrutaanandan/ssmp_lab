#include<stdio.h>
#include<string.h>

struct root_dir{
char dir_name[20];
}root[20];

struct directory{
char file_name[20];
char dir_name[20];
}dir[20];

int search(char search_dir[20], struct root_dir root[20]){
    int i,value;
    for(i=0;i<20;i++){
        if(strcmp(search_dir, root[i].dir_name) == 0){
            return i;
        }
    }
    return -999;
}

int search_2(char search_file[20], struct directory dir[20]){
    int i,value;
    for(i=0;i<20;i++){
        if(strcmp(search_file, dir[i].file_name) == 0){
            return i;
        }
    }
    return -999;
}


void main(){
    int option,dir_count=-1,file_count=-1,temp,i=0,j=0;
    int total_dir=0, total_file=0;
    char search_dir[20],search_file[20];
    
    while(option != 8){
        printf("\n\n\t---<Menu>---\n");
        printf("1.\tCreate directory\n2.\tDelete directory\n3.\tSearch directory\n4.\tCreate file\n5.\tDelete file\n6.\tSearch file\n7.\tDisplay\n8.\tExit\n");
        scanf("%d", &option);
        switch(option){
            case 1:{
                printf("\nEnter directory name: ");
                dir_count+=1;
                scanf("%s", root[dir_count].dir_name);
                printf("\nCreated successfully!\nPath: root/%s\n", root[dir_count].dir_name);
                break;
            }
            case 2:{
                printf("Enter directory name: ");
                scanf("%s", search_dir);
                
                temp = search(search_dir, root);
                
                if(temp != -999){
                    dir_count-=1;
                    printf("\nDeleted succesfully!\n");
                    for(i=temp;i<=19;i++){
                        strcpy(root[i].dir_name, root[i+1].dir_name);
                    }
                }
                else
                printf("\nDirectory not found!\n");
                
                break;
            }
            case 3:{
                printf("Enter directory name: ");
                scanf("%s", search_dir);
                
                temp = search(search_dir, root);
                
                if(temp != -999){
                    printf("\nDirectory path: root/%s", root[temp].dir_name);
                }
                else
                    printf("\nDirectory not found!\n");
                
                break;
            }
            case 4:{
                printf("Enter file name: ");
                scanf("%s", search_file);
                printf("\nEnter directory to enter: ");
                scanf("%s", search_dir);
                
                temp = search(search_dir, root);
                
                if(temp != -999){
                    file_count+=1;
                    strcpy(dir[file_count].file_name, search_file);
                    strcpy(dir[file_count].dir_name, search_dir);
                    printf("\nCreated successfully!\nFile path: root/%s/%s", search_dir, dir[file_count].file_name);
                }
                else
                    printf("\nDirectory not found!\n");
                break;
            }
            
            case 5:{
                printf("Enter file name: ");
                scanf("%s", search_file);
                
                temp = search_2(search_file, dir);
                
                if(temp != -999){
                printf("\nDeleted succesfully!\n");
                file_count-=1;
                for(i=temp;i<19;i++){
                strcpy(dir[temp].file_name, dir[temp+1].file_name);
                }
                
                }
                else
                printf("\nFile not found!\n");
                
                break;
            }
            case 6:{
                printf("Enter file name: ");
                scanf("%s", search_file);
                temp = search_2(search_file, dir);
                
                if(temp != -999){
                    printf("\nFile path: root/%s/%s", dir[temp].dir_name, dir[temp].file_name);
                }
                else
                    printf("\nFile not found!\n");
                
                break;
            }
            case 7:{
                for(i=0;i<=dir_count;i++){
                    printf("<%s>\t", root[i].dir_name);
                    for(j=0;j<=file_count;j++){
                        if(strcmp(root[i].dir_name, dir[j].dir_name) == 0){
                            printf("%s\t", dir[j].file_name);
                        }
                    }
                    printf("\n");
                }
            }
        }
    }
}
