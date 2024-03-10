# WinSOS

This technique utilizes executables within the WinSxS folder, commonly trusted by Windows, to exploit the classic DLL Search Order Hijacking method. By leveraging these executables, threat actors can execute malicious code within Windows applications without requiring elevated privileges. 
This approach eliminates the need for additional binaries in the attack chain and enables the execution of malicious code from any location. It is compatible with both Windows 10 and 11 and can evade detection by defense software and responders, as the malicious code runs within the memory space of a trusted binary. This technique simplifies the classic DLL Search Order Hijacking and exploits native Windows functionalities without directly exploiting an OS issue.


## References

 - [Hide and Seek in Windows' Closet: Unmasking the WinSxS Hijacking Hideout](https://www.securityjoes.com/post/hide-and-seek-in-windows-closet-unmasking-the-winsxs-hijacking-hideout)


