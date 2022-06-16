#include "telemetryPipe.h"


#define PREFIX_LENGTH 8
#define FILE_BUFFER_SIZE 2048

/**
 * Repeatedly sends a file through a PIPE (see mkfifo), followed by an instruction and waits for an answer
 * measured transfer times: 1.9GB in 2945mshtop (1853882368 / 2945 = 629501 bytes/ms (@buffer size = 2048 bytes)
 * @return
 *
 */

telemetryPipe::telemetryPipe() {
    mkfifo(myfifo_read, 0666);
    mkfifo(myfifo_write, 0666);
}

void telemetryPipe:: sendState() {
    telemetrics* tel = telemetrics::getInstance();
    std::string t_json = JS::serializeStruct((*tel).telemetry, JS::SerializerOptions(JS::SerializerOptions::Compact));
    const char *t_json_char = t_json.c_str();
    char hexlen[8 + 1];
    size_t chars_read;
    uint64_t start = getTimestamp();

    //std::cout << "write integer " << fcntl(fd_write, F_GETFD) << std::endl;

    writeStringToPipe(fd_write, t_json_char);



    uint64_t ended = getTimestamp();
    std::cout << "Sending finished in " << (ended - start) << "ms" << std::endl;

    char answer[512];
    //std::cout << "read integer " << fcntl(fd_read, F_GETFD) << std::endl;


    readStringFromPipe(answer, fd_read);
    (*tel).xPos = std::stoi(answer);
    std::cout << "Singleton xPos " << (*tel).xPos << std::endl;

}

void telemetryPipe::printDCS() {
    telemetrics* tel = telemetrics::getInstance();
    std::string t_json = JS::serializeStruct((*tel).telemetry);
    std::cout << t_json << std::endl;
}


/***
 * Create a string indicating the hexadecimal representation of the given parameter LEN
 * @param buffer a pointer to a buffer where the result is stored. make sure to declare enough space to hold the result
 * It is advised to the the constant PREFIX_LENGTH+1
 * @param len the integer number to be converted.
 */
void telemetryPipe::createLengthIndicator(char *buffer, unsigned long int len){
    char format[5];
    // setup the format using the constant
    sprintf(format, "%%0%dX", PREFIX_LENGTH);

    // print in HEX to the given buffer
    sprintf(buffer, format , len);
}//createLengthIndicator

/***
 * gets the current timestamp in milliseconds (UNIX style, since 1/1/1970 00:00:00)
 * @return the number of milleseconds
 */
uint64_t telemetryPipe::getTimestamp() {
    return std::chrono::duration_cast< std::chrono::milliseconds >(
            std::chrono::system_clock::now().time_since_epoch()
    ).count();
}//getTimestamp

/**
 * writes a string to the pipe. the string is prefixed with a hexadecimal indicator, indicating the length.
 * @param fd File Descriptor of the pipe (see also mkfifo)
 * @param text the text to be written to the pipe
 * @return
 */
unsigned long int telemetryPipe::writeStringToPipe (int fd, const char* text){
    char hexlen[8 + 1];
    unsigned long int len = strlen(text);

    // first create the prefix in HEX-format: how many bytes will follow?
    createLengthIndicator(hexlen, len);
    write (fd, hexlen,PREFIX_LENGTH  );
    write (fd, text, len);
    return len;
}//writeStringToPipe

/**
 * write a complete file to the pipe. The contents of the file is prefixed with a hexadecimal indicator, indicating
 * the length of the file
 * @param fd File Descriptor of the pipe (see also mkfifo)
 * @param path the absolute path to the file to be written
 * @return the number of bytes written
 */
unsigned long int telemetryPipe::writeFileToPipe(int fd, const char *path) {
    char hexlen[PREFIX_LENGTH+1];
    char buffer[FILE_BUFFER_SIZE];

    // create the streamreader, indicate binary (byte-for-byte reading)
    std::ifstream infile(path, std::ifstream::binary);

    //get length of file (seek to end, then back to begin
    infile.seekg(0, std::ios::end);
    size_t length = infile.tellg();
    infile.seekg(0, std::ios::beg);

    // write the length of the file in HEX to the pipe
    createLengthIndicator(hexlen, ( unsigned int) length);
    write (fd, hexlen, PREFIX_LENGTH  );

    // read the file
    while (!infile.eof()){
        // read from the file, maximum size of the buffer
        infile.read(buffer, sizeof(buffer));

        // determine how many bytes were read
        int bytesRead = infile.gcount();

        // write the file to the pipe.
        write(fd, buffer, bytesRead);
    }

    return (unsigned long int ) length;
}//writeFileToPipe

/**
 * Reads a length indicator (string in hexadecimal format)
 * @param fd the file descriptor of the pipe (see also mkfifo)
 * @return the number converted to an unsigned long int
 */
unsigned long int telemetryPipe::readLengthIndicatorFromPipe(int fd){
    char hexlen[PREFIX_LENGTH + 1];

    read(fd, hexlen, 8);
    hexlen[8]='\0';
//    std::cout << "hexlen " << hexlen << " -------------" << std::endl;

//    try {
        return std::stoi(hexlen, 0,  16);
//    }
//
//    catch (const std::invalid_argument& ia) {
//        std::cerr << "Invalid argument: " << ia.what() << std::endl;
//        std::cout << "-1 -------------" << std::endl;
//        throw std::exception();
//    }
//
//    catch (const std::out_of_range& oor) {
//        //std::cerr << "Out of Range error: " << oor.what() << std::endl;
//        std::cout << "-2 -------------" << std::endl;
//        throw std::exception();
//
//    }
//
//    catch (const std::exception& e)
//    {
//        //std::cerr << "Undefined error: " << e.what() << std::endl;
//        std::cout << "0 -------------" << std::endl;
//        throw std::exception();
//
//    }


}//readLengthIndicatorFromPipe

/**
 * reads a string from the given pipe, storing the string in the given buffer
 * @param buffer the buffer to hold the string read from pipe; make sure the buffer is large enough!
 * @param fd the file descriptor of the pipe (see also mkfifo)
 * @return
 */
int telemetryPipe::readStringFromPipe(char *buffer, int fd) {
    int nrOfBytesToRead = readLengthIndicatorFromPipe(fd);

    read(fd, buffer, nrOfBytesToRead);

    buffer[nrOfBytesToRead] = '\0';

    return nrOfBytesToRead;
}//readStringFromPipe
