#!/bin/bash
set -e

# Parse command line arguments
ARCH=""
while [[ $# -gt 0 ]]; do
    case "$1" in
        --arch)
            ARCH="$2"
            shift 2
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

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
        if [ "$ARCH" == "x86" ]; then
            sudo dpkg --add-architecture i386
            sudo apt update
            sudo apt install -y gcc-multilib g++-multilib \
                libx11-dev:i386 libxkbcommon-dev:i386 libwayland-dev:i386 libgl1-mesa-dev:i386 \
                libwayland-client0:i386 libwayland-cursor0:i386 libwayland-egl1:i386 libxkbcommon0:i386
        else
            sudo apt install -y libwayland-dev libxkbcommon-dev xorg-dev libgl1-mesa-dev
        fi
        ;;
    fedora|rhel|centos)
        sudo dnf update -y
        if [ "$ARCH" == "x86" ]; then
            sudo dnf install -y glibc-devel.i686 libX11-devel.i686 mesa-libGL-devel.i686 \
                libxkbcommon-devel.i686 wayland-devel.i686
        else
            sudo dnf install -y wayland-devel libxkbcommon-devel \
                libXcursor-devel libXi-devel libXinerama-devel libXrandr-devel \
                mesa-libGL-devel
        fi
        ;;
    freebsd)
        echo "WARNING: Theres no current implementation for cross-toolchain installation on FreeBSD, making --arch obsolete"
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