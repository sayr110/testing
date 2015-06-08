#include <stdio.h>



int char_atoi(char *s);


int main(int argc, char **argv) {
  FILE *fp,*fpu;
  char key;
  int temp;
  char c;
  if(3 != argc) {
    printf("Error: need 3 arguments/n");
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
    printf("Error: failed to open file/n");
    return -1;
  }

/*create output file*/
  fpu = fopen("output.txt", "rb+");
  if(NULL == fpu) /*if file does not exist, create it*/
  {
    fpu = fopen("output.txt", "wb");
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
