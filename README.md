         _____            ___  ____    ____            _           _   
        |_   _|__  _ __  / _ \/ ___|  |  _ \ _ __ ___ (_) ___  ___| |_ 
          | |/ _ \| '_ \| | | \___ \  | |_) | '__/ _ \| |/ _ \/ __| __|
          | | (_) | |_) | |_| |___) | |  __/| | | (_) | |  __/ (__| |_ 
          |_|\___/| .__/ \___/|____/  |_|   |_|  \___// |\___|\___|\__|
                  |_|                               |__/               
                            

# SO_Project --> TOPOS
The Project implement a process monitor that allows to:
   - terminate
   - kill
   - suspend
   - resume
   
the running processes.

>The processes are accessed via the /proc filesystem.
>The program monitors the resources used by each process (CPU usage/ Memory usage)

<b>
<p align="center">
Project created for Course of Operating System at University La Sapienza of Rome - Computer Engineering, requested by Prof. Giorgio Grisetti at year (2021/2022).
</p>
</b>

------------

# Graphics interface

![Schermata del 2022-09-28 18-37-57](https://user-images.githubusercontent.com/38427839/192834529-bae28c21-1f39-4e2b-8b71-b900ea47699e.png)

![](https://img.shields.io/github/issues/AndreaCrisciotti/SO_Project?label=TOP%20usage)
![](https://img.shields.io/github/stars/AndreaCrisciotti/SO_Project?label=VS%20Code&logo=visual-studio-code)
![](https://img.shields.io/github/license/AndreaCrisciotti/SO_Project?color=blue&label=License&logo=MIT)

------------

# How to use

#### Running program
First of all compile the program with:

        $ make

If you want "CLEAR" the .exe program use:

        $ make clear

For execute use this:

        $ sudo ./topOS

------------

#### Usage

Opening the program you can decide to:

- Terminate process(press 1)
- Kill process (press 2)
- Suspend process (press 3)
- Resume process (press 4)
- View information of your PC (press 5)
- Refresh the view of process (press 6)
   - Yes, i used this procedure because TOP command is too fast and sometimes I didn't see the process that interests me
- Exit and terminate the session (press 7)


# Valgrind TEST
![Schermata del 2022-10-10 17-00-09](https://user-images.githubusercontent.com/38427839/194894058-fa9c8b2e-7e0b-4b39-8647-4add5c47d1dd.png)


# Powerd By

Copyright © 2021-2022 Andrea Crisciotti
Student of Computer Engineering - University La Sapienza of Rome
