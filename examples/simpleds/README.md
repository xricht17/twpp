TWPP Simple Source
==================
This is a simple TWAIN/TWPP data source that always returns the same image. It contains a minimal GUI consisting of Scan and Cancel buttons.

Contents
--------
- [Requirements](#requirements)
- [Usage](#usage)

Requirements
--------
- Qt 4 or newer (tested with Qt 5.11.1 MINGW 5.3.0 32bit)
- Windows (other OSes not tested)

Usage
------------
1. Compile using Qt and the supplied `.pro` file
   1. Or use Qt Creator
2. Copy the resulting `simpleds.ds` file to `\Windows\twain_32` directory
   1. Or, if using 64bit build and DSM, copy the file to `\Windows\twain_64` directory
3. Make sure all the necessary dependencies are available in the `PATH`
4. Test using any TWAIN app, e.g. IrfanView
