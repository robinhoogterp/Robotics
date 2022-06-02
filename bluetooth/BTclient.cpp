#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main(int argc, char **argv)
{
    struct sockaddr_rc addr = { 0 };
    char buf[1024];
    int s, status, bytes_read;
    char dest[18] = "30:C6:F7:0E:34:AA";

    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );

    // connect to server
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

    memset(buf,0, sizeof(buf));
  

    // send a message
    if( status == 0 ) {
        status = write(s, "hallo!", 6);
    }
    listen(s, 1);
    while (true)
    {
       bytes_read = read(s,buf, sizeof(buf));
    if(bytes_read > 0){
        printf("recieved[%s]\n",buf);
        break;
    }
    }
    

    if( status < 0 ) perror("uh oh");

    close(s);
    close(status);
    return 0;
}

