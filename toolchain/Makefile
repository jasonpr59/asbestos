# I set up my cross-compilation toolchain with the help of
# http://preshing.com/20141119/how-to-build-a-gcc-cross-compiler/.
# I tweaked the process then automated it with made this Makefile.
# This Makefile is not 100% hermetic.  Known dependencies:
#  * make
#  * gcc
#  * gawk (claimed by the website--I haven't confirmed)

GCCPREFIX := "i686-elf"
DEST=undefined-dest

# GZ archives.
src/mpfr.tar.gz:
	@mkdir -p src
	@curl -L "http://ftpmirror.gnu.org/mpfr/mpfr-3.1.5.tar.gz" > $@
src/binutils.tar.gz:
	@mkdir -p src
	@curl -L https://ftp.gnu.org/gnu/binutils/binutils-2.28.tar.gz  >$@
src/mpc.tar.gz:
	@mkdir -p src
	@curl -L http://ftpmirror.gnu.org/mpc/mpc-1.0.3.tar.gz >$@
src/gcc.tar.gz:
	@mkdir -p src
	@curl -L http://mirrors.concertpass.com/gcc/releases/gcc-6.3.0/gcc-6.3.0.tar.gz >$@

# XZ archives.
src/gmp.tar.xz:
	@mkdir -p src
	@curl -L http://ftpmirror.gnu.org/gmp/gmp-6.1.2.tar.xz >$@

# Unzip GZ.
src/binutils src/mpfr src/mpc src/gcc: %: %.tar.gz
	@mkdir -p $@
	@tar xf $< -C$@ --strip-components=1

# Unzip XZ.
src/gmp: %: %.tar.xz
	@mkdir -p $@
	@tar xf $< -C$@ --strip-components=1

# Link extra source code into GCC source dir.
src/gcc/%: src/% src/gcc
	@cd src/gcc && ln -s ../$* $*

# TODO(jasonpr): Print an error message instead of failing cryptically.
dest-exists:
	test -d $(DEST)

build/binutils/Makefile: dest-exists src/binutils
	@mkdir -p build/binutils
	@cd build/binutils && $(realpath src/binutils/configure) --prefix=$(realpath $(DEST)) --target=$(GCCPREFIX) --disable-multilib

# Run 'make; make install' for binutils.
install-binutils: dest-exists build/binutils/Makefile 
	@cd build/binutils && make -j4
	@cd build/binutils && make -j4 install


# Also enable c++?
build/gcc/Makefile: dest-exists src/gcc/mpfr src/gcc/mpc src/gcc/gmp
	@mkdir -p build/gcc
	@cd build/gcc && $(realpath src/gcc/configure) --prefix=$(realpath $(DEST)) --target=$(GCCPREFIX) --disable-multilib --enable-languages=c

install-gcc: dest-exists build/gcc/Makefile 
	@cd build/gcc && make -j4 all-gcc
	@cd build/gcc && make -j4 install-gcc

install-libgcc: dest-exists build/gcc/Makefile
	@cd build/gcc && make -j4 all-target-libgcc
	@cd build/gcc && make -j4 install-target-libgcc

clean:
	@rm -rf build src
