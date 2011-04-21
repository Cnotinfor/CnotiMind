# ------------------------------------------------------------
#
#  Project for building CnotiMind library
#
# ------------------------------------------------------------

TARGET    = CnotiMind
TEMPLATE  = lib
QT       += xml
QT       -= gui
#CONFIG   += embed_manifest_exe create

# ------------------------------------------------------------
TMP_PATH      = ../tmp
DESTDIR       = ../lib

# ------------------------------------------------------------
DEFINES      += CNOTIMIND_LIB QT_NO_QT_INCLUDE_WARN

# ------------------------------------------------------------
# Defautl settings
# ------------------------------------------------------------

#INCLUDEPATH += .

# Debug settings
CONFIG( debug, debug|release ) {
	TARGET = $${TARGET}_d
	BUILD_NAME = debug
}

# Release settings
CONFIG( release, debug|release ) {
	BUILD_NAME = release
}


OBJECTS_DIR += $${TMP_PATH}/$${BUILD_NAME}
MOC_DIR     += $${TMP_PATH}/moc
UI_DIR      += $${TMP_PATH}/ui
RCC_DIR     += $${TMP_PATH}/rcc

INCLUDEPATH += $${OBJECTS_DIR} \
			   $${MOC_DIR} \
			   $${UI_DIR} \
			   $${RCC_DIR}

# ------------------------------------------------------------
#  Files to be included in the project
# ------------------------------------------------------------
include( "Files.pri" )
include( "../include/Include.pri" )
include( "rules/Rules.pri" )

# ------------------------------------------------------------
