{ pkgs ? import <nixpkgs> { } }:

let
    unstable = import
        (fetchTarball "https://nixos.org/channels/nixos-unstable/nixexprs.tar.xz") {};
    buildLibs = with pkgs; (with xorg; [
        hidapi
        libusb1
    ]);
in with pkgs; mkShell {
    buildInputs = [
        gnumake
        libusb
        python3
        sdcc
        virtualenv
    ] ++ buildLibs;
    shellHook = ''
        export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${lib.makeLibraryPath buildLibs}"
        export XDG_DATA_DIRS="${gsettings-desktop-schemas}/share/gsettings-schemas/${gsettings-desktop-schemas.name}:${gtk3}/share/gsettings-schemas/${gtk3.name}"
        virtualenv .venv
        source .venv/bin/activate
        python3 -m pip install ch55xtool
        python3 -m pip install pyusb
    '';
}

