#-------------------------------------------------
#
# Project created by QtCreator 2014-03-19T21:38:36
#
#-------------------------------------------------

QT       += core gui    \
            sql

TARGET = TCPSTUB
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../DBLAYER/capture_packet_db.cpp \
    ../DBLAYER/create_project_db.cpp \
    ../DBLAYER/DB/capture_packet.cpp \ # ../DBLAYER/DB/capture_packet.cpp_old \
    ../DBLAYER/DB/create_project.cpp \
    ../DBLAYER/DB/dummy_server.cpp \
    ../DBLAYER/DB/function.cpp \
    ../DBLAYER/DB/newpacket.cpp \
    ../DBLAYER/dummy_server_db.cpp \
    ../DBLAYER/newpacketDb.cpp \
    ../STRUCTURE/src/database_structure.cpp \
    ../STRUCTURE/src/rawdata_structure.cpp \
    ../STRUCTURE/src/scenario_struct.cpp \
    ../STRUCTURE/src/configStruct.cpp \
    ../CORE/INTERFACE/src/sniffing.cpp \
    ../CORE/STUB/src/server.cpp \
    ../SUPPORT/LOG/src/loghandle.cpp \
    ../SUPPORT/init.cpp \
    newproject.cpp \
    adddbserver.cpp \
   #../CORE/DISSECTOR/src/buffer.cpp \
    ../CORE/DISSECTOR/src/field.cpp \
    ../CORE/DISSECTOR/src/proto.cpp \
    ../CORE/DISSECTOR/src/types.cpp \
    ../CORE/DISSECTOR/src/proto_mysql.cpp \
   ../CORE/DISSECTOR/src/ber.cpp    \
    ../CORE/DISSECTOR/src/proto_ldap.cpp \
    ../CORE/DISSECTOR/src/shift_char.cpp \
    ../SUPPORT/JSON/src/jsonHandler.cpp \
    projectopen.cpp	\
   ../Test/src/readFromJsonFile.cpp

HEADERS  += mainwindow.h \
    ../DBLAYER/capture_packet_db.hpp \
    ../DBLAYER/create_project_db.hpp \
    ../DBLAYER/DB/capture_packet.hpp \
    ../DBLAYER/DB/create_project.hpp \
    ../DBLAYER/DB/dummy_server.hpp \
    ../DBLAYER/DB/function.hpp \
    ../DBLAYER/DB/newpacket.hpp \
    ../DBLAYER/dummy_server_db.hpp \
    ../DBLAYER/newpacketDb.hpp \
    ../STRUCTURE/include/database_structure.hpp \
    ../STRUCTURE/include/rawdata_structure.hpp \
    ../STRUCTURE/include/scenario_struct.hpp \
    ../STRUCTURE/include/globalDatatypes.hpp \
    ../STRUCTURE/include/configStruct.hpp \
    ../CORE/INTERFACE/include/sniffing.hpp \
    ../CORE/STUB/include/server.hpp \
    ../SUPPORT/LOG/include/loghandle.hpp \
    ../SUPPORT/init.hpp \
    newproject.h \
    adddbserver.h \
    ../CORE/DISSECTOR/include/field.hpp \
    ../CORE/DISSECTOR/include/proto.hpp \
    ../CORE/DISSECTOR/include/types.hpp \
    ../CORE/DISSECTOR/include/init.hpp \
    ../CORE/DISSECTOR/include/shift_int.hpp \
    ../CORE/DISSECTOR/include/proto_mysql.hpp \
    ../CORE/DISSECTOR/include/ber.hpp    \
    ../CORE/DISSECTOR/include/proto_ldap.hpp \
    ../CORE/DISSECTOR/include/shift_char.hpp \
    ../SUPPORT/JSON/include/jsonHandler.hpp \
    ../CORE/DISSECTOR/include/buffer.hpp \
    projectopen.h   \
    ../SUPPORT/globalDatatypes.hpp	\
   ../Test/include/readFromJsonFile.hpp

FORMS    += mainwindow.ui \
    newproject.ui \
    adddbserver.ui \
    projectopen.ui
LIBS += -lpcap \
    -lsqlite3 \
#    -ljson_linux-gcc-4.4.3_libmt    \
   -ljson_linux-gcc-4.6_libmt  \	
    -lboost_serialization   \
    -lboost_thread
QMAKE_CXXFLAGS += -std=c++0x
