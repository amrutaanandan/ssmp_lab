#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct directory{
  char file_name[50];
};

int search(char search_file[10], struct directory root[20]){
  int i,value;
  for(i=0;i<20;i++){

    if(strcmp(search_file, root[i].file_name) == 0){
      return i;
    }
  }
return -999;
}

void main(){
  int option, file_count = -1,temp,i;
  struct directory root[20];
  char search_file[50],temp2[50];

  for(i=0;i<20;i++){
    strcpy(root[i].file_name, "null");
  }

  while(option != 5){
    printf("\n\n\t\t<Menu>\n");
    printf("1.\tCreate file\n2.\tDelete file\n3.\tSearch file\n4.\tls\n5.\tExit\n");
    scanf("%d", &option);

    switch(option){
      case 1:{
      printf("Enter file name: ");
      file_count+=1;
      scanf("%s", root[file_count].file_name);
      printf("\nCreated successfully!\nPath: root/%s\n", root[file_count].file_name);
      break;
    }

      case 2:{
        printf("Enter file name: ");
        scanf("%s", search_file);

        temp = search(search_file, root);

        if(temp != -999){
          printf("\nDeleted succesfully!\n");
          for(i=temp;i<19;i++){
            strcpy(root[i].file_name, root[i+1].file_name);
          }

        }
       else
          printf("\nFile not found!\n");

        break;
      }
      case 3:{
        printf("Enter file name: ");
        scanf("%s", search_file);

        temp = search(search_file, root);

        if(temp != -999){
          printf("\nFile path: root/%s", root[temp].file_name);
        }
        else
          printf("\nFile not found!\n");

        break;
      }
      case 4:{
        for(i=0;i<20;i++){
          if(strcmp(root[i].file_name, "null") != 0)
            printf("%s\t",root[i].file_name);
        }
        break;
      }
    }
  }
}
