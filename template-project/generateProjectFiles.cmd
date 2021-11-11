
:: Set project variables here
set PROJECT_NAME=""
set ENGINE_PATH=""

:: Creates the project
call scripts\premake5\premake5 vs2019 --projectname=%PROJECT_NAME% --enginepath=%ENGINE_PATH%

:: Unsets project variables
set PROJECT_NAME=""
set ENGINE_PATH=""
PAUSE