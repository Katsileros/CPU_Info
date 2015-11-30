# CPU_INFO Project

Detects the Operating System(Linux/Windows) and the Brand-Family-Architecture of the CPU

## Building
Clone the project, and make the build directory
For this project there are no external libraries required.
	
-Linux

Move into build directory

```sh
cmake ..
make
```

-Windows

Move into build directory

```sh
cmake -G "NMake Makefiles" ..
qmake/nmake
```

## Running

-Linux

```sh
chmod +x cpuinfo.sh
./cpuinfo.sh
```

-Windows

```sh
cpuinfo.bat
```
