Set-Variable -Name "QtENV" -Value "D:\QtEnterprise\5.14.0\mingw73_64\bin\qtenv2.bat" 
Set-Variable -Name "BUILD_LOC" -Value "$PSScriptRoot/__CMAKE_BUILD"
Set-Variable -Name "CMAKE_CMD" -Value "cmake.exe  ../"
Set-Variable -Name "BUILD_CMD" -Value "cmake.exe --build ../ --target all"

New-Item -Force -Path "$BUILD_LOC" -ItemType Directory

Set-Location -Path $BUILD_LOC

Invoke-Expression $QtENV
Invoke-Expression $CMAKE_CMD
Invoke-Expression $BUILD_CMD

Set-Location -Path  "$PSScriptRoot"
