#g++ main_call.cpp ../DBLAYER/create_project_db.cpp ../DBLAYER/DB/create_project.cpp ../SUPPORT/INTERFACE/sniffing.cpp  -lpcap -l sqlite3

#g++ main_call.cpp ../DBLAYER/create_project_db.cpp ../DBLAYER/DB/create_project.cpp ../DBLAYER/DB/capture_packet.cpp ../DBLAYER/capture_packet_db.cpp  ../SUPPORT/INTERFACE/sniffing.cpp  -lpcap -l sqlite3


#g++ main_call.cpp ../DBLAYER/create_project_db.cpp ../DBLAYER/DB/create_project.cpp ../DBLAYER/DB/capture_packet.cpp ../DBLAYER/capture_packet_db.cpp  ../SUPPORT/INTERFACE/sniffing.cpp  ../STRUCTURE/database_structure.cpp ../DBLAYER/DB/function.cpp -lpcap -l sqlite3

#g++ main_call.cpp ../DBLAYER/create_project_db.cpp ../DBLAYER/DB/create_project.cpp ../DBLAYER/DB/capture_packet.cpp ../DBLAYER/capture_packet_db.cpp  ../SUPPORT/INTERFACE/sniffing.cpp  ../STRUCTURE/database_structure.cpp ../DBLAYER/DB/function.cpp ../STRUCTURE/rawdata_structure.cpp -lpcap -l sqlite3


#g++ ../STRUCTURE/scenario_struct.cpp main_call.cpp ../DBLAYER/create_project_db.cpp ../DBLAYER/DB/create_project.cpp ../DBLAYER/DB/capture_packet.cpp ../DBLAYER/capture_packet_db.cpp  ../SUPPORT/INTERFACE/sniffing.cpp  ../STRUCTURE/database_structure.cpp ../DBLAYER/DB/function.cpp ../STRUCTURE/rawdata_structure.cpp  -lpcap -l sqlite3



#g++ ../STRUCTURE/scenario_struct.cpp main_call.cpp ../DBLAYER/create_project_db.cpp ../DBLAYER/DB/create_project.cpp ../DBLAYER/DB/capture_packet.cpp ../DBLAYER/capture_packet_db.cpp  ../SUPPORT/INTERFACE/sniffing.cpp  ../STRUCTURE/database_structure.cpp ../DBLAYER/DB/function.cpp ../STRUCTURE/rawdata_structure.cpp  ../SUPPORT/tcp_pdu.cpp -lpcap -l sqlite3 `pkg-config gtkmm-2.4 --cflags --libs`


g++ ../STRUCTURE/scenario_struct.cpp main_call.cpp ../DBLAYER/create_project_db.cpp ../DBLAYER/DB/create_project.cpp ../DBLAYER/DB/capture_packet.cpp ../DBLAYER/capture_packet_db.cpp  ../SUPPORT/INTERFACE/sniffing.cpp  ../STRUCTURE/database_structure.cpp ../DBLAYER/DB/function.cpp ../STRUCTURE/rawdata_structure.cpp  -lpcap -l sqlite3 -o tcpstub

./tcpstub
