@echo off

echo.
echo ---------------------------------------
echo primus-engine: cleaning build directory
echo ---------------------------------------
echo.

cd ..

echo cleaning junk build directories...

for /d %%a in (*.*) do (
    if /i not "%%~nxa"=="scripts" (
        echo -- deleting dir '%%a'
        rd /s /q "%%a"
    )
)

echo.
echo cleaning junk build files...

for %%a in (*.*) do (
    echo -- deleting dir '%%a'
    del "%%a"
)

echo.
echo ---------------------------------------
echo primus-engine: finished. all clean!
echo ---------------------------------------
echo.

pause