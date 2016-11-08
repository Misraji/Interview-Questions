# BOOKS
Repository containing solutions to real life interview problems from various companies.
If the programming challenge contained a sample input, that would be stored in the corresponding inputs/ directory.

# BUILD
The default Makefile target builds all programs in src directory. All binaries
are created in the build directory. To build one specific file, the makefile
target should be the path of the file without the file-suffix. For eg:
```
# If using a directory for the first time, do setup.
make setup
make src/company1/prog1
./build/src/company1/prog1 < inputs/company1/prog1.txt
```
