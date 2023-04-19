@echo off

echo.
echo --------------------------------
echo primus-engine: starting build...
echo --------------------------------
echo.

cd ..
cmake .. -G"Unix Makefiles"
make

echo.
echo --------------------------------
echo primus-engine: build complete.
echo --------------------------------
echo.

primus-engine.exe

pause