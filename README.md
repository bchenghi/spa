# Team 32

## Target Environment

Item | Version
-|-
OS | macOS
Toolchain | CMake
C++ Standard | C++17

### Additional Build Instructions
1. Ensure you have cmake version of at least 3.20.5

2. Navigate to Team32 directory
```
$ cd Team32
```

3. Create build directory to contain build files and cd into the new directory
```
$ mkdir build
$ cd build
```

4. Build the project via the following commands using cmake
```
$ cmake -DCMake_BUILD_TYPE=Release ../Code32/
$ cmake --build . --target autotester
```

5. The path to the executable is at `./build/src/autotester/autotester`, from the Team32 directory

# Team Members

Name | Mobile | Email | Development OS/Toolchain
-:|:-:|:-|-|
Lin Geyu | 84810795 | e0376918@u.nus.edu | macOS/CMake
Lin Zhengyang | 80327705 | e0376919@u.nus.edu | Windows 10/CMake
Joshua Liang XingYa | 91465067 | e0406742@u.nus.edu | Windows 10/CMake
So Wai Yein Ethan | 96463658 | e0407515@u.nus.edu | macOS/CMake
Boh Cheng Hin | 96509522 | e0406145@u.nus.edu | Windows 10/CMake
Nguyen Dinh Quang Minh | 86473897 | e0313667@u.nus.edu | Windows 10/CMake

