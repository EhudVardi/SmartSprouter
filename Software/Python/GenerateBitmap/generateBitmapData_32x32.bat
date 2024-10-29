@echo off

REM Define resolution variables
set WIDTH=32
set HEIGHT=32

REM Check if an image file is passed as an argument
if "%~1"=="" (
    echo No image file provided. Please drag and drop an image onto this batch file.
    timeout /t 5
    exit /b
)

REM Display the path and name of the dragged file
echo File passed: %~1

REM Display the current resolution being used
echo Generating bitmap with resolution %WIDTH%x%HEIGHT%...

REM Specify the full path to your Python script using the batch script's directory
set SCRIPT_PATH=%~dp0GenerateBitmapFromMonochromeImage.py

REM Run the Python script with the specified width and height
python "%SCRIPT_PATH%" "%~1" %WIDTH% %HEIGHT%

REM Wait for 5 seconds before closing the console window
timeout /t 5
