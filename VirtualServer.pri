
#Pri file for Vserver.pro



HEADERS +=./gui/forms/CustomWindow.h
HEADERS +=./gui/core/vservermainwindow.h
HEADERS +=./gui/core/qtsingletonapplication.h
HEADERS +=./gui/core/qtfilelock.h
HEADERS +=./gui/core/treeitem.h
HEADERS +=./gui/core/form/openDump.h
HEADERS +=./gui/core/form/livecapture.h
HEADERS +=./gui/core/viewmodel/filetreemodel.h
HEADERS +=./gui/core/controls/messagebox.h

SOURCES +=./gui/core/main.cpp
SOURCES +=./gui/core/vservermainwindow.cpp
SOURCES +=./gui/core/qtsingletonapplication.cpp
SOURCES +=./gui/core/qtfilelock.cpp
SOURCES +=./gui/core/treeitem.cpp
SOURCES +=./gui/core/form/openDump.cpp
SOURCES +=./gui/core/form/livecapture.cpp
SOURCES +=./gui/core/viewmodel/filetreemodel.cpp
SOURCES +=./gui/core/controls/messagebox.cpp

FORMS += gui/forms/CustomWindow.ui
FORMS += gui/forms/OpenDumpFileDialog.ui
FORMS += gui/forms/messagebox.ui

FORMS += gui/forms/livecapture.ui

RESOURCES += Resources/resource.qrc
