#include <stdio.h>

static char *petscii_convert(char *msg) {

  char *cur_char = msg;

  while(*cur_char) {
  
    if( *cur_char >= 'a' && *cur_char <= 'z') {
      *cur_char = *cur_char - 'a' + 'A';  // Convert to upper case.
    }

     ++cur_char;
   }

   return msg;
}

int main (int argc, char** argv) {

  puts( petscii_convert( "Hello world!\n"));

  return 0;
}
