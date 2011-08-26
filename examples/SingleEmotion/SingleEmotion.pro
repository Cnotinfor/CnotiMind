# ------------------------------------------------------------
#
#  Project for building Little Mozart with the Ogre SDK
#
# ------------------------------------------------------------

TARGET    = SingleEmotion
TEMPLATE  = app
QT       += xml
CONFIG   += embed_manifest_exe

# ------------------------------------------------------------
# Debug settings
CONFIG( debug, debug|release ) {
	TARGET = $${TARGET}_d
	BUILD_NAME = debug
	LIBS += -lCnotiMind_d
}

# Release settings
CONFIG( release, debug|release ) {
	BUILD_NAME = release
	LIBS += -lCnotiMind
}

# ------------------------------------------------------------
TMP_PATH      = ../../tmp/examples/$${TARGET}
DESTDIR       = ../bin/$${BUILD_NAME}

# ------------------------------------------------------------
INCLUDEPATH += ../../include

LIBS += -L../../lib

# ------------------------------------------------------------
#  Files to be included in the project
# ------------------------------------------------------------


HEADERS += \
	Form.h

SOURCES += \
	Form.cpp \
	main.cpp

FORMS += \
	Form.ui

OTHER_FILES += \
	../xml/single_emotion_rules.xml \
	../xml/mind_settings.xml
