#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>



#define AC                         "\x1b[01;36m"
#define AM                         "\x1b[01;35m"
#define AR                         "\x1b[0m"
#define AY                         "\x1b[01;33m"
#define AB                         "\x1b[01;5m"

#define NUM                        "\t\x1b[01;36m%d) \x1b[0m"
#define TAB                        "\t"
#define SPACER                      "    \x1b[01;35m>\x1b[0m "
#define AION                      "\x1b[01;36mAion\x1b[01;35m>\x1b[0m "

#define BUFSIZE                    64

#define PATH                      "/etc/"


// Converts the file content into a string
// INPUT: Path to the file folder
// OUTPUT: Converted content

char* file_to_string(char* path)
{

        char file_path[BUFSIZE];
        sprintf(file_path, "%s/aion.tkn", path);

        int fd_owner = open(file_path, O_RDONLY);
        if (fd_owner < 0) return "Unknown";

        char *buffer = malloc (BUFSIZE);

        bzero(buffer, BUFSIZE);
        read(fd_owner, buffer, BUFSIZE);
        close(fd_owner);

        buffer[strlen(buffer)-1] = 0;


        return (char*) buffer;
}


// Verifies if the string contains only digits or not
// INPUT: String
// OUTPUT: TRUE / FALSE


int validate_number(char *str) {
        while (*str) {
                if(!isdigit(*str)) return 0;

                str++;
        }
        return 1;
}


// Verifies if the string respect the IPv4 format
// INPUT: String
// OUTPUT: TRUE / FALSE

int validate_ip(char *ip) {
        int i, num, dots = 0;
        char *ptr;
        if (ip == NULL)
                return 0;
        ptr = strtok(ip, "."); // String explosion
        if (ptr == NULL)
                return 0;
        while (ptr) {
                if (!validate_number(ptr)) return 0;
                num = atoi(ptr);
                if (num >= 0 && num <= 255) {
                        ptr = strtok(NULL, ".");
                        if (ptr != NULL) dots++;
                } else return 0;
        }
        if (dots != 3) return 0;
        return 1;
}

