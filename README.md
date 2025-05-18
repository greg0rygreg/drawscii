# DRAWscii - blindpaint, refurbished
ueghuhuhri<s i remade blin dpait yeah

## what does DRAWscii have that differs from blindpaint?
DRAWscii has:
1. artwork viewing
	- unlike blindpaint, you can see what you're drawing and improve it
2. ~~absolute ZERO golang in sight on the source code~~ compiled code
	- hell yeah no more binary size measuring in megabytes!!!!!!!!!!!!!!!!!!!!

## where blindpaint go?
i think it's just been perfected (kinda) so it just... sits there (i forgot how to code in golang so no updates to it)

i encourage you to try and fork it to add what you want (i would like to see how adding italian brainrot to it would turn out)

## how do i make DRAWscii walk twice?
first, you need to compile it; to do so, make sure you have CLang/GNU Compiler Collection, make and git installed

if you don't have those installed, install them

after that, clone this repo (or download it) and compile the main.cpp file by using `make`:
```sh
git clone https://github.com/greg0rygreg/drawscii.git
cd drawscii
make # change clang++ to g++ in the Makefile if you installed the GNU Compiler Collection
./drawscii # add .exe if you're using windows
```

# KNOWN BUGS
- ~~unicode characters (like the logo for DRAWscii) and ANSI escape codes don't work correctly on windows~~

~~i don't know how to fix it but if i find out i will fix it ASAP (will also update libmenu because of `util::error`, `util::clear`, etc.)~~

fixed i think??? we need windows testers PLEASE
