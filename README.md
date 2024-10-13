# DRAWscii - blindpaint, refurbished.
DRAWscii is like blindpaint 2, blindpaint but, in my opinion, better.

its objective of blindly painting is gone, sad, i know. but atleast you get to know what you're doing!!

## what does it have, however?
DRAWscii will have:
1. artwork viewing
	- unlike blindpaint, you can see what you're drawing and improve it
2. cross-platform support
	- just like blindpaint, except you need to compile it yourself
3. DLL/shared library file (not done)
	- again, like blindpaint, but you need to compile it yourself
4. compiled code
	- hell yeah no more binary size measuring in megabytes!!!!!!!!!!!!!!!!!!!!

## why did you kill blindpaint?
i didn't mean to kill it but i think it's just been perfected (it's not.)

if you want it to come back try forking it and adding what you want (no brainrot please for the love of god)

## how do i run it?
you need to first compile it, to do so, make sure you have mingw installed

but BEFORE that, you need git, which is included with mingw iirc

if you don't have it installed, install it, you'll need it

after that, clone the repo and compile the main file:
```sh
git clone https://github.com/greg0rygreg/drawscii.git drawscii
cd drawscii
g++ -o drawscii main.cpp # add .exe after drawscii if you're a windows user
```