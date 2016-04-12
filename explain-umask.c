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

  // calculated default permissions
  int octal_def_user_file, octal_def_group_file, octal_def_other_file;
  int octal_def_user_dir, octal_def_group_dir, octal_def_other_dir;

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

  printf("\n"); // spacer

  // calculate default permissions
  octal_def_user_file  = octal_mask_user  > 6 ? 0 : (6 - octal_mask_user);
  octal_def_group_file = octal_mask_group > 6 ? 0 : (6 - octal_mask_group);
  octal_def_other_file = octal_mask_other > 6 ? 0 : (6 - octal_mask_other);
  octal_def_user_dir   =                            (7 - octal_mask_user);
  octal_def_group_dir  =                            (7 - octal_mask_group);
  octal_def_other_dir  =                            (7 - octal_mask_other);

  // print default permissions
  printf("Default file permissions:      666 - %i%i%i = %i%i%i ",
	 octal_mask_user, octal_mask_group, octal_mask_other,
	 octal_def_user_file, octal_def_group_file, octal_def_other_file);

  printf("[-");
  if(octal_def_user_file  & 4) printf("r"); else printf("-");
  if(octal_def_user_file  & 2) printf("w"); else printf("-");
  if(octal_def_user_file  & 1) printf("x"); else printf("-");
  if(octal_def_group_file & 4) printf("r"); else printf("-");
  if(octal_def_group_file & 2) printf("w"); else printf("-");
  if(octal_def_group_file & 1) printf("x"); else printf("-");
  if(octal_def_other_file & 4) printf("r"); else printf("-");
  if(octal_def_other_file & 2) printf("w"); else printf("-");
  if(octal_def_other_file & 1) printf("x"); else printf("-");
  printf("]\n");

  printf("Default directory permissions: 777 - %i%i%i = %i%i%i ",
	 octal_mask_user, octal_mask_group, octal_mask_other,
	 octal_def_user_dir, octal_def_group_dir,octal_def_other_dir);

  printf("[d");
  if(octal_def_user_dir  & 4) printf("r"); else printf("-");
  if(octal_def_user_dir  & 2) printf("w"); else printf("-");
  if(octal_def_user_dir  & 1) printf("x"); else printf("-");
  if(octal_def_group_dir & 4) printf("r"); else printf("-");
  if(octal_def_group_dir & 2) printf("w"); else printf("-");
  if(octal_def_group_dir & 1) printf("x"); else printf("-");
  if(octal_def_other_dir & 4) printf("r"); else printf("-");
  if(octal_def_other_dir & 2) printf("w"); else printf("-");
  if(octal_def_other_dir & 1) printf("x"); else printf("-");
  printf("]\n");

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
