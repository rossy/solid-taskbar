**solid-taskbar** removes transparency from the Windows 8 taskbar.

![Screenshot](https://rossy.github.io/solid-taskbar/screenshot.png)

Installation
------------

Download an .exe from [the releases page][1], put it in your startup folder
(Start Menu\Programs\Startup) and run it. The program will hang around in the
background to remove transparency again if Windows recreates the taskbar, which
can happen from time to time.

To uninstall, move the .exe out of the startup folder, logout and log back in.

[1]: https://github.com/rossy/solid-taskbar/releases

Known issues
------------

Not tested (probably doesn't work) on multiple-monitor systems with multiple
taskbars.

Building
--------

The program requires mingw-w64 GCC and GNU Make. The easiest way to get them is
through the [MSYS2][2] project. To build, just run ``make``.

[2]: https://msys2.github.io/

Copying
-------

To the extent possible under law, the author(s) have dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

[![CC0](http://i.creativecommons.org/p/zero/1.0/80x15.png)](http://creativecommons.org/publicdomain/zero/1.0/)
