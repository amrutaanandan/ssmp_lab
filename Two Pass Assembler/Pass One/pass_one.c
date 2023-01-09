#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *program, *optab, *symtab, *imdt, *length;

char label[10], operand[10], opcode[5], code[5], mnemonic[5], LOCCTR_hex[5];
int LOCCTR, start_address;

void read_from_optab(){
    optab = fopen("optab.txt", "r");
    fscanf(optab, "%s %s", code, mnemonic);

    while(strcmp(code, "END") != 0){
        if (strcmp(opcode, code) == 0){

            LOCCTR += 3;
            break;
        }
        fscanf(optab, "%s %s", code, mnemonic);
    }

    if (strcmp(opcode, "RESW") == 0){
            LOCCTR += atoi(operand)*3;
    }
    else if (strcmp(opcode, "WORD") == 0){
            LOCCTR += 3;
    }
    else if (strcmp(opcode, "RESB") == 0){
            LOCCTR += atoi(operand);
    }
    else if (strcmp(opcode, "BYTE") == 0){
            LOCCTR += strlen(operand) - 3;
    
    }
    else if (opcode[0] == '+'){
            LOCCTR += 4;
    }
    fclose(optab);
}

void main(){
    
    program = fopen("input.txt", "r");
    
    symtab = fopen("symtab.txt", "w");
    imdt = fopen("intermediate.txt", "w");
    length = fopen("length.txt", "w");


    fscanf(program, "%s%s%s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0){
        LOCCTR = atoi(operand);
        start_address = LOCCTR;
        fprintf(imdt, "- %s %s %s\n", label, opcode, operand);
        fscanf(program, "%s%s%s", label, opcode, operand);
    }
    else{
        LOCCTR = 0;
    }


    while(strcmp(opcode, "END") != 0){
        fprintf(imdt, "%d %s %s %s\n", LOCCTR, label, opcode, operand);

        if (strcmp(label, "-") != 0){
            fprintf(symtab, "%s\t%d\n", label, LOCCTR);
        }

        read_from_optab();

        fscanf(program, "%s%s%s", label, opcode, operand);
    }

    fprintf(imdt, "%d\t%s\t%s\t%s\n", LOCCTR, label, opcode, operand);

    fprintf(length, "%d", LOCCTR - start_address);

    fclose(program);
    fclose(symtab);
    fclose(imdt);
    fclose(length);

}
