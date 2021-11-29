set COMPILER=vs2019
set MODULES_PATH=scripts\premake5\modules

call scripts\premake5\premake5 %COMPILER% --scripts="%MODULES_PATH%"

pause