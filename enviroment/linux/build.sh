#/bin/bash
echo "Start Build Script"

KERNEL=kernel7

echo "Build Kernel"
make -j4 zImage modules dtbs

echo "Finished Build Script"
