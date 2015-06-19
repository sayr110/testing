#ifndef CONFIG_H
#define CONFIG_H

#define BYTES_TO_VALIDATE 4
#define MAGIC_STRING 'A'


int char_atoi(char *);
int validate_file(FILE *);
void print_usage();


#endif