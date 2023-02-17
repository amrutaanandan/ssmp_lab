#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *obj;

struct mod{ //structure to store modification locations and operation to be done on them
    char op[10];
    int reloc[10];
    int flag[10];
}r;

char prog_name[10], record[100], locn[6], instr[2], objcode[9], cnt[2], relocn[6];

int i, j, k=0, flag=0, rec_len, start, ind, new_loc, load_addr, count=0, mod_count=0, minstr;
int rel_addr;


int main(){

    printf("\nEnter the name of the program to be loaded: ");
    scanf("%s", prog_name);

    obj = fopen("obj3.txt", "r");
    fscanf(obj, "%s", record);

    for(i=0; i<strlen(prog_name); i++){
        if(record[i+2] == prog_name[i]){
            flag=0;
        }
        else{
            flag=1;
            break;
        }
    }
    if (flag == 1){
        printf("Invalid program name!\n");
    }
    else{
        printf("\nEnter load address: ");
        scanf("%x", &load_addr);
        for(i=strlen(prog_name)+5, k=0; k<4, i<= strlen(prog_name)+8; k++, i++){
            locn[k] = record[i];
        }

        while(record[0] != 'E'){
            if(record[0] == 'M'){
                for(i=2, j=0; i<8, j<6; i++, j++){
                    relocn[j] = record[i];
                }

                sscanf(relocn, "%x", &rel_addr);
                
                rel_addr += load_addr;

                r.reloc[mod_count] = rel_addr;  //inserting location to be modified
                r.op[mod_count] = record[11];   //inserting the operation:'+' or '-'
                r.flag[mod_count] = 0;          //flag to see if relocation has already happened for the location
                mod_count ++;
            }
            
            fscanf(obj, "%s", record);
        }

        rewind(obj);
        fscanf(obj, "%s", record);
        printf("\nLocation  Object Code\n");
        while(record[0] != 'E'){
            if(record[0] == 'T'){
                for (j=4, k=0; j<8, k<4; k++, j++){ //read start location from text record
                    locn[k] = record[j];
                }

                sscanf(locn, "%x", &start);
                new_loc = start;
                new_loc += load_addr;

                for(i=9, k=0; i<11, k<2; i++, k++){ //get instruction length
                    cnt[k] = record[i];
                }

                sscanf(cnt, "%x", &count);
                
                count = count/3; //dividing by 3 to get total no of object codes

                ind = 12;
                for(i=0; i<10; i++){
                    while(count > 0){
                        objcode[0] = '\0';
                        for(j=0, k=ind; j<6, k<ind+6; j++, k++){
                            objcode[j] = record[k];
                        }
                        ind+=6;

                        if(record[ind] == '^' || record[ind] == '\0'){ //if the objet is not a byte constant i.e. object code length = 6
                            ind++;
                            objcode[j] = '\0';
                        }
                        else{
                            while(record[ind] != '^'){ //if the object code is a byte constant
                                if(record[ind] == '\0'){ //if it is the last instruction
                                    break;
                                }
                                objcode[j] = record[ind];
                                ind++;
                                j++;
                            }

                            ind++;
                        }

                        objcode[j] == '\0'; //setting the end of the string

                        sscanf(objcode, "%x", &minstr);
                        
                        for(i=0; i< mod_count; i++){
                            if(r.reloc[i] > new_loc && r.reloc[i] < new_loc+4 && r.flag[i] != 1){ //if the current location requires modification
                                if(r.op[i] == '+'){
                                    minstr += load_addr;
                                    
                                }
                                else{
                                    minstr -= load_addr;
                                }
                                r.flag[i] = 1;  //location modified
                                break;
                            }
                        }
                        
                        printf("\n  %x    %x",new_loc,minstr);
                        new_loc += strlen(objcode)/2; //add number of half bytes in object code to new_locn
                        count--;                      
                    }

                }
            }
            fscanf(obj, "%s", record);
        }
    }
    return 0;
}
