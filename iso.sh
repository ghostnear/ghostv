#!/bin/sh
set -e
. ./clean.sh
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/ghostv.kernel isodir/boot/ghostv.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "GhostV" {
	multiboot /boot/ghostv.kernel
}
EOF
grub-mkrescue -o ghostv.iso isodir
