# Using VSCode for Arduino and ESP32

The "classic" Arduino IDE is severely limited when you start developing more complex code. I have been working with it for some time and found the following shortcomings especially severe:

* **IntelliSense**: There is no useful Intellisense for object members so you would need to know (or look up) the names of methods and theor overloads all the time.
* **Go To Definition**: There is no way to jump to the source code of a given member to take a peek into underlying classes to better understand code

## VSCode to the Rescue

*VSCode* is a free cross-platform generic editor from Microsoft that has excellent parsing capabilities and a great extension model. There are free extensions for just about any programming language you wish for.

In addition, these extensions often come with logic to actually run compilers, upload code, or open a serial monitor. Stand-alone, *VSCode* is just a (very capable) text editor. Combined with extensions, it turns into a full-fledged one-stop-serves-all *integrated development environment* (IDE). It can fully replace the classic Arduino IDE.

> This article will not discuss how you download and install *VSCode* or any of its extensions. There is a plethora of articles available on the Internet.
