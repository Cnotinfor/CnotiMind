@echo off

set COPY_COMMAND=xcopy /D /Y

if "%1" == "release" goto RELEASE
if "%1" == "debug" goto DEBUG
if "%1" == "" goto HELP


:RELEASE
set UP_MODE=Release
set UP_DEST_FOLDER="..\bin\release"
set UP_CNOTIMIND="..\..\lib\CnotiMind.dll"

goto COPY


:DEBUG
set UP_MODE=Debug
set UP_DEST_FOLDER="..\bin\debug"
set UP_CNOTIMIND="..\..\lib\CnotiMind_d.dll"
set UP_QT_FLAG="d"

goto COPY


:COPY
echo %UP_MODE% Mode

echo Updating Cnoti Mind DLL
%COPY_COMMAND% %UP_CNOTIMIND% %UP_DEST_FOLDER%

echo Updating Qt dlls
%COPY_COMMAND% %QTDIR%\bin\QtCore%UP_QT_FLAG%4.dll %UP_DEST_FOLDER%
%COPY_COMMAND% %QTDIR%\bin\QtGui%UP_QT_FLAG%4.dll %UP_DEST_FOLDER%
%COPY_COMMAND% %QTDIR%\bin\QtXml%UP_QT_FLAG%4.dll %UP_DEST_FOLDER%

goto END


: HELP
echo To copy the libraries choose between debug and release
echo Must be called from the example source folder
echo
echo   update_libs debug,release



:END


set UP_CNOTIMIND=
set UP_DEST_FOLDER=
set UP_MODE=
set UP_QT_FLAG=
set COPY_COMMAND=