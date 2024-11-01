#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
void main(){
    FILE *source = fopen("source.txt","r");
    FILE *optab = fopen("optab.txt","r");
    FILE *intermediate = fopen("intermediate.txt","w");
    FILE *symtab = fopen("symtab.txt","w+");
    FILE *length = fopen("length.txt","w");
    char label[20],opcode[20],operand[20],symtab_data[20],optab_data[20];
    int locctr=0,starting_address=0,program_length=0;
    bool symbol_found,opcode_found;
    //read first line
    fscanf(source,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0){
        starting_address=atoi(operand);
        locctr=starting_address;
        //write to intermediate
        fprintf(intermediate,"\t\t%s\t%s\t%s\n",label,opcode,operand);
        //read next line
        fscanf(source,"%s%s%s",label,opcode,operand);
    }
    while(strcmp(opcode,"END")!=0){
        if(strcmp(label,"**")!=0){//checks if the label is not empty
            symbol_found=false;
            rewind(symtab);//reset the pointer to the beginning to scan the label....
            while(fscanf(symtab,"%s",symtab_data)!=EOF){
                if(strcmp(symtab_data,label)==0){
                    printf("Error: Label found in SYMTAB\n");
                    symbol_found = true;
                    break;
                }
            }
            if(!symbol_found){
                fprintf(symtab,"%s\t%d\n",label,locctr);
            }
        }
        //check if opcode exists in OPTAB...........
        opcode_found=false;
        rewind(optab);
        while(fscanf(optab,"%s",optab_data)!=EOF){
            if(strcmp(optab_data,opcode)==0){
                opcode_found=true;
                break;
            }
        }
        fprintf(intermediate,"%d\t",locctr);
        if(opcode_found){
            locctr+=3;
        }
        else if(strcmp(opcode,"WORD")==0)
            locctr+=3;
        else if(strcmp(opcode,"RESW")==0)
            locctr+=3*atoi(operand);
        else if(strcmp(opcode,"RESB")==0)
            locctr+=atoi(operand);
        else if(strcmp(opcode,"BYTE")==0)
            locctr+=strlen(operand)-3;
        else
            printf("Error:Invalid operation code!!!");
        
        fprintf(intermediate,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(source, "%s%s%s", label, opcode, operand);//read last input line!!!!!!!!!!!
    }
    fprintf(intermediate,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    program_length = locctr - starting_address;
    printf("\nProgram Length: %d\n", program_length);
    fprintf(length, "%d", program_length);
    fclose(source);
    fclose(optab);
    fclose(intermediate);
    fclose(symtab);
    fclose(length);

}

