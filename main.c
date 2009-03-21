// Made by kraiser a.k.a. krisje8

#include <stdio.h>
#include <windows.h>
#include <winbase.h>
#include <process.h>

 int xsystem(char *cmd, char *path, int wait)
 {
   	PROCESS_INFORMATION pi;
	STARTUPINFO si;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_FORCEOFFFEEDBACK;
	si.wShowWindow = SW_HIDE;

	if (CreateProcess(0, cmd, 0, 0, TRUE, 0, 0, path, &si, &pi) == 0)
		return 1;	/* FAILED */

	if (wait) {
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
	return 0;		/* SUCCESS */
 }


int main(){
    //Let's get the logial drives first
    char drivebuf[1024];
    char path[1024];
    char pathfile[1024];
    int found = 0;
    GetLogicalDriveStrings(1024, drivebuf);
    char *pch = drivebuf;
    
    //Iterate through them to see which one has our go.cmd
    while (*pch) {
          sprintf(path, "%sWIP\\CMD\\", pch);
          sprintf(pathfile, "%sgo.cmd", path);
          if(access(pathfile, "F_OK") == 0){
               found = 1;
               break;
          }
          pch = &pch[strlen(pch) + 1];
    }
    
    if(found == 1){
             //Ok we found the drive letter of our U3 drive
             xsystem(pathfile, path, 0);
    }
    
    return 0;
}
