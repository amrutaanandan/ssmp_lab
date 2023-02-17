#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *program, *optab, *symtab, *imdt, *length, *create_symtab, *littab;
int error=0, instr_len = 3, curr, i=0, j=0, k=0;

char label[10] = {' '}, operand[10] = {' '}, opcode[10] = {' '}, optab_opcode[10] = {' '}, hexlit[2];
char optab_mnemonic[10] = {' '}, symtab_opcode[10] = {' '}, symtab_operand[10] = {' '};

int LOCCTR, start_address, symbol_dupl, hex;

/*--------------------READING FROM OPTAB AND GETTING LOCCTR--------------------*/

void read_from_optab() {
  optab = fopen("optab.txt", "r");
  fscanf(optab, "%s %s", optab_opcode, optab_mnemonic);

  while (!feof(optab)) {
    //if found then 
    if (strcmp(opcode, optab_opcode) == 0) {
      //add 3 {instruction length} to locctr
      LOCCTR += 3;
      break;
    }
    fscanf(optab, "%s %s", optab_opcode, optab_mnemonic);
  }
  
  if(strcmp(opcode, "LTORG") == 0){
     LOCCTR += 0;
  }
  //if the operand is a literal, enter it into littab
  if(operand[0] == '='){
    
    for(i=1; i<strlen(operand); i++)  //entering literal name
      fprintf(littab, "%c", operand[i]);
      
    fprintf(littab, "\t");
    
    
    for(i=3; i<strlen(operand)-1; i++){ //entering literal value
      if(operand[1] == 'C')
        fprintf(littab, "%x", operand[i]);
      else
        fprintf(littab, "%c", operand[i]);
    }
    
    if(operand[1] == 'C'){  //literal length
      fprintf(littab, "\t%x\t%x", (int)(strlen(operand)-4),LOCCTR);
    }
    else{
      for(i=3, j=0; i<strlen(operand), j<2; j++, i++){
        hexlit[j] = operand[i];
      }
      sscanf(hexlit, "%x", &hex);
      hexlit[0] = '\0';
      sprintf(hexlit,"%x", hex);
      fprintf(littab, "\t%x\t%x", (int)strlen(hexlit), LOCCTR);
    }
    
    fprintf(littab, "\n");
  }
  
  //else if opcode = 'RESW' then
  if (strcmp(opcode, "RESW") == 0) {
    LOCCTR += atoi(operand) * 3;
  }
  //else if opcode = 'WORD' then
  else if (strcmp(opcode, "WORD") == 0) {
    LOCCTR += 3;
  }
  //else if opcode = 'RESB' then
  else if (strcmp(opcode, "RESB") == 0) {
    LOCCTR += atoi(operand);
  }
  //else if opcode = 'BYTE' then
  else if (strcmp(opcode, "BYTE") == 0) {
    LOCCTR += strlen(operand) - 3;
      
  }
  //else if it is a format 4 instruction
  else if (opcode[0] == '+') {
    LOCCTR += 4;
  }
    else{
    //set error flag {invalid operation code}
     error = 0;
    }
    
  fclose(optab);
}

/*--------------------SEARCHING IN SYMTAB FOR SYMBOLS--------------------*/

void search_in_symtab() {
  FILE *symtab;
  symbol_dupl = 0;
  int count = 0;
  symtab = fopen("symtab.txt", "r+");

  while (!feof(symtab)) {
    fscanf(symtab, "%s\t%s", symtab_opcode, symtab_operand);

    //if symbol found in symtab then 
    if (strcmp(label, symtab_opcode) == 0) {
      symbol_dupl = 1;
    //set error flag {duplicate symbol}
      error = 1;
      break;
    }
  }
  //else insert {label, locctr} into symtab
  if (symbol_dupl == 0) {
    
    fprintf(symtab, "%s\t%x\n", label, LOCCTR);

  }

  fclose(symtab);
}

