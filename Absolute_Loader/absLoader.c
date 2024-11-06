#include <stdio.h>
#include <stdlib.h>
void main() {
    FILE *fp = fopen("record.txt", "r");
    char line[50];
    int length, i;
    fscanf(fp, "%s", line);
    printf("Program name is : ");
    for (i = 4; i < 8; i++) {
        printf("%c", line[i]);
    }
    printf("\n");
    while (fscanf(fp, "%s", line) != EOF) {
        if (line[0] == 'T') {
            length = atoi(line + 2);
            i = 12;
            while (line[i] != '$') {
                if (line[i] != '^') {
                    printf("%d : \t %c%c\n", length, line[i], line[i+1]);
                    length++;
                    i += 2;
                } else {
                    i++;
                }
            }
        } else if (line[0] == 'E') {
            break; 
        }
    }
    fclose(fp);
}
