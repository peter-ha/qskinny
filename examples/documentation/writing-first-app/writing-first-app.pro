TEMPLATE = app
TARGET = myapp

INCLUDEPATH += /home/peter/temp/qskinny/support \
               /home/peter/temp/qskinny/src/common \
               /home/peter/temp/qskinny/src/controls \
               /home/peter/temp/qskinny/src/layouts

LIBS += -L/home/peter/temp/qskinny/lib -lqskinny -lqsktestsupport

SOURCES += \
    main.cpp
