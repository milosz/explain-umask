#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

mode_t read_umask(void);

int main()
{
  // mask value
  mode_t mask;

  // extracted values
  int octal_mask_user, octal_mask_group, octal_mask_other;
  int binary_mask[8]; // UUUGGGOOO

  // temporary variable
  int i;

  // read umask
  mask=read_umask();

  // calculate octal values
  octal_mask_user=mask >> 6;          //  XXX000000
  octal_mask_group=(mask & 56) >> 3;  //  000XXX000
  octal_mask_other=mask & 7;          //  000000XXX

  // print octal representation
  printf("Octal    representation: %i%i%i\n", \
	 octal_mask_user, octal_mask_group, octal_mask_other);

  //calculate binary form
  for(i=8; i>=0; i--) {
    binary_mask[-(i-8)]=(mask & (1 << i)) ? 1 : 0;
  }

  // print binary representation
  printf("Binary   representation: ");
  for(i=0; i<=8; i++) {
    printf("%i",binary_mask[i]);
    if(i == 2 || i == 5) printf(" "); // add space
  }
  printf("\n");

  // calculate and print symbolic representation
  printf("Symbolic representation: u=");
  if(octal_mask_user & 4) printf("r");
  if(octal_mask_user & 2) printf("w");
  if(octal_mask_user & 1) printf("x");
  printf(",g=");
  if(octal_mask_group & 4) printf("r");
  if(octal_mask_group & 2) printf("w");
  if(octal_mask_group & 1) printf("x");
  printf(",o=");
  if(octal_mask_other & 4) printf("r");
  if(octal_mask_other & 2) printf("w");
  if(octal_mask_other & 1) printf("x");
  printf("\n");

  // exit
  exit(0);
}

mode_t read_umask(void) {
  // how to read the mask with umask without changing it permanently:
  // http://www.gnu.org/software/libc/manual/html_node/Setting-Permissions.html
  mode_t mask = umask (0);
  umask (mask);
  return mask;
}
