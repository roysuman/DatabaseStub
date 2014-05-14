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
    ../STRUCTURE/database_structure.cpp \
    ../STRUCTURE/rawdata_structure.cpp \
    ../STRUCTURE/scenario_struct.cpp \
    ../STRUCTURE/configStruct.cpp \
    ../SUPPORT/INTERFACE/sniffing.cpp \
    ../SUPPORT/STUB/server.cpp \
    ../SUPPORT/LOG/loghandle.cpp \
    ../SUPPORT/init.cpp \
    newproject.cpp \
    adddbserver.cpp \
  # ../SUPPORT/DISSECTOR/buffer.cpp \
    ../SUPPORT/DISSECTOR/field.cpp \
    ../SUPPORT/DISSECTOR/proto.cpp \
    ../SUPPORT/DISSECTOR/types.cpp \
    ../SUPPORT/DISSECTOR/proto_mysql.cpp \
   ../SUPPORT/DISSECTOR/ber.cpp    \
    ../SUPPORT/DISSECTOR/proto_ldap.cpp \
    ../SUPPORT/GENERATOR/shift_char.cpp \
    ../SUPPORT/JSON/jsonHandler.cpp \
    projectopen.cpp

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
    ../STRUCTURE/database_structure.hpp \
    ../STRUCTURE/rawdata_structure.hpp \
    ../STRUCTURE/scenario_struct.hpp \
    ../STRUCTURE/sumanGtkmm.hpp \
    ../STRUCTURE/configStruct.hpp \
    ../SUPPORT/INTERFACE/sniffing.hpp \ 
    ../SUPPORT/STUB/server.hpp \
    ../SUPPORT/LOG/loghandle.hpp \
    ../SUPPORT/init.hpp \
    newproject.h \
    adddbserver.h \
    ../SUPPORT/DISSECTOR/field.hpp \
    ../SUPPORT/DISSECTOR/proto.hpp \
    ../SUPPORT/DISSECTOR/types.hpp \
    ../SUPPORT/DISSECTOR/init.hpp \
    ../SUPPORT/DISSECTOR/shift_int.hpp \
    ../SUPPORT/DISSECTOR/proto_mysql.hpp \
    ../SUPPORT/DISSECTOR/ber.hpp    \
    ../SUPPORT/DISSECTOR/proto_ldap.hpp \
    ../SUPPORT/GENERATOR/shift_char.hpp \
    ../SUPPORT/JSON/jsonHandler.hpp \
    ../SUPPORT/DISSECTOR/buffer.hpp \
    projectopen.h

FORMS    += mainwindow.ui \
    newproject.ui \
    adddbserver.ui \
    projectopen.ui
LIBS += -lpcap \
    -lsqlite3 \
    -ljson_linux-gcc-4.6_libmt	\
    -lboost_serialization	
QMAKE_CXXFLAGS += -std=c++0x
