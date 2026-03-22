@echo off
echo Cleaning build artifacts...
if exist "OVMATH" (
    rmdir /s /q "OVMATH"
    echo Build artifacts cleaned successfully.
) else (
    echo Build artifacts directory does not exist.
)
pause