int main(int argc, char const **argv)
{

        printf(AM "_____"AC "/\\\\\\\\\\\\\\\\\\"AM "______________________________________        \n");
        printf(" ___"AC "/\\\\\\\\\\\\\\\\\\\\\\\\\\"AM "____________________________________       \n");
        printf("  __"AC "/\\\\\\/////////\\\\\\"AM "__"AC "/\\\\\\"AM "_____________________________      \n");
        printf("   _"AC "\\/\\\\\\"AM "_______"AC "\\/\\\\\\"AM "_"AC "\\///"AM "______"AC "/\\\\\\\\\\"AM "_____"AC "/\\\\/\\\\\\\\\\\\"AM "___     \n");
        printf("    _"AC "\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"AM "__"AC "/\\\\\\"AM "___"AC "/\\\\\\///\\\\\\"AM "__"AC "\\/\\\\\\////\\\\\\"AM "__    \n");
        printf("     _"AC "\\/\\\\\\/////////\\\\\\"AM "_"AC "\\/\\\\\\"AM "__"AC "/\\\\\\"AM "__"AC "\\//\\\\\\"AM "_"AC "\\/\\\\\\"AM "__"AC "\\//\\\\\\"AM "_   \n");
        printf("      _"AC "\\/\\\\\\"AM "_______"AC "\\/\\\\\\"AM "_"AC "\\/\\\\\\"AM "_"AC "\\//\\\\\\"AM "__"AC "/\\\\\\"AM "__"AC "\\/\\\\\\"AM "___"AC "\\/\\\\\\"AM "_  \n");
        printf("       _"AC "\\/\\\\\\"AM "_______"AC "\\/\\\\\\"AM "_"AC "\\/\\\\\\"AM "__"AC "\\///\\\\\\\\\\/"AM "___"AC "\\/\\\\\\"AM "___"AC "\\/\\\\\\"AM "_ \n");
        printf("        _"AC "\\///"AM "________"AC "\\///"AM "__"AC "\\///"AM "_____"AC "\\/////"AM "_____"AC "\\///"AM "____"AC "\\///"AM "__\n" AR);
        printf(AY "                                                       v1.0.1\n" AR);

        printf("\033[31;1;5mWARNING: This is a vulnerable application!\033[0m\n");
        printf("\nThis application is made to speed up the configuration of multiple network hosts \n\n");


        printf("\nChoose an option: \n");
        printf(NUM "Get hostname" TAB TAB NUM "Get IP address\n", 1, 2);
        printf(NUM "Change IP address" TAB NUM "Get interfaces\n", 3, 4);
        printf(NUM "Exit from Aion" TAB NUM "Reboot\n", 5, 6);
        printf(NUM "Shutdown\n\n\n", 7);



        char *eptr;
        long result;
        char option[sizeof(int)];
        char buffer[BUFSIZE];



        while (1) {

                // User input fetching
                printf(AION);
                gets(option);
                result = strtol(option, &eptr, 10);


                switch (result) {
                case 1: {

                        // Get hostname
                        char hostname[BUFSIZE];
                        hostname[BUFSIZE-1] = '\0';
                        gethostname(hostname, BUFSIZE-1);
                        printf(SPACER AC "Hostname: "AR "%s\n", hostname);
                } break;
                case 2: {

                        // Get IP address
                        printf(SPACER AC "Insert the interface name" AR "\n");
                        printf(SPACER);
                        gets(buffer);

                        struct ifaddrs *ifaddr, *ifa;
                        int family, s;
                        char host[NI_MAXHOST];

                        if (getifaddrs(&ifaddr) == -1)
                        {
                                perror("getifaddrs");
                                exit(EXIT_FAILURE);
                        }


                        int found = 0;
                        for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
                        {
                                if (ifa->ifa_addr == NULL)
                                        continue;

                                s=getnameinfo(ifa->ifa_addr,sizeof(struct sockaddr_in),host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

                                if((strcmp(ifa->ifa_name,buffer)==0)&&(ifa->ifa_addr->sa_family==AF_INET))
                                {
                                        found++;
                                        printf(SPACER AC "Address: "AR "%s\n", host);
                                }


                        }
                        if (!found) printf(SPACER AM "Interface not found"AR "\n");

                        freeifaddrs(ifaddr);

                } break;
                case 3: {

                        // Change IP address
                        printf(SPACER AC "Insert the new IP address" AR " (xxx.xxx.xxx.xxx)\n");
                        printf(SPACER);
                        gets(buffer);

                        if (!validate_ip(buffer)) {
                                printf(SPACER AM "IP address not valid"AR "\n");
                                break;
                        }
                        char IPaddr[BUFSIZE];
                        strcpy(IPaddr, buffer);





                        printf(SPACER AC "Insert mask" AR " (0-32)\n");
                        printf(SPACER);
                        gets(buffer);

                        int mask = atoi(buffer);
                        if (mask < 0 || mask > 32) {
                                printf(SPACER AM "Mask not valid"AR "\n");
                                break;
                        }



                        printf(SPACER AC "Insert the interface" AR "\n");
                        printf(SPACER);
                        gets(buffer);

                        char interface[BUFSIZE];
                        strcpy(interface, buffer);


                        printf(SPACER AC "Due to safety reasons, insert the root password to apply the changes:" AR "\n");



                        char psw_o[15];
                        strcpy(psw_o, file_to_string(PATH));

                        char psw[15];
                        int access = 0;

                        printf(SPACER);
                        gets(psw);



                        if (strcmp(psw, psw_o)) {
                                printf(SPACER AM "Invalid password"AR "\n");

                        }else{
                                printf(SPACER AC "Access gained"AR "\n");
                                access = 1;
                        }


                        if(access) {
                                char cmd[BUFSIZE*20] = "sudo ip flush dev ";
                                sprintf(cmd, "ip a flush dev %s", interface);
                                printf("%s\n", cmd);
                                system(cmd);

                                sprintf(cmd, "ip a add %s/%d dev %s", IPaddr, mask, interface);
                                system(cmd);
                        }




                } break;
                case 4: {

                        // Get interfaces list
                        printf(SPACER AC "Interfaces list" AR "\n");
                        struct if_nameindex *if_nidxs, *intf;

                        if_nidxs = if_nameindex();
                        if ( if_nidxs != NULL )
                        {
                                for (intf = if_nidxs; intf->if_index != 0 || intf->if_name != NULL; intf++)
                                {
                                        printf(SPACER "- %s\n", intf->if_name);
                                }

                                if_freenameindex(if_nidxs);
                        }
                } break;
                case 5: {

                        // Exit from Aion
                        printf(SPACER "Bye!\n");
                        exit(0);
                } break;
                case 6: {

                        // Reboot
                        system("reboot");
                } break;
                case 7: {

                        // Shutdown
                        system("shutdown now");
                } break;

                default:
                        printf("Invalid option\n");
                        break;
                }

        }


        return 0;
}
