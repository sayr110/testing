#include <stdio.h>
#include "config.h"

int main(int argc, char **argv) {
  FILE *fp,*fpu;
  char key;
  int temp;
  char c;
  if(3 != argc) {
    print_usage();
    return -1;
  }

  temp = char_atoi(argv[2]);
  if(temp < 0) {
   return -1;
  }else {
    key = temp;
  }
/*open file*/
  fp = fopen(argv[1],"r");
  if(NULL == fp) {
    printf("Error: failed to open file\n");
    return -1;
  }

  if(validate_file(fp) == 0) {
    printf("Error: failed to validate the input file\n");
	return -1;
  }
  
  
/*create output file*/
  fpu = fopen("output.txt", "rb+");
  if(NULL == fpu) /*if file does not exist, create it*/
  {
   if((fpu = fopen("output.txt", "wb")) == NULL) {
      printf("Error: could not create file\n");
      return -1;
    }
  }

/*read xor and write*/
  while((c =fgetc(fp)) != EOF) {
    fprintf(fpu,"%c",c^key);
  }

/*close file*/
  if(fclose(fp)||fclose(fpu)) {
    printf("Error: failed to close file/n");
    return -1;
   }
  return 0;
}


int char_atoi(char *s) {
  
  int temp = atoi(s);
  if(temp > 255){
    printf("Error: key must be sizeof char");
    return -1;
  }
  return temp;
}


int validate_file(FILE *fp) {
  /* FIXME: TODO: Validate the first BYTES_TO_VALIDATE bytes and not just the first one */
  char *magic = MAGIC_STRING; // FIXME: TODO: magic to be char *
  FILE *temp = fp;
  char c;
  // FIXME: TODO: save the original file pointer position in order to restore it later (ftell)
  // Seek the file pointer to the start
  if(fseek(fp, 0, SEEK_SET) != 0) {
	return 1;
  }
  
  // read the magic
  while (c=fgetc(fp) != EOF) {
    if (*magic == '\0' || c != *magic) {
      printf("Error: not magic\n");
      return 1;
    }
    magic++;
  }
  
  // Restore the file pointer to the start
  if(fseek(fp, 0, SEEK_SET) != 0) {
	return 1;
  }
  
  // this file is okay
  return 0;
}

void print_usage() {
  printf("Usage: xorfile input.txt key\n");
}
