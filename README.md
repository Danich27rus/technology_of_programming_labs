# Just labs that im making during subject with reports
My labs from NSTU second course subject "Techonolgies and methods of programming"
### What was used?
Visual Studio 2019 Community (C++ 17)
### How to run it?
You can use cmake/g++ compilers for it, but the easiest way will be using Visual Studio 2022 (MSVC 143, CMake C++ for Windows)

To compile it on Linux/Mac, in terminal type
```
g++ -o prog_1 program_1.cpp
```
If you dont have g++ on your PC, on Linux you can do this:
```
$ sudo apt update
$ sudo apt -y install build-essential
```
On Windows you must use MinGW instalator

Some description for labs:
There are reports in all labs in reprository and ```.sln``` file for Visual Studio


### Lab 1

In first lab we have dealt with two design patterns - SOLID and Singleton.
Theory for these patterns you can find here:
SOLID - https://techrocks.ru/2020/08/26/solid-principles-in-plain-russian/ and https://pro-prof.com/archives/1914#part_2
Singleton - https://en.wikipedia.org/wiki/Singleton_pattern

### Lab 2

In second lab we were creating data structure and learning one of algorithms, that were peresented in Techinical Task.

Lab provided with two folders - one is a data structure (linked list was for me) and second is algorithm (Edmonds' algorithm for me)

### Lab 3

We were using NSTU VDS as a platform for VPN, HTML site and simple application, which theme is described in Technical Task.
All configuration was made in terminal.

Third laboratory contains several files: html rip-off, client.ovpn for OpenVPN app and server daemon and .py script
All files were transferred on server using scp
```
scp -P port C:\destination_on_local_host server_user@ssh.cloud.nstu.ru:destination_on_server/
```

### Lab 4

...
