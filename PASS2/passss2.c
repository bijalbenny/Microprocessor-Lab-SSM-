#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main() {
     FILE *optab = fopen("optab.txt", "r"),
         *intermediate = fopen("intermediate.txt", "r"),
         *symtab = fopen("symtab.txt", "r"),
         *output = fopen("output.txt", "w"),
         *objectcode = fopen("objectcode.txt", "w"),
         *prgmlength = fopen("length.txt", "r");
    char opcode[20], operand[20], label[20], code[20], value[20], textRecord[70] = "";
    int locctr, start, programLength, length = 0, textStartAddr;
    fscanf(intermediate, "%s %s %s", label, opcode, operand);
    fprintf(output, "     %-7s%-7s%-7s\n", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        fscanf(prgmlength, "%d", &programLength);
        start = atoi(operand);
        fprintf(objectcode, "H^%s^%06d^%06d\n", label, start, programLength);
    }
    fscanf(intermediate, "%d %s %s %s", &locctr, label, opcode, operand);
    textStartAddr = locctr;
    while (strcmp(opcode, "END") != 0) {
        char objectCode[10] = "";
        fprintf(output, "%d %-7s%-7s%-7s", locctr, label, opcode, operand);
        if (strcmp(opcode, "BYTE") == 0) {
            if (operand[0] == 'C' && operand[1] == '\'') {
                for (int i = 2; i < strlen(operand) - 1; i++)
                    sprintf(objectCode + strlen(objectCode), "%02X", operand[i]);
            }
        } else if (strcmp(opcode, "WORD") == 0) {
            sprintf(objectCode, "%06d", atoi(operand));
        } else if (strcmp(opcode, "RESB") != 0 && strcmp(opcode, "RESW") != 0) {
            rewind(optab);
            while (fscanf(optab, "%s %s", code, value) != EOF) {
                if (strcmp(opcode, code) == 0) {
                    strcpy(objectCode, value);
                    break;
                }
            }
            rewind(symtab);
            while (fscanf(symtab, "%s %s", label, value) != EOF) {
                if (strcmp(operand, label) == 0) {
                    sprintf(objectCode + strlen(objectCode), "%04d", atoi(value));
                    break;
                }
            }
        }
        fprintf(output, "%s\n", objectCode);
        if (length + strlen(objectCode) > 60) {
            fprintf(objectcode, "T^%06d^%02X^%s\n", textStartAddr, length / 2, textRecord);
            strcpy(textRecord, "");
            textStartAddr = locctr;
            length = 0;
        }
        if (strlen(objectCode) > 0) {
            strcat(textRecord, objectCode);
            strcat(textRecord, "^");
            length += strlen(objectCode);
        }
        fscanf(intermediate, "%d %s %s %s", &locctr, label, opcode, operand);
    }
    if (length > 0) {
        textRecord[strlen(textRecord) - 1] = '\0';
        fprintf(objectcode, "T^%06d^%02X^%s\n", textStartAddr, length / 2, textRecord);
    }
    fprintf(objectcode, "E^%06d\n", start);
    fclose(intermediate); fclose(symtab); fclose(optab); fclose(output); fclose(prgmlength);
    printf("FINISHED EXECUTION!!!\n");
}













