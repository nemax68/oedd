# OPEN-EYES LCD PC simulator

This simulator is derived from [Littlev Graphic Library](https://github.com/littlevgl/lvgl) and is used to develop custom LCD interface over [OPEN-EYES platform](https://open-eyes.it) 

## Requirements
* The PC simulator is cross platform so **Windows, Linux and OSX** is supported
* **SDL** a low level driver library to use graphics, handle mouse, keyboard etc.
* This project (configured for **Eclipse CDT IDE**)

## Usage

### Get the PC project

Clone the PC project and the related sub modules:
```
git clone --recursive https://github.com/nemax68/lvgl_simulator.git
```

### Install SDL
You can download SDL from https://www.libsdl.org/

On Linux you can install it via terminal:
```
sudo apt-get update && sudo apt-get install -y build-essential libsdl2-dev
```

### Install Eclipse CDT
Download and install Eclipse CDT from  http://www.eclipse.org/cdt/

### Import the PC simulator project
1. Open Eclipse CDT
2. Click **File->Import** and choose **General->Existing project into Workspace**
3. Browse the root directory of the project and click Finish
4. Build your project and run it

If you find an issue, please report it via GitHub!

## SYSTEMCTL

systemctl daemon-reload
systemctl start oedd
systemctl status oedd

## PACKAGE CREATION
--------------------------------------

#The first time only to build directory infrastructure
dh_make --native --single --packagename oedd_0.0.1 --email pinco.pallino@gmail.com

#Every time new version is generated
dpkg-buildpackage -us -uc --host-arch armhf

## LICENCE 

This project is licensed under the terms of the GNU GENERAL PUBLIC LICENSE Version 3


