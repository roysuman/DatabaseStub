
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
#sniffing
HEADERS +=./capture/pcapinterface.h
HEADERS +=./capture/capturemanager.h
#HEADERS +=./capture/captureoptions.h
HEADERS +=./core/api/ringbuffer.h
HEADERS +=./core/singleton.h

#parse config
HEADERS +=./core/xmlparser/parser.h
HEADERS +=./core/xmlparser/parseringbuffer.h
HEADERS +=./core/xmlparser/parsermanager.h
HEADERS +=./core/api/ringbuffer.h
HEADERS +=./core/api/apihelper.h


SOURCES +=./gui/core/main.cpp
SOURCES +=./gui/core/vservermainwindow.cpp
SOURCES +=./gui/core/qtsingletonapplication.cpp
SOURCES +=./gui/core/qtfilelock.cpp
SOURCES +=./gui/core/treeitem.cpp
SOURCES +=./gui/core/form/openDump.cpp
SOURCES +=./gui/core/form/livecapture.cpp
SOURCES +=./gui/core/viewmodel/filetreemodel.cpp
SOURCES +=./gui/core/controls/messagebox.cpp
SOURCES +=./core/api/ringbuffer.cpp
#sniffing
SOURCES +=./capture/pcapinterface.cpp
SOURCES +=./capture/capturemanager.cpp
#SOURCES +=./capture/captureoptions.cpp
#parse config
SOURCES +=./core/xmlparser/parser.cpp
SOURCES +=./core/xmlparser/parseringbuffer.cpp
SOURCES +=./core/xmlparser/parsermanager.cpp
SOURCES +=./core/api/ringbuffer.cpp

 



FORMS += gui/forms/CustomWindow.ui
FORMS += gui/forms/OpenDumpFileDialog.ui
FORMS += gui/forms/messagebox.ui

FORMS += gui/forms/livecapture.ui

RESOURCES += Resources/resource.qrc
