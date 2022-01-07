#include<unistd.h>
void main()
{ setuid(0);
  setgid(0);
  system("tobeX"); //change the binary name to whatever u want
}
