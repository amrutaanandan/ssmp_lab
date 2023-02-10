#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *obj, *optab, *symtab, *imdt, *length;
int tot_len, i, flag = 0, nim;

char label[10] = {' '}, operand[10] = {' '}, opcode[10] = {' '}, optab_opcode[10] = {' '};
char optab_mnemonic[10] = {' '}, symtab_opcode[10] = {' '}, symtab_operand[10] = {' '}, minstr[6]={' '};
int LOCCTR, start_address, symbol_dupl;

void convert_to_hex(){
    fprintf(obj,"^");
    for(i=2; i<strlen(operand)-1; i++){
        fprintf(obj, "%x", operand[i]);
    }
}

void get_symbol(){
    symtab = fopen("Symtab.txt", "r");
    fscanf(symtab, "%s%s", symtab_operand, symtab_opcode);
    while(!feof(symtab)){
        if(strcmp(symtab_operand, operand) == 0){
            strcat(minstr, symtab_opcode);
            break;
        }
        fscanf(symtab, "%s%s", symtab_operand, symtab_opcode);
    }
    
    rewind(symtab);
}

void get_opcode(){
    optab = fopen("optab.txt", "r");
    fscanf(optab, "%s%s", optab_mnemonic, optab_opcode);
    while(!feof(optab)){
        if(strcmp(optab_mnemonic, opcode) == 0){
            strcpy(minstr, optab_opcode);
            if(strcmp(operand, "-") != 0){
                get_symbol();
                fprintf(obj,"^%s", minstr);
            }
            else{
                strcat(minstr, "0000");
                fprintf(obj,"^%s", minstr);
            }
            break;
        }
        else if(strcmp(opcode, "BYTE") == 0 || strcmp(opcode, "WORD") == 0){
            if(strcmp(opcode, "WORD") == 0){
                strcpy(minstr, "00000");
                strcat(minstr, operand);
                fprintf(obj,"^%s", minstr);
                break;
            }
            else{
                convert_to_hex();
                break;
            }
            flag=1;
        }
        else if(strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0){
            break;
        }
        
        fscanf(optab, "%s%s", optab_mnemonic, optab_opcode);
    }
    rewind(optab);
}



int main(){
    
    imdt = fopen("intermediate.txt", "r");
    obj = fopen("object.txt", "w");
    length = fopen("length.txt", "r");

    fscanf(imdt, "%s%s%s%s%x", operand, optab_opcode, label, opcode, &LOCCTR);
    fscanf(length, "%x", &tot_len);

    if(strcmp(opcode, "START") == 0){
        fprintf(obj, "H^%s^00%x^0000%x\n",label, LOCCTR, tot_len);
    }
    fprintf(obj,"T^%x", tot_len-3);

    fscanf(imdt, "%x%x%s%s%s", &LOCCTR, &instr_len, label, opcode, operand);
    while(strcmp(opcode, "END") != 0){
        get_opcode();
        fscanf(imdt, "%x%x%s%s%s", &LOCCTR, &instr_len, label, opcode, operand);
    }
    fprintf(obj, "\n");
    fprintf(obj, "E^00%x", tot_len);
    fclose(optab);
    return 0;
}
