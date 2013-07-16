1. Download mingw
-http://sourceforge.net/projects/mingwbuilds/files/host-windows/releases/4.8.1/64-bit/threads-posix/
-Seh works well
-Unzip it somewhere fitting, for example c:/
-Add the bin folder of the unzipped directory to the system PATH variable

2. Download Cmake
-http://www.cmake.org/
-Install using installer.
-Add cmake bin folder to system PATH

3. Restart computer
-Do it!

4. Download mingw binary packages
-http://sourceforge.net/projects/mingwbuilds/files/external-binary-packages/
-Grab the newest bundle.
-Unzip it into the mingw folder extracted in previous step.

5. Download glew source
-http://glew.sourceforge.net/
-Unzip it somewhere fitting

6. Build glew
-Start the msys.bat file existing in the folder unzipped in step 2 to get a terminal.
-Use cd to navigate the unzipped glew folder.
-Type mingw32-make to build glew.

7. Download latest SFML
-git clone https://github.com/LaurentGomila/SFML.git

8. Build SFML
-Navigate to the cloned repository using the msys terminal as in step 6.
-Type cmake . to generate makefiles.
-Type mingw32-make to compile sfml.
-Type mingw32-make install to install it.

9. Download the framework
-Download snapshot at http://pallkars.net/gitweb/?p=windlab_engine.git;a=summary
-Extract somewhere nice.

10. Build the framework
-Use the CMake GUI in the extracted folder to select which components to build as well as if debug should be built.
-Navigate to the cloned repository using the msys terminal as in step 6 and 7.
-Type mingw32-make to build.

Framework is now ready for use!

Use the following steps to setup the test project for Code::Blocks:

1. Download and install Code::Blocks
-codeblocks-12.11-setup.exe from the page http://www.codeblocks.org/downloads/26 is good enough
-install

It will complain that it does not have any compiler configured. This is okay, we will configure it to use the one installed with mingw from the previous step.

2. Get the test project
- Grab the latest snapshot from http://pallkars.net/gitweb/?p=framework_test.git;a=summary
- Extract somewhere

3. Use CMake to generate Code::Blocks project files
- Use the CMake GUI to select the extracted folder.
- Change the FRAMEWORK_PATH variable to point to the directory of the framework repository.
- Configure and generate.

4. Start and configure Code::Blocks
- Open the generated project file in Code::Blocks
- Go to Settings -> Compiler
- Where the compiler binaries are set, change the folder to the binary folder of the mingw folder from before, and change the names of all binaries to match the ones in that folder.
- Save the settings

5. Build
- This should succeed by now if everything else was setup correctly.

6. Copy needed dlls
- For the executables to run correctly, DLL files have to be copied to the folder containing the executables. Do this. Find out the needed ones by starting the exe.