/*
    #include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    // File pointers for input and output files
    FILE *intermediate, *optab, *symtab, *output, *prgmlength, *objectcode;

    // Variables for parsing input and storing codes
    char opcode[20], operand[20], label[20], mneumonic[20], code[20], value[20], textRecord[70];
    int locctr, start, programLength, length = 0, textStartAddr;

    // Opening necessary files
    optab = fopen("optab.txt", "r");
    intermediate = fopen("intermediate.txt", "r");
    symtab = fopen("symtab.txt", "r");
    output = fopen("output.txt", "w");
    objectcode = fopen("objectcode.txt", "w");
    prgmlength = fopen("prgmlength.txt", "r");

    // Check if all files opened successfully
    if (!optab || !intermediate || !symtab || !output || !prgmlength) {
        printf("Error opening files\n");
        return;
    }

    // Reading the first line from the intermediate file
    fscanf(intermediate, "%s %s %s", label, opcode, operand);
    printf("First input line: %s %s %s\n", label, opcode, operand);

    // Write first line to output file
    fprintf(output, "     %-7s%-7s%-7s\n", label, opcode, operand);

    // If the opcode is START, initialize program start address and write header record
    if (strcmp(opcode, "START") == 0) {
        fscanf(prgmlength, "%d", &programLength);
        start = atoi(operand); // Convert operand to integer
        fprintf(objectcode, "H^%s^%06d^%06d\n", label, start, programLength);
    }

    // Reading the next line for processing
    fscanf(intermediate, "%d %s %s %s", &locctr, label, opcode, operand);
    textStartAddr = locctr; // Set start address of text record
    strcpy(textRecord, ""); // Initialize text record

    // Process each line until opcode END is encountered
    while (strcmp(opcode, "END") != 0) {
        char objectCode[10] = ""; // Initialize object code as empty

        printf("Processing line: %d %s %s %s\n", locctr, label, opcode, operand);
        fprintf(output, "%d %-7s%-7s%-7s", locctr, label, opcode, operand);

        // Generate object code based on opcode type
        if (strcmp(opcode, "BYTE") == 0) {
            // Convert character constants to hex
            if (operand[0] == 'C' && operand[1] == '\'') {
                for (int i = 2; i < strlen(operand) - 1; i++) {
                    sprintf(objectCode + strlen(objectCode), "%02X", operand[i]);
                }
            } else if (strcmp(operand, "C'EOF'") == 0) {
                strcpy(objectCode, "454F46"); // Special case for "C'EOF'"
            }
        } else if (strcmp(opcode, "WORD") == 0) {
            sprintf(objectCode, "%06d", atoi(operand)); // WORD as a 6-digit number
        } else if (strcmp(opcode, "RESB") == 0 || strcmp(opcode, "RESW") == 0) {
            // No object code for RESB and RESW
        } else {
            // Search for opcode in OPTAB
            rewind(optab);
            while (fscanf(optab, "%s %s", mneumonic, code) != EOF) {
                if (strcmp(opcode, mneumonic) == 0) {
                    strcpy(objectCode, code);
                    break;
                }
            }

            // If operand is a label, find its address in SYMTAB
            rewind(symtab);
            while (fscanf(symtab, "%s %s", label, value) != EOF) {
                if (strcmp(operand, label) == 0) {
                    sprintf(objectCode + strlen(objectCode), "%04d", atoi(value));
                    break;
                }
            }
        }

        // Output the object code
        printf("Object Code: %s\n", objectCode);
        fprintf(output, "%s\n", objectCode);

        // Manage text record size
        if (length + strlen(objectCode) > 60) {
            fprintf(objectcode, "T^%06d^%02X^%s\n", textStartAddr, length / 2, textRecord);
            strcpy(textRecord, ""); // Reset text record
            textStartAddr = locctr; // Update start address
            length = 0;
        }

        // Append object code to text record if available
        if (strlen(objectCode) > 0) {
            strcat(textRecord, objectCode);
            strcat(textRecord, "^");
            length += strlen(objectCode);
        }

        // Read the next line
        fscanf(intermediate, "%d %s %s %s", &locctr, label, opcode, operand);
    }

    // Write the final text record
    if (length > 0) {
        textRecord[strlen(textRecord) - 1] = '\0'; // Remove trailing '^'
        fprintf(objectcode, "T^%06d^%02X^%s\n", textStartAddr, length / 2, textRecord);
    }

    // Write end record
    fprintf(output, "%d %-7s%-7s%-7s", locctr, label, opcode, operand);
    fprintf(objectcode, "E^%06d\n", start);

    // Close all files
    fclose(intermediate);
    fclose(symtab);
    fclose(optab);
    fclose(output);
    fclose(prgmlength);
    fclose(objectcode);

    printf("FINISHED EXECUTION!!!\n");
}
*/
