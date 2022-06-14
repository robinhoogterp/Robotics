import os

PREFIX_LENGTH = 8
FILE_BUFFER_SIZE = 2048

def readPrefixFromPipe(fd: object) -> int:
    """
    Will read a prefix from the pipe indicating the number of bytes that will be sent through the pipe.
    This indicator is in string format indicating a hexadecimal number.
    :param fd: the filedescriptor pointing to the pipe
    :return: an integer indicating the length
    """

    # First read how many bytes are sent (this is in byte-array, representing a HEX-number as a string)
    msgPrefix = os.read(fd, PREFIX_LENGTH)

    # convert to string
    hexlen = msgPrefix.decode()

    # decode to integer
    nrOfBytes = int("0x" + hexlen,0)

    return nrOfBytes
# readPrefixFromPipe()

def readStringFromPipe(fd: object) -> str:
    """
    Reads a complete string from the pipe. This is done by first reading a length indicator (prefix) and translating
    that to an integer (indicating the number of bytes in the string sent over the pipe).
    :param fd: the file descriptor pointing to the pipe
    :return: the string sent over through the pipe.
    """
    # first,  read the length of the pipeline
    nrOfBytes = readPrefixFromPipe(fd)

    # read the bytes
    result = os.read(fd, nrOfBytes).decode()

    return result
#  readStringFromPipe()


def writeStringToPipe(fd: object, text: str) -> int:
    """
    Writes a complete string to the pipe. first the number of bytes in the string is converted to a hexadecimal string
    and sent as a prefix through the pipe.
    :param fd:
    :param text:
    """
    #determine how much to send
    nrOfBytes = len(text)

    # convert length to hex string
    # first setup the conversion format (e.g. 8 bytes hex)
    format = "%0." + str(PREFIX_LENGTH) + "X"
    # do the conversion
    hexlen = format % nrOfBytes

    # encode strings to byte-array
    hexlenBytes = str.encode(hexlen)
    textBytes   = str.encode(text)

    # write to the pipe; first the prefix then the actual string.
    os.write(fd_write, hexlenBytes)
    os.write(fd_write, textBytes)
# writeStringToPipe()

def readFileFromPipe(fd, dest_filename: str) -> int:
    """
    Reads a complete file from the given pipe and saves it to the local file (indicated by dest_filename)
    :param fd: file descriptor pointing to the pipe
    :param dest_filename: the filename, indicating the location (path) of a local file
    """

    # first get the prefix, indicating the file size
    nrOfBytesInFile = readPrefixFromPipe(fd_read)

    # open the destination file for writing, indicating binary storage (byte-for-byte storage)
    dest_fd = open(dest_filename, "wb")

    # a counter is needed to prevent reading to much from the pipe.
    byteCounter = 0

    # read until the nr of bytes (indicated by the prefix) is reached
    while True:
        # define a buffer size
        bytesToRead = FILE_BUFFER_SIZE

        # calc how much is left to read; if needed, adjust the nr of bytes to read
        if (nrOfBytesInFile - byteCounter - bytesToRead) < 0:
            bytesToRead = nrOfBytesInFile - byteCounter

        # do the actual reading from the pipe
        bytes_read = os.read(fd_read, bytesToRead)

        # write the bytes to the file
        dest_fd.write(bytes_read)

        # adjust bytes read up till now
        byteCounter = byteCounter + len(bytes_read)

        # check if we can stop reading
        if (byteCounter >= nrOfBytesInFile):
            break;

    # close destination file
    dest_fd.close()

    return byteCounter
# readFileFromPipe()

"""
 Repeatedly received a file through a PIPE (see mkfifo), followed by an instruction and waits for an answer
 measured transfer times: 1.9GB in 2945ms (1853882368 / 2945 = 629501 bytes/ms (@buffer size = 2048 bytes)
"""
# indicate the absolute locations of the pipe (notice that the OUT-pipe is used for reading in this program)
path_read = "/tmp/greppel_out"
path_write = "/tmp/greppel_in"

# Open a pipe for reading and writing
fd_read = os.open(path_read, os.O_RDONLY)
fd_write = os.open(path_write, os.O_WRONLY)

# repeat forever
while True:

    # Get the filename
    print("before")
    filename = readStringFromPipe(fd_read)
    print("Receiving file: " + filename)

    # # get the operation/instruction ==> this could be used to conclude what to do with the given file.
    # # at this time this is discarded
    # instruction = readStringFromPipe(fd_read)
    #
    # # get the file and save it
    # # FIXME: use correct path based on current situation
    # readFileFromPipe(fd_read, "/home/martin/result.file")

    #Return an answer
    writeStringToPipe(fd_write, "OKE")

# officially this code is never reached. just a reminder to close stuff when handling exceptions properly
os.close(fd_read)
os.close(fd_write)