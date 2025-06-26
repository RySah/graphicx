#!/bin/bash

# Detect distribution
if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$ID
elif type lsb_release >/dev/null 2>&1; then
    OS=$(lsb_release -si | tr '[:upper:]' '[:lower:]')
else
    OS=$(uname -s | tr '[:upper:]' '[:lower:]')
fi

# Install dependencies
case $OS in
    debian|ubuntu|linuxmint)
        sudo apt update
        sudo apt install -y libwayland-dev libxkbcommon-dev xorg-dev libgl1-mesa-dev
        ;;
    fedora|rhel|centos)
        sudo dnf install -y wayland-devel libxkbcommon-devel \
            libXcursor-devel libXi-devel libXinerama-devel libXrandr-devel \
            mesa-libGL-devel
        ;;
    freebsd)
        sudo pkg install -y wayland libxkbcommon evdev-proto xorgproto mesa-libs
        ;;
    *)
        echo "Unsupported OS: $OS"
        echo "Please install these packages manually:"
        echo "- OpenGL development packages (libgl1-mesa-dev/mesa-libGL-devel)"
        echo "- wayland development packages"
        echo "- xkbcommon"
        echo "- X11 development packages (libXcursor, libXi, libXinerama, libXrandr)"
        exit 1
        ;;
esac

echo "All dependencies (OpenGL, Wayland, X11) installed successfully"