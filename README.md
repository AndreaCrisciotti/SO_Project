# SO_Project
The Project implement a process monitor that allows to:
   - terminate
   - kill
   - suspend
   - resume
   
the running processes.

>The processes are accessed via the /proc filesystem.
>The program monitors the resources used by each process (CPU usage/ Memory usage)

# Graphics interface

![Schermata del 2022-09-28 18-37-57](https://user-images.githubusercontent.com/38427839/192834529-bae28c21-1f39-4e2b-8b71-b900ea47699e.png)

![](https://img.shields.io/github/issues/AndreaCrisciotti/SO_Project?label=TOP%20usage)
![](https://img.shields.io/github/stars/AndreaCrisciotti/SO_Project?label=VS%20Code&logo=visual-studio-code)
![](https://img.shields.io/github/license/AndreaCrisciotti/SO_Project?color=blue&label=License&logo=MIT)

------------

# How to use

#### Running program
First of all compile the program with:

>`$ make`

If you want "CLEAR" the .exe program use:

>`$ make clear`

For execute use this:

>`$ sudo ./topOS`

#### Usage

Opening the program you can decide to:
- Terminate process(1)
- Kill process (2)
- Suspend process (3)
- Resume process (4)
- View information of your PC (5)
- Refresh process (6)
- Exit and terminate the session (7)

