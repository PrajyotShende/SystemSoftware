#include <iostream>  
#include <sys/stat.h> 
#include <sys/types.h> 
#include <fcntl.h>
#include <unistd.h>
using namespace std;
int main(int argc, char *argv[]) {
    struct stat z;

    if (stat(argv[1], &z) == -1) {
        cout<<"File Cannot be Retrieved. Not possible, please try later");
        return 0;
    }

    if (S_ISREG(z.st_mode)) cout<<"Normal File"<<endl;
    else if (S_ISDIR(z.st_mode)) cout<<"Not a file, but a directory"<<endl;
    else if (S_ISCHR(z.st_mode)) cout<<"Character File"<<endl;
    else if (S_ISBLK(z.st_mode)) cout<<"Block file"<<endl;
    else if (S_ISFIFO(z.st_mode)) cout<<"File type - FIFO"<< endl;
    else if (S_ISLNK(z.st_mode)) cout<<"File type - Symbolic"<<endl;
    else if (S_ISSOCK(z.st_mode)) cout<<"File type - Socket"<< endl;
    else cout<<"File type not Recognizable"<<endl;

}
