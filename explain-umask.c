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

  // read umask
  mask=read_umask();

  // calculate octal values
  octal_mask_user=mask >> 6;          //  XXX000000
  octal_mask_group=(mask & 56) >> 3;  //  000XXX000
  octal_mask_other=mask & 7;          //  000000XXX

  // print octal representation
  printf("Octal    representation: %i%i%i\n", \
	 octal_mask_user, octal_mask_group, octal_mask_other);

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
