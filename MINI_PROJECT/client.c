#include "common1.h"

int main()
{
    int client_fd;

    struct sockaddr_in server;
    
    char buffer[1000];

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (client_fd == -1)
    {
        perror("Socket creation failed");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if (connect(client_fd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("Connection to server failed");
        exit(1);
    }

    printf("Connected to the server!\n");

    while(1)
    {
        
        char read_buffer[1000],write_buffer[1000];

        memset(read_buffer,0,sizeof(read_buffer));
        
        memset(write_buffer,0,sizeof(write_buffer));
        
        int read_bytes = read(client_fd,&read_buffer,sizeof(read_buffer));
        
        if(read_bytes == -1)
        {
            perror("error in reading from server\n");
        }
        else if(read_bytes == 0)
        {
            printf("nothing send from server closing connection\n");
            break;
        }
        else
        {       
            
            char *end_ptr = strchr(read_buffer, '$');
            
            if (end_ptr != NULL)
            {
                *end_ptr = '\0'; 
                printf("%s\n", read_buffer); 
                break; 
            }
                
            char *no_write = strchr(read_buffer, '%');
                
            if(no_write == NULL)
            {    
                    
                memset(write_buffer,0,sizeof(write_buffer));
                    
                    // char temp = read_buffer[0];
                    
                    // if(temp == '#')
                    // {
                    //     break;
                    // }
                                        
                printf("%s\n",read_buffer);
                    

                scanf(" %[^\n]%*c",write_buffer);

                if (strcmp(write_buffer, "#") == 0)
                {
                    write(client_fd, write_buffer, strlen(write_buffer));
                    printf("Sent '#' to server. Closing connection...\n");
                    break; 
                }
                
                int write_bytes = write(client_fd,&write_buffer,sizeof(write_buffer));
                    
                if (write_bytes == -1) 
                {
                    perror("Write to client socket\n");
                    break;
                }
            }
            else
            {
                *no_write = '\0';
                printf("%s\n",read_buffer);
            }
            
        }
    }

    close(client_fd);
    return 0;
}
