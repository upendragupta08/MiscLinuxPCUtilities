# MiscLinuxPCUtilities

Below works for GNOME based OS. i.e. Mint, Ubuntu

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
fs_monitor.c
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Compile and run fs_monitor.c
It consists of below functionality:
1> Free Hard disk.
2> Free RAM
3> System Uptime 
4> Free CPU %

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
mem_monitor.sh
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Given script will monitor RAM usage of given application.
Mentioned by "APP_NAME_STR" and if it exeeds MAX_MEM_USAGE then 
it will kill application with SIGKILL signal.
