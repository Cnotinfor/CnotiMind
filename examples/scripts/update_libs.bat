@echo off

set COPY_COMMAND=xcopy /D /Y

if "%1" == "release" goto RELEASE
if "%1" == "debug" goto DEBUG
if "%1" == "" goto HELP


:RELEASE
set UP_MODE=Release
set UP_DEST_FOLDER="..\bin\release"
set UP_CNOTIMIND_FILE="..\..\lib\CnotiMind.dll"

goto COPY


:DEBUG
set UP_MODE=Debug
set UP_DEST_FOLDER="..\bin\debug"
set UP_CNOTIMIND_FILE="..\..\lib\CnotiMind_d.dll"

goto COPY


:COPY
echo %UP_MODE% Mode

echo Updating Cnoti ;ind DLL
%COPY_COMMAND% %UP_CNOTIMIND_FILE% %UP_DEST_FOLDER%


echo Updating Qt dlls
::%COPY_COMMAND% %QTDIR%\bin\QtCore%UP_QT_FLAG%4.dll %UP_DEST_FOLDER%
::%COPY_COMMAND% %QTDIR%\bin\QtGui%UP_QT_FLAG%4.dll %UP_DEST_FOLDER%
::::%COPY_COMMAND% %QTDIR%\bin\QtOpenGL%UP_QT_FLAG%4.dll %UP_DEST_FOLDER%
::%COPY_COMMAND% %QTDIR%\bin\QtXml%UP_QT_FLAG%4.dll %UP_DEST_FOLDER%
::%COPY_COMMAND% %QTDIR%\bin\QtNetwork%UP_QT_FLAG%4.dll %UP_DEST_FOLDER%


goto END


: HELP
echo To copy the libraries choose between debug and release
echo update_libs debug,release


:END


set UP_CNOTI3D_FILE=
set UP_SOUNDMANAGER_FILE=
set UP_DEST_FOLDER=
set UP_MODE=
set UP_QT_FLAG=
set UP_OGRE_FILE1=
set UP_OGRE_FILE2=
set COPY_COMMAND=
set UP_CEGUI_FILE1=
set UP_CEGUI_FILE2=
set UP_CEGUI_FILE3=
set UP_CEGUI_FILE4=
set UP_UPDATE_MANAGER_FILE=