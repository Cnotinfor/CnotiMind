# ------------------------------------------------------------
#
#  Project for building Little Mozart with the Ogre SDK
#
# ------------------------------------------------------------

TARGET    = LittleMozart
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
#  Path for CnotiMind
# ------------------------------------------------------------
INCLUDEPATH += ../../include

LIBS += -L../../lib

# ------------------------------------------------------------
#  Files to be included in the project
# ------------------------------------------------------------



SOURCES += \
	main.cpp \
	Form.cpp

OTHER_FILES += \
    ../xml/mozart_mind.xml \
    ../xml/mozart_action_modifiers.xml \
    ../xml/mozart_rules.xml \
    ../xml/mozart_tutoring.xml \
    ../xml/mozart_social.xml \
    ../xml/mozart_general.xml

HEADERS += \
	Form.h \
	CnotiAudio.h

FORMS += \
	Form.ui
