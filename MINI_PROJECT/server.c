#include "common1.h"
#include "real_admin.h"
#include "employee.h"
// #include "admin.h"

int server_fd;

// void signalHandler(int signum)
// {
//     printf("\nInterrupt signal (%d) received. Shutting down the server.\n", signum);
//     close(server_fd);
//     exit(0);
// }

void connection(int fd)
{
    printf("Client And Server connection successful\n");

    char buffer[1000];
    
    int choice;
    
    int ptr = 0;
    
    while(1)
    {
        

        int write_bytes = write(fd,"\nWho would you like to login as:\n\n1. Admin\n2. Employee\n3. Customer\n4. Exit\n\nEnter Your Choice",strlen("\nWho would you like to login as:\n\n1. Admin\n2. Employee\n3. Customer\n4. Exit\n\nEnter Your Choice"));
        
        if(write_bytes == -1)
        {
            perror("error in sending message to client\n");
        }
        else
        {
            memset(buffer,0,sizeof(buffer));

            int read_bytes = read(fd,buffer,sizeof(buffer));
            
            if(read_bytes == -1)
            {
                perror("error while reading from client\n");
            }
            else if(read_bytes == 0)
            {
                printf("no data sent by the client\n");
            }
            else
            {
                choice = atoi(buffer);
                switch (choice)
                {
                    case 1:
                        login_admin(fd);
                        // system("./real_admin");
                        break;
                    case 2:
                        login_employee(fd);
                        break;
                    // case 3:
                    //     employee_operation(fd,3);
                    //     break;
                    // case 4:
                    //     customer_operation(fd);
                    //     break;
                    case 5:
                            break;
                    default:
                        ptr++;
                        return;
                        break;
                }
            }
            if(ptr)
            {
                break;
            }
        }
    }
    printf("connection break\n");

    write(fd,"#",sizeof("#"));
    
    read(fd,buffer,sizeof(buffer));
} 

int main()
{
    int client_fd;
    
    socklen_t address;
    
    // signal(SIGINT, signalHandler);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (server_fd == -1)
    {
        perror("Socket creation failed");
        exit(1);
    }

    struct sockaddr_in server, client;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    int binding = bind(server_fd, (struct sockaddr *)&server, sizeof(server));

    if (binding == -1)
    {
        perror("Bind failed");
        exit(1);
    }
    printf("Binding to server socket successful!\n");

    int listening = listen(server_fd, 10);

    if (listening == -1)
    {
        perror("Listen failed");
        exit(1);
    }
    printf("Listening for connections...\n");

    address = sizeof(client);

    while ((client_fd = accept(server_fd, (struct sockaddr *)&client, &address)) != -1)
    {
        printf("Client connected\n");

        int new_client = fork();
        
        if (new_client == -1)
        {
            perror("Fork failed");
            close(client_fd);
        }
        else if (new_client == 0)
        {
            // close(server_fd);
            // handleClient(client_fd);
            connection(client_fd);
            close(client_fd);
            exit(0);
        }
        else
        {
            close(client_fd);
        }
    }

    if (client_fd == -1)
    {
        perror("Error accepting connection");
    }

    close(server_fd);
    return 0;
}
