/*
========================================================================================================

Name: 2
Author: Prajyot Shende
Description: Write a simple program to execute in an infinite loop at the background. Go to /proc directory and identify all the process related information in the corresponding proc directory.
Date: 29th August, 2024

========================================================================================================
*/


#include<bits/stdc++.h>
using namespace std;
int main()
{
	cout<<"It will run in an infinte loop after you press something, parallely check /proc directory by using :- ps -e|grep a.out OR ps -e for all processes and to check ststus of tthe running program write the cmd :- ps ax | grep a.out\n";
	getchar();
	while(99999999);
}


/*
========================================================================================================
Output:

./a.out

ps ax | grep a.out
   9384 pts/0    S+     0:00 ./a.out


cat /proc/9384/status
Name:	a.out
Umask:	0002
State:	S (sleeping)
Tgid:	9384
Ngid:	0
Pid:	9384
PPid:	3731
TracerPid:	0
Uid:	1000	1000	1000	1000
Gid:	1000	1000	1000	1000
FDSize:	256
Groups:	4 24 27 30 46 100 118 1000 
NStgid:	9384
NSpid:	9384
NSpgid:	9384
NSsid:	3731
VmPeak:	    6176 kB
VmSize:	    6176 kB
VmLck:	       0 kB
VmPin:	       0 kB
VmHWM:	    3200 kB
VmRSS:	    3200 kB
RssAnon:	     160 kB
RssFile:	    3040 kB
RssShmem:	       0 kB
VmData:	     264 kB
VmStk:	     132 kB
VmExe:	       4 kB
VmLib:	    3504 kB
VmPTE:	      52 kB
VmSwap:	       0 kB
HugetlbPages:	       0 kB
CoreDumping:	0
THP_enabled:	1
Threads:	1
SigQ:	1/62515
SigPnd:	0000000000000000
ShdPnd:	0000000000000000
SigBlk:	0000000000000000
SigIgn:	0000000000000000
SigCgt:	0000000000000000
CapInh:	0000000000000000
CapPrm:	0000000000000000
CapEff:	0000000000000000
CapBnd:	000001ffffffffff
CapAmb:	0000000000000000
NoNewPrivs:	0
Seccomp:	0
Seccomp_filters:	0
Speculation_Store_Bypass:	thread vulnerable
SpeculationIndirectBranch:	conditional enabled
Cpus_allowed:	fffff
Cpus_allowed_list:	0-19
Mems_allowed:	00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000001
Mems_allowed_list:	0
voluntary_ctxt_switches:	1
nonvoluntary_ctxt_switches:	0


========================================================================================================
*/

