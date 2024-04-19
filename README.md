# CH552G Dev Board

## Description

A simple breakout board with minimal hardware design for the CH552G

## Build Example Code 

For those who want to use their own tools or try their hand at C programming the Game-Card X.

First, clone the repo, then make sure you clone all submodules: `git submodule update --init --recursive`

### Dependencies

- Linux:
   + Just use [nix](https://nixos.org/download/). Use `nix-shell` to get the following:
      - gnumake
      - hidapi
      - libusb1
      - libusb
      - python3
      - sdcc
      - virtualenv which will create .venv w/
         + pyusb
         + ch55xtool
- Windows:
   + Install [sdcc](https://sourceforge.net/projects/sdcc/files/latest/download?source=files)
   + Install [mingw](https://sourceforge.net/projects/mingw/files/latest/download)
   + Install [WCHISPTool](https://www.wch.cn/download/WCHISPTool_Setup_exe.html)
      - Only relevant for uploading, not building

### Build

On Linux, make sure you have the python virtualenv active and sdcc in your path (this happens every time you run `nix-shell`)

Run `make -C example-code` (or `mingw32-make -C example-code`), and it will build everything.

### Upload

__Linux:__

Assuming the game has been built, to upload:

1. Hold down a button on the board you want to upload to
2. Plug into USB and let go of the button
3. Within 2 seconds of letting go, run `make -C example-code upload`

If it fails, just try again a few times. If it's still not working, then repeat the process.

__Windows:__

Use WCHISP Studio

