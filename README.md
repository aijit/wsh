# Windows baSH, WSH


__[WSH](https://github.com/wordworld/wsh)__
is pointed to be a
[**W**indows](https://gnuwin32.sourceforge.net/)
porting version of the
[gnu/ba**SH**(Bourne Again SHell)](https://github.com/gitGNU/gnu_bash).
It is a developing interactive shell,
as well as a interpreter for bash scripts.

This project is initially based on the
__[win-bash_0.8.5](https://sourceforge.net/projects/win-bash/)__
( last updated on 2011-03-17 )
developed by [Jutta Albrecht](https://sourceforge.net/u/bithexe/profile/)
| [Christian V. J. Bruessow](https://sourceforge.net/u/cvjb/profile/)
| [Joerg Matysiak](https://sourceforge.net/u/matysiak/profile/)
| [Mathias Faas](https://sourceforge.net/u/mfaascenit/profile/).

### 编译依赖

* 依赖工具

    [w64devkit v1.19.0](https://github.com/skeeto/w64devkit/releases/tag/v1.19.0)
    | [CMake v3.25.0](https://github.com/Kitware/CMake/releases/tag/v3.25.0)
    
    GCC 从 2.95.3 开始 no longer implements <varargs.h>

* 编译命令

    `$ cmake -G Ninja -S . -B $BUILD_DIR`

    `$ cmake --build $BUILD_DIR --target bash`

### 更新记录

* 2023-05-17:
[bash-4.4](https://github.com/gitGNU/gnu_bash/releases/tag/bash-4.4)
