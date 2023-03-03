# Using VSCode for Arduino and ESP32

The "classic" Arduino IDE is severely limited when you start developing more complex code. I have been working with it for some time and found the following shortcomings especially severe:

* **IntelliSense**: There is no useful Intellisense for object members so you would need to know (or look up) the names of methods and theor overloads all the time.
* **Go To Definition**: There is no way to jump to the source code of a given member to take a peek into underlying classes to better understand code

## VSCode to the Rescue

*VSCode* is a free cross-platform generic editor from Microsoft that has excellent parsing capabilities and a great extension model. There are free extensions for just about any programming language you wish for.

In addition, these extensions often come with logic to actually run compilers, upload code, or open a serial monitor. Stand-alone, *VSCode* is just a (very capable) text editor. Combined with extensions, it turns into a full-fledged one-stop-serves-all *integrated development environment* (IDE). It can fully replace the classic Arduino IDE.

> This article will not discuss how you download and install *VSCode* or any of its extensions. There is a plethora of articles available on the Internet.

# Setting Up PlatformIO

One of the free extensions available for Arduino, ESP32 and a number of other embedded systems is **PlatformIO**. This article discusses the steps to set up this extension once you have installed it in *VSCode*.

Once the extension is installed in *VSCode*, you see a new icon in the symbol bar to the left. When you click on it, the main *PlatformIO Cockpit* page opens:

![Icon](media/platformio_setup_1.PNG | width=50)

## Creating New Project

To create a new *Project*, simply click on **New Project**. This opens up a new page. Here you can finally click on **New Project**:

![Icon](media/platformio_setup_2.PNG | width=50)

This opens a dialog.

### Choose Board Type

Enter the details about your project:

* **Name**: Any name for your project. This will name the folder your code is stored in.
* **Model**: Specify the board you are using. I am using a *Arduino Mega 2560* in this example. 
* **Framework**: The available frameworks depend on the software you have installed on your machine. If you have used *Arduino* before and downloaded the official *Arduino* Software, the list contains *Arduino Framework*. We'll later discuss how you can install and use other frameworks as well, for example if you want to program *ESP32* boards.
* **Location**: By default, all projects are stored in a dedicated folder *PlatformIo\Projects* inside your *Documents* folder. You can choose a different location as well if you like.

> Start choosing the correct *model* by clicking the drop-down icon at the right end of the *Model* text field. This lists all available models. By entering any text iinto the field, the list of models is automatically filtered for you. So by entering i.e. *2560* you immediately see the available models.

![Icon](media/platformio_setup_3.PNG | width=50)

