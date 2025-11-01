#include &lt;stdlib.h&gt;
#include &lt;stdio.h&gt;
#include &lt;sys/stat.h&gt;

mode_t read_umask(void);
void print_permissions(int octal_value);
void print_permission_string(int user, int group, int other, char prefix);

int main()
{
  mode_t mask = read_umask();

  // Extract octal values
  int octal_mask_user  = mask &gt;&gt; 6;
  int octal_mask_group = (mask & 56) &gt;&gt; 3;
  int octal_mask_other = mask & 7;

  // Print octal representation
  printf("Octal    representation: %i%i%i\n",
         octal_mask_user, octal_mask_group, octal_mask_other);

  // Print binary representation
  printf("Binary   representation: ");
  for(int i = 8; i &gt;= 0; i--) {
    printf("%i", (mask & (1 &lt;&lt; i)) ? 1 : 0);
    if(i == 6 || i == 3) printf(" ");
  }
  printf("\n");

  // Print symbolic representation
  printf("Symbolic representation: u=");
  print_permissions(octal_mask_user);
  printf(",g=");
  print_permissions(octal_mask_group);
  printf(",o=");
  print_permissions(octal_mask_other);
  printf("\n\n");

  // Calculate default permissions
  int octal_def_user_file  = (octal_mask_user  &gt; 6) ? 0 : (6 - octal_mask_user);
  int octal_def_group_file = (octal_mask_group &gt; 6) ? 0 : (6 - octal_mask_group);
  int octal_def_other_file = (octal_mask_other &gt; 6) ? 0 : (6 - octal_mask_other);
  int octal_def_user_dir   = 7 - octal_mask_user;
  int octal_def_group_dir  = 7 - octal_mask_group;
  int octal_def_other_dir  = 7 - octal_mask_other;

  // Print default file permissions
  printf("Default file permissions:      666 - %i%i%i = %i%i%i ",
         octal_mask_user, octal_mask_group, octal_mask_other,
         octal_def_user_file, octal_def_group_file, octal_def_other_file);
  print_permission_string(octal_def_user_file, octal_def_group_file, 
                          octal_def_other_file, '-');

  // Print default directory permissions
  printf("Default directory permissions: 777 - %i%i%i = %i%i%i ",
         octal_mask_user, octal_mask_group, octal_mask_other,
         octal_def_user_dir, octal_def_group_dir, octal_def_other_dir);
  print_permission_string(octal_def_user_dir, octal_def_group_dir,
                          octal_def_other_dir, 'd');

  return 0;
}

void print_permissions(int octal_value) {
  printf("%c", (octal_value & 4) ? 'r' : '-');
  printf("%c", (octal_value & 2) ? 'w' : '-');
  printf("%c", (octal_value & 1) ? 'x' : '-');
}

void print_permission_string(int user, int group, int other, char prefix) {
  printf("[%c", prefix);
  print_permissions(user);
  print_permissions(group);
  print_permissions(other);
  printf("]\n");
}

mode_t read_umask(void) {
  mode_t mask = umask(0);
  umask(mask);
  return mask;
}
