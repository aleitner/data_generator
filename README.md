Generate data based on string

build on osx
OSX `gcc src/generate_data.c -o bin/generate_data_darwin`

Windows
32 bit
`/usr/local/gcc-4.8.0-qt-4.8.4-for-mingw32/win32-gcc/bin/i586-mingw32-gcc src/generate_data.c -o bin/generate_data_win32.exe`

Linux
32 bit
`/usr/local/gcc-4.8.1-for-linux32/bin/i586-pc-linux-gcc --static src/generate_data.c -o bin/generate_data_linux32`

64 bit
`/usr/local/gcc-4.8.1-for-linux64/bin/x86_64-pc-linux-gcc --static src/generate_data.c -o bin/generate_data_linux64`

run
`bin/generate_data <-s size> [-t text]`

example for writing to file
`./bin/generate -s 715112054784 -t "It's in that place where I put that thing that time. " > /Volumes/2tbjunk/666gb`

example for writing to stdout
`./bin/generate -s 715112054784 -t "It's in that place where I put that thing that time. " 2> /dev/null
