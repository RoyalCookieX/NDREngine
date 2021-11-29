
:: Set project variables here
set PROJECT_NAME=
set ENGINE_PATH=

set COMPILER=vs2019
set MODULES_PATH=%ENGINE_PATH%;%ENGINE_PATH%\scripts\premake5\modules

:: Creates the project
call Scripts\Premake5\premake5 %COMPILER% --projectname="%PROJECT_NAME%" --enginepath="%ENGINE_PATH%" --scripts="%MODULES_PATH%"

PAUSE