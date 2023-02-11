#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *obj;

char prog_name[10], record[100], locn[4], instr[2], reloc_bits[3], bit_mask[30], objcode[6], cnt[2];

int i, j, k=0, flag=0, rec_len, start, ind, new_loc, load_addr, count=0;
long rel_addr;

void convert_to_bin(){
    i=0;
    while (reloc_bits[i]) {
        switch (reloc_bits[i]) {
            case '0': strcat(bit_mask, "0000"); break;
            case '1': strcat(bit_mask, "0001"); break;
            case '2': strcat(bit_mask, "0010"); break;
            case '3': strcat(bit_mask, "0011"); break;
            case '4': strcat(bit_mask, "0100"); break;
            case '5': strcat(bit_mask, "0101"); break;
            case '6': strcat(bit_mask, "0110"); break;
            case '7': strcat(bit_mask, "0111"); break;
            case '8': strcat(bit_mask, "1000"); break;
            case '9': strcat(bit_mask, "1001"); break;
            case 'A': case 'a': strcat(bit_mask, "1010"); break;
            case 'B': case 'b': strcat(bit_mask, "1011"); break;
            case 'C': case 'c': strcat(bit_mask, "1100"); break;
            case 'D': case 'd': strcat(bit_mask, "1101"); break;
            case 'E': case 'e': strcat(bit_mask, "1110"); break;
            case 'F': case 'f': strcat(bit_mask, "1111"); break;
        }
        
        i++;
    }
}

int main(){

    printf("\nEnter the name of the program to be loaded: ");
    scanf("%s", prog_name);

    obj = fopen("obj2.txt", "r");
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
            bit_mask[0] = '\0';
            if(record[0] == 'T'){
                for (j=4, k=0; j<8, k<4; k++, j++){ //read start location from text record
                    locn[k] = record[j];
                }

                sscanf(locn, "%x", &start);
                new_loc = start;

                for(i=12, j=0; i<15, j<3; i++, j++){ //read relocating bits
                    reloc_bits[j] = record[i];
                }

                for(i=9, k=0; i<11, k<2; i++, k++){ //get instruction length
                    cnt[k] = record[i];
                }

                sscanf(cnt, "%x", &count);
                
                count = count/3; //dividing by 3 to get total no of object codes

                convert_to_bin();   //get the bit mask

                ind = 16;
                for(i=0; i<10; i++){
                    while(count > 0){
                        for(j=0, k=ind; j<6, k<ind+6; j++, k++){
                                objcode[j] = record[k];
                            }
                        ind+=7;
                        
                        if(bit_mask[i] == '1'){ //relocation required
                            sscanf(objcode, "%x", &rel_addr);
                            printf("00%x\t  %x\n", new_loc+load_addr, rel_addr + load_addr);
                            new_loc += 3;
                            count--;
                            break;
                        }
                        else{ //relocation not required
                            sscanf(objcode, "%x", &rel_addr);
                            printf("00%x\t  %x\n", new_loc+load_addr, rel_addr);
                            new_loc += 3;
                            count--;
                            break;
                        }
                    }

                }
            }
            fscanf(obj, "%s", record);
        }

        
    }
    return 0;
}