/*--------------------GETTING INSTRUCTION LENGTH--------------------*/

void get_instr_len() {
  optab = fopen("optab.txt", "r");
  fscanf(optab, "%s %s", optab_opcode, optab_mnemonic);

  while (!feof(optab)) {
    //if found then 
    if (strcmp(opcode, optab_opcode) == 0) {
      //add 3 {instruction length} to locctr
      instr_len = 3;
      break;
    }
    fscanf(optab, "%s %s", optab_opcode, optab_mnemonic);
  }
  
  //else if opcode = 'RESW' then
  if (strcmp(opcode, "RESW") == 0) {
    instr_len = atoi(operand) * 3;
  }
  //else if opcode = 'WORD' then
  else if (strcmp(opcode, "WORD") == 0) {
    instr_len = 3;
  }
  //else if opcode = 'RESB' then
  else if (strcmp(opcode, "RESB") == 0) {
    instr_len = atoi(operand);
  }
  //else if opcode = 'BYTE' then
  else if (strcmp(opcode, "BYTE") == 0) {
    instr_len = strlen(operand) - 3;
      
  }
  //else if it is a format 4 instruction
  else if (opcode[0] == '+') {
    instr_len = 4;
  }
    
  fclose(optab);
}

void main() {

  program = fopen("input.txt", "r");
  imdt = fopen("intermediate.txt", "w");
  length = fopen("length.txt", "w");
  create_symtab = fopen("symtab.txt", "w");
  littab = fopen("littab.txt", "w");
  fclose(create_symtab);

  // read first input line

  fscanf(program, "%s%s%x", label, opcode, &LOCCTR);

  if (strcmp(opcode, "START") == 0) {
    // save #[operand] as starting start_address
    // initialize LOCCTR to start address
    start_address = LOCCTR;
    fprintf(imdt, "-\t    -  \t%s\t%s\t%s\n", label, opcode, operand);

    // read next input line
    fscanf(program, "%s%s%s", label, opcode, operand);
  } else {
    // initialize LOCCTR to zero
    LOCCTR = 0;
  }

  // while opcode not equal to end
  while (strcmp(opcode, "END") != 0) {

    // if not a comment line then
    if (label[0] != ';') {
      get_instr_len();
      // write file to intermediate text
      if(strcmp(opcode, "LTORG") != 0)
        fprintf(imdt, "%x\t%d\t%s\t%s\t%s\n", LOCCTR, instr_len, label, opcode, operand);
      else
        fprintf(imdt,"  -  \t-  \t-  \tLTORG\t  -\n");

      if (strcmp(label, "-") != 0 && strcmp(label, "START") != 0) {
        // if there is a symbol in label field then
        //search symtab for label
        search_in_symtab();
      }

        //search optab for opcode
        read_from_optab();
    }
    //read next input line
    fscanf(program, "%s%s%s", label, opcode, operand);
  }
  //write last line to intermediate file
  fprintf(imdt, "%x\t%d\t%s\t%s\t%s\n", LOCCTR, instr_len, label, opcode, operand);
  //save {LOCCTR - starting address} as program length
  fprintf(length, "%x", LOCCTR - start_address);

  fclose(program);
  fclose(imdt);
  fclose(length);
}

/*Output format:                                
-----------------------------------------------
Intermediate.txt:
-	     -  	     COPY	     START	 
4000 3	START	LDA	     ALPHA
4003	3	-	     ADD	     ONE
4006	3	-	     SUB	     TWO
4009	4	-	     +STA	     BETA
400d	3	-	     RSUB	     -
4010	5	ALPHA	BYTE	     C'HELLO'
4015	2	ONE	     RESB	     2
4017	3	TWO	     WORD	     5
401a	3	BETA	     RESW	     1
401d	3	-	     END	     START
-----------------------------------------------
Symtab.txt:

ALPHA     4010
ONE	     4015
TWO	     4017
BETA	     401a
-----------------------------------------------
Length.txt:

29*/
