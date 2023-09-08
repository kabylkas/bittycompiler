set SCRIPT_DIR=%~dp0
set OUTPUT_FOLDER=%SCRIPT_DIR%windows\%VS_FOLDER%
if not exist %OUTPUT_FOLDER% (
    mkdir %OUTPUT_FOLDER%
)

set VS_VER="Visual Studio 17 2022"

cd %OUTPUT_FOLDER%
cmake -G %VS_VER% ..\.. 
