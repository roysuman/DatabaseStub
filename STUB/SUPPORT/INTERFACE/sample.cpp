//#include<stdio.h>
//#include<pcap.h>
//int main(int argc,char *argv[])
//{
//int i=1;
//char errbuf[PCAP_ERRBUF_SIZE];
//char dev[]="lo"; // set the device to listen on lo
//bpf_u_int32 mask;
//bpf_u_int32 net;
//pcap_t *handle;
//const u_char *packet;
//struct pcap_pkthdr header;
    
//printf("\nOpen Device = %s\n\n",dev);
    
//handle=pcap_open_live(dev,BUFSIZ,1,0,errbuf);
//for ( ; ; )
//    {
//        printf("Sniff no. %d\n",i);
//        packet=(u_char *)pcap_next(handle,&header);
//  if (packet == NULL)
//        {
//            printf("      No Packet!!?? on sniff no. %d\n",i );
//            i++;
//            continue;
//        }else
//  if (packet != NULL)
//        {
//            /*   possible to insert code here for printing out packet down here    */
            
//            printf("      Captured a Packet of Length [%d] from Device [%s]\n",header.len,dev);
//            printf("\nClosing Dev handle\n",dev);
//            pcap_close(handle);
//            break;
//        }
//     }
//   printf("Exit Now!\n\n",dev);
//   return(0);
//}
