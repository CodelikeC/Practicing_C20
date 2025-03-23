#include <iostream> 
using namespace std; 
#include <lmcons.h> 
#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <windows.h> 

int main (int argc, char*argv[])
{
    char username[UNLEN + 1]; 
    DWORD username_len = UNLEN + 1; 
    GetUserName(username, &username_len); 
    cout << "Hello" << username << endl;
    if (GetUserName(username, &username_len))
    {
        cout <<"Current user:" << username << endl ; 
    }
    else 
    {
        cerr <<"Failed to get username." << endl; 
    }
    return 0;  
}


