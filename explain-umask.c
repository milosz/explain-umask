#include <stdlib.h>
#include <sys/stat.h>

mode_t read_umask(void);

int main()
{
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
