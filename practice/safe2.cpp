#include <iostream> 
using namespace std; 
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <windows.h> 

BOOL RemoveBackuAndStorePrivilages(VOID)
{
    BOOL bresult; 
    HANDLE hProcess, hProcessToken; 
    PTOKEN_PRIVILEGES pNewState; 

    // alocate a token privilages buffer to hold the privilage
    // change information.. 
    // luid and  attributes elements in the privilage field of Token privilages.. 
    pNewState = (PTOKEN_PRIVILEGES)LocalAlloc(LMEM_FIXED, sizeof(TOKEN_PRIVILEGES) + (sizeof(LUID_AND_ATTRIBUTES) *2));

    if (!pNewState)
    return FALSE;  

    // add the two privilages that will be removed to the allocated buffer..//
    pNewState -> PrivilegeCount = 2 ; 
    if (!LookupPrivilegeValue(NULL, SE_BACKUP_NAME, &pNewState -> Privileges[0].Luid))
    {
        LocalFree(pNewState); 
        return FALSE; 
    }
    pNewState -> Privileges[0].Attributes = SE_PRIVILEGE_REMOVED; 
    pNewState -> Privileges[1].Attributes = SE_PRIVILEGE_REMOVED; 

    // get handle to the process primary token..// 
    // access so that we can adjust the privilages..// 
    // Token query access would be required in order to retrieve the previous.. 
    hProcess = GetCurrentProcess();
    if (!OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hProcessToken))
    {
        LocalFree(pNewState); 
        return FALSE; 
    }

    // adjust the privilages, specifying False for disable all privilages... so that
    // the new state argument will be used instead, do not request information regarding.. 
    // the token previous state by specifying null for the last three arguementss.. /

    bresult = AdjustTokenPrivileges(hProcessToken, FALSE, pNewState, 0, 0 ,0 ); 

    // clean up and return the success or failure of the adjustment,.. // 
    CloseHandle(hProcessToken) ; 
    LocalFree(pNewState); 
    return bresult; 
}

// working with PSID spclookup sidby name..
PSID SpcLookupSidByName(LPCSTR lpAccountName, PSID_NAME_USE peUse)
{
    PSID psid = 0; 
    DWORD cbsid, cchReferenceDomainName; 
    SID_NAME_USE eUse;
    LPSTR lpReferenceDomainName;

    cbsid = cchReferenceDomainName= 0; 
    if (!LookupAccountName(LMEM_FIXED, lpAccountName, psid, &cbsid, lpReferenceDomainName, &cchReferenceDomainName, &eUse))
    {
        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
            psid = (PSID)LocalAlloc(LMEM_FIXED, cbsid); 
            lpReferenceDomainName = (LPSTR)LocalAlloc(LMEM_FIXED, cchReferenceDomainName); 
            if (!psid || !lpReferenceDomainName)
            {
                if (psid)
                LocalFree(psid); 
                if (lpReferenceDomainName)
                LocalFree(lpReferenceDomainName); 
                return 0; 
            }
            if (!LookupAccountName(NULL, lpAccountName, psid, &cbsid, lpReferenceDomainName, &cchReferenceDomainName, &eUse))
            {
                LocalFree(psid); 
                LocalFree(lpReferenceDomainName); 
                return 0; 
            }
        }
        else 
        {
            return 0; 
        }
    }
}

// int main()
// {
//     // remove the backup and restore privilages.. // 
//     if (!RemoveBackuAndStorePrivilages())
//     {
//         cerr << "Failed to remove backup and restore privilages." << endl; 
//         return 1; 
//     }
//     return 0; 
// }

int main()
{
    // Kiểm tra quyền trước khi loại bỏ
    cout << "Removing backup and restore privileges..." << endl;

    if (!RemoveBackuAndStorePrivilages())
    {
        cerr << "Failed to remove backup and restore privileges." << endl;
        return 1;
    }

    cout << "Successfully removed backup and restore privileges." << endl;

    // Kiểm tra SID của một tài khoản (ví dụ: "Administrator")
    PSID_NAME_USE peUse;
    PSID psid = SpcLookupSidByName("Administrator", peUse);
    if (psid)
    {
        cout << "Successfully retrieved SID for 'Administrator'." << endl;
        LocalFree(psid); // Giải phóng bộ nhớ
    }
    else
    {
        cerr << "Failed to retrieve SID for 'Administrator'." << endl;
    }

    return 0;
}