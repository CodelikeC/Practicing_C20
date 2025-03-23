```cpp
#include <iostream>
using namespace std;
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

static int orig_ngroups = -1; 
static gid_t orig_gid = -1; 
static uid_t orig_uid = -1;
static gid_t orig_groups[NGROUPS_MAX]; 

void spc_drop_privilages()
{
    gid_t newgid = getgid(), oldgid = getegid(); 
    uid_t newuid = getuid(), olduid = geteuid(); 
    if (!permanent)
    {
        orig_gid = oldgid; 
        orig_uid = olduid;
        orig_ngroups = getgroups(ngroups_maxm , orig_groups);

    }

    if (!olduid ) stegroups(1, &newgid); 
    if (newgid != oldgid)
    {
        if (newgid != oldgid) 
         {
 #if !defined(linux)
    setegid(newgid);
    if (permanent && setgid(newgid) == -1) abort();
#else
    if (setregid((permanent ? newgid : -1), newgid) == -1) abort();
#endif
        }
}
 if (newuid != olduid) {
 #if !defined(linux)
    seteuid(newuid);
    if (permanent && setuid(newuid) == -1) abort();
 #else
    if (setreuid((permanent ? newuid : -1), newuid) == -1) abort();
 #endif
  }
  /* verify that the changes were successful */
  if (permanent) {
    if (newgid != oldgid && (setegid(oldgid) != -1 || getegid() != newgid))
      abort( );
    if (newuid != olduid && (seteuid(olduid) != -1 || geteuid() != newuid))
      abort( );
}
 else {
    if (newgid != oldgid && getegid() != newgid) abort();
    if (newuid != olduid && geteuid() != newuid) abort();
  }
}

 void spc_restore_privileges(void) {
  if (geteuid() != orig_uid)
    if (seteuid(orig_uid) == -1 || geteuid() != orig_uid) abort();
  if (getegid() != orig_gid)
    if (setegid(orig_gid) == -1 || getegid() != orig_gid) abort();
  if (!orig_uid)
    setgroups(orig_ngroups, orig_groups);
 }