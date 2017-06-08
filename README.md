asbestos
========

A toy OS, from scratch.

Goals and Non-Goals
-------------------

I have the following goal for this project.

  * Make an OS, "from scratch."  We'll see what "from scratch" ends up
    meaning!  (In 6.828, we implemented many parts of an OS, but it
    was not from scratch.)

The following are not goals for this project:

  * Design a "good" OS.  I intend to run this unstructured OS into the
    ground, first.  Only then might I consider "doing it right" and
    designing an OS.

  * Use other people's libraries wisely..  Making an OS from scratch
    is probably not a good idea.  I would make progress a lot faster
    if I used other people's libraries.  But, the from-scratch aspect
    is very important to me, so I'm declaring those libs to be
    off-limits.


Getting Asbestos
----------------
```bash
git clone https://github.com/jasonpr59/asbestos.git
# The rest of the README assumes that you are in the asbestos repository.
cd asbestos
```

Building Asbestos
-----------------

### Building the Toolchain

To build Asbestos, you'll need a cross-compilation toolchain targetting
'i686-elf'.  By default, the Asbestos Makefile expects the toolchain to be
installed in the `cross` directory (inside the top-level Asbestos directory).
From within the Asbestos repo, install it with:
```bash
mkdir cross
cd toolchain
make install-binutils install-gcc install-libgcc DEST=../cross

# Finally, discard the downloaded source and intermediate build artificats.
# This does not touch installed artifacts.
make clean

# Return to top-level Asbestos directory for future steps.
cd ..
```

### Building the kernel disk image

All of the Asbestos source combines to build `asbestos.bin`.  This is a
Multiboot-compatible disk image. Build it with:
```bash
make kernel
```

Running Asbestos
----------------

### Running Asbestos in an emulator

I run Asbestos on QEMU.  (On OS X, I installed QEMU with `brew install qemu`.)

Run QEMU using the `asbestos.bin` disk image with:
```bash
make qemu
```

### Running Asbestos on real hardward

I've never tried this.  Stay tuned for instructions.

Debugging Asbestos
------------------

Use GDB to debug Asbestos.  `asbestos.bin` has file format elf32-i386.  Your GDB might not understand that format.  To install a "cross-GDB", do the following.
```bash
mkdir $ASBESTOS/toolchain/src
cd $ASBESTOS/toolchain/src
curl https://ftp.gnu.org/gnu/gdb/gdb-8.0.tar.xz > gdb.tar.xz
tar xf gdb.tar.xz -Cgdb --strip-components=1

mkdir $ASBESTOS/toolchain/build
cd $ASBESTOS/toolchain/build
$ASBESTOS/toolchain/src/gdb/configure --target=i686-elf --prefix=$ASBESTOS/cross
make
make install
```

After following the instructions above, you will have installed a "cross-GDB" in
$ASBESTOS/cross/bin/i686-elf-gdb.  Run QEMU with a GDB debug server with `make
qemu-gdb`.  Connect to it (from a separate shell) with `make gdb` (which uses
the `.gdbinit` file in the root Asbestos directory to connect to the server and
read the symbol file).