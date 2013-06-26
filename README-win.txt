1. Download mingw
-http://sourceforge.net/projects/mingwbuilds/files/host--windows/releases/4.8.1/64-bit/threads-posix/
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