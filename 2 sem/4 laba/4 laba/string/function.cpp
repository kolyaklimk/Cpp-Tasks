#include "function.h"
//https://opensource.apple.com/source/BerkeleyDB/BerkeleyDB-18/db/clib/strncat.c.auto.html

void* my_memcpy(void* s1, const void* s2, size_t n) {
    char* csrc = (char*)s2;
    char* cdest = (char*)s1;

    for (int i = 0; i < n; i++)
        cdest[i] = csrc[i];
}

void* my_memmove(void* s1, const void* s2, size_t n) {
    char* csrc = (char*)s2;
    char* cdest = (char*)s1;

    char* temp = new char[n];

    for (int i = 0; i < n; i++)
        temp[i] = csrc[i];

    for (int i = 0; i < n; i++)
        cdest[i] = temp[i];

    delete[] temp;
}

char* my_strcpy(char* s1, const char* s2) {
    if (s1 == NULL) {
        return NULL;
    }
    char* ptr = s1;

    while (*s2 != '\0')
    {
        *s1 = *s2;
        s1++;
        s2++;
    }

    *s1 = '\0';
    return ptr;
}

char* my_strncpy(char* s1, const char* s2, size_t n)
{
    if (s1 == NULL) {
        return NULL;
    }

    char* ptr = s1;

    while (*s2 && n--)
    {
        *s1 = *s2;
        s1++;
        s2++;
    }

    *s1 = '\0';

    return ptr;
}

char* my_strcat(char* destination, const char* source)
{
    char* ptr = destination + my_strlen(destination);

    while (*source != '\0') {
        *ptr++ = *source++;
    }

    *ptr = '\0';

    return destination;
}

char* my_strncat(char* destination, const char* source, size_t num)
{
    char* ptr = destination + my_strlen(destination);

    while (*source != '\0' && num--) {
        *ptr++ = *source++;
    }

    *ptr = '\0';

    return destination;
}

int my_memcmp(const void* buf1, const void* buf2, size_t count)
{
    if (!count)
        return(0);

    while (--count && *(char*)buf1 == *(char*)buf2) {
        buf1 = (char*)buf1 + 1;
        buf2 = (char*)buf2 + 1;
    }

    return(*((unsigned char*)buf1) - *((unsigned char*)buf2));
}

int my_strcmp(const char* X, const char* Y)
{
    while (*X)
    {
        if (*X != *Y) {
            break;
        }

        X++;
        Y++;
    }

    return *(const unsigned char*)X - *(const unsigned char*)Y;
}

int my_strncmp(const char* s1, const char* s2, size_t n)
{
    while (n && *s1 && (*s1 == *s2))
    {
        ++s1;
        ++s2;
        --n;
    }
    if (n == 0)
    {
        return 0;
    }
    else
    {
        return (*(unsigned char*)s1 - *(unsigned char*)s2);
    }
}

char* my_strtok(char* s, char d)
{
    static char* input = NULL;

    if (s != NULL)
        input = s;

    if (input == NULL)
        return NULL;

    char* result = new char[my_strlen(input) + 1];
    int i = 0;

    for (; input[i] != '\0'; i++) {

        if (input[i] != d)
            result[i] = input[i];

        else {
            result[i] = '\0';
            input = input + i + 1;
            return result;
        }
    }

    result[i] = '\0';
    input = NULL;

    return result;
}

void* my_memset(void* b, int c, size_t len)
{
    int i;
    unsigned char* p = (unsigned char* )b;
    i = 0;
    while (len > 0)
    {
        *p = c;
        p++;
        len--;
    }
    return(b);
}

size_t my_strlen(const char* str)
{
    const char* s; 
    for (s = str; *s; ++s) ;
    return (s - str);
}


int my_strcoll(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2))
    {
        ++s1;
        ++s2;
    }
    if (*s1 == '\0' && *s2 == '\0') return 0;

    return (*(unsigned char*)s1 - *(unsigned char*)s2);
}


size_t my_strxfrm(char* s1, const char* s2, size_t n) {

    size_t buf = 0;
    if (s1 == NULL) {
        return NULL;
    }

    char* ptr = s1;

    while (*s2 && n--)
    {
        *s1 = *s2;
        s1++;
        s2++;
        buf++;
    }

    *s1 = '\0';

    return buf;
}

char* my_strerror(int errnum)
{
    char a[60];
    switch (errnum) {
    default: my_strcpy(a, "Undefined error: 0"); break;
    case 1: my_strcpy(a, "Operation not permitted"); break;
    case 2: my_strcpy(a, "No such file or directory"); break;
    case 3: my_strcpy(a, "No such process"); break;
    case 4: my_strcpy(a, "Interrupted system call"); break;
    case 5: my_strcpy(a, "Input/output error"); break;
    case 6: my_strcpy(a, "Device not configured"); break;
    case 7: my_strcpy(a, "Argument list too long"); break;
    case 8: my_strcpy(a, "Exec format error"); break;
    case 9: my_strcpy(a, "Bad file descriptor"); break;
    case 10: my_strcpy(a, "No child processes"); break;
    case 11: my_strcpy(a, "Resource deadlock avoided"); break;
    case 12: my_strcpy(a, "Cannot allocate memory"); break;
    case 13: my_strcpy(a, "Permission denied"); break;
    case 14: my_strcpy(a, "Bad address"); break;
    case 15: my_strcpy(a, "Block device required"); break;
    case 16: my_strcpy(a, "Device busy"); break;
    case 17: my_strcpy(a, "File exists"); break;
    case 18: my_strcpy(a, "Cross-device link"); break;
    case 19: my_strcpy(a, "Operation not supported by device"); break;
    case 20: my_strcpy(a, "Not a directory"); break;
    case 21: my_strcpy(a, "Is a directory"); break;
    case 22: my_strcpy(a, "Invalid argument"); break;
    case 23: my_strcpy(a, "Too many open files in system"); break;
    case 24: my_strcpy(a, "Too many open files"); break;
    case 25: my_strcpy(a, "Inappropriate ioctl for device"); break;
    case 26: my_strcpy(a, "Text file busy"); break;
    case 27: my_strcpy(a, "File too large"); break;
    case 28: my_strcpy(a, "No space left on device"); break;
    case 29: my_strcpy(a, "Illegal seek"); break;
    case 30: my_strcpy(a, "Read-only file system"); break;
    case 31: my_strcpy(a, "Too many links"); break;
    case 32: my_strcpy(a, "Broken pipe"); break;
    case 33: my_strcpy(a, "Numerical argument out of domain"); break;
    case 34: my_strcpy(a, "Result too large"); break;
    case 35: my_strcpy(a, "Resource temporarily unavailable"); break;
    case 36: my_strcpy(a, "Resource temporarily unavailable"); break;
    case 37: my_strcpy(a, "Operation now in progress"); break;
    case 38: my_strcpy(a, "Operation already in progress"); break;
    case 39: my_strcpy(a, "Socket operation on non-socket"); break;
    case 40: my_strcpy(a, "Destination address required"); break;
    case 41: my_strcpy(a, "Message too long"); break;
    case 42: my_strcpy(a, "Protocol wrong type for socket"); break;
    case 43: my_strcpy(a, "Protocol not available"); break;
    case 44: my_strcpy(a, "Protocol not supported"); break;
    case 45: my_strcpy(a, "Socket type not supported"); break;
    case 46: my_strcpy(a, "Operation not supported"); break;
    case 47: my_strcpy(a, "Protocol family not supported"); break;
    case 48: my_strcpy(a, "Address family not supported by protocol family"); break;
    case 49: my_strcpy(a, "Address already in use"); break;
    case 50: my_strcpy(a, "Can't assign requested address"); break;
    case 51: my_strcpy(a, "Network is down"); break;
    case 52: my_strcpy(a, "Network is unreachable"); break;
    case 53: my_strcpy(a, "Network dropped connection on reset"); break;
    case 54: my_strcpy(a, "Software caused connection abort"); break;
    case 55: my_strcpy(a, "Connection reset by peer"); break;
    case 56: my_strcpy(a, "No buffer space available"); break;
    case 57: my_strcpy(a, "Socket is already connected"); break;
    case 58: my_strcpy(a, "Socket is not connected"); break;
    case 59: my_strcpy(a, "Can't send after socket shutdown"); break;
    case 60: my_strcpy(a, "Too many references: can't splice"); break;
    case 61: my_strcpy(a, "Operation timed out"); break;
    case 62: my_strcpy(a, "Connection refused"); break;
    case 63: my_strcpy(a, "Too many levels of symbolic links"); break;
    case 64: my_strcpy(a, "File name too long"); break;
    case 65: my_strcpy(a, "Host is down"); break;
    case 66: my_strcpy(a, "No route to host"); break;
    case 67: my_strcpy(a, "Directory not empty"); break;
    case 68: my_strcpy(a, "Too many processes"); break;
    case 69: my_strcpy(a, "Too many users"); break;
    case 70: my_strcpy(a, "Disc quota exceeded"); break;
    case 71: my_strcpy(a, "Stale NFS file handle"); break;
    case 72: my_strcpy(a, "Too many levels of remote in path"); break;
    case 73: my_strcpy(a, "RPC struct is bad"); break;
    case 74: my_strcpy(a, "RPC version wrong"); break;
    case 75: my_strcpy(a, "RPC prog. not avail"); break;
    case 76: my_strcpy(a, "Program version wrong"); break;
    case 77: my_strcpy(a, "Bad procedure for program"); break;
    case 78: my_strcpy(a, "No locks available"); break;
    case 79: my_strcpy(a, "Function not implemented"); break;
    case 80: my_strcpy(a, "Inappropriate file type or format"); break;
    case 81: my_strcpy(a, "Authentication error"); break;
    case 82: my_strcpy(a, "Need authenticator"); break;
    case 83: my_strcpy(a, "Identifier removed"); break;
    case 84: my_strcpy(a, "No message of desired type"); break;
    case 85: my_strcpy(a, "Value too large to be stored in data type"); break;
    case 86: my_strcpy(a, "Operation canceled"); break;
    case 87: my_strcpy(a, "Illegal byte sequence"); break;
    case 88: my_strcpy(a, "Attribute not found"); break;
    case 89: my_strcpy(a, "Programming error"); break;
    case 90: my_strcpy(a, "Bad message"); break;
    case 91: my_strcpy(a, "Multihop attempted"); break;
    case 92: my_strcpy(a, "Link has been severed"); break;
    case 93: my_strcpy(a, "Protocol error"); break;
        /*
        ERRSTR(0, "Undefined error: 0");
        ERRSTR(EPERM, "Operation not permitted");
        ERRSTR(ENOENT, "No such file or directory");
        ERRSTR(ESRCH, "No such process");
        ERRSTR(EINTR, "Interrupted system call");
        ERRSTR(EIO, "Input/output error");
        ERRSTR(ENXIO, "Device not configured");
        ERRSTR(E2BIG, "Argument list too long");
        ERRSTR(ENOEXEC, "Exec format error");
        ERRSTR(EBADF, "Bad file descriptor");
        ERRSTR(ECHILD, "No child processes");
        ERRSTR(EDEADLK, "Resource deadlock avoided");
        ERRSTR(ENOMEM, "Cannot allocate memory");
        ERRSTR(EACCES, "Permission denied");
        ERRSTR(EFAULT, "Bad address");
        ERRSTR(ENOTBLK, "Block device required");
        ERRSTR(EBUSY, "Device busy");
        ERRSTR(EEXIST, "File exists");
        ERRSTR(EXDEV, "Cross-device link");
        ERRSTR(ENODEV, "Operation not supported by device");
        ERRSTR(ENOTDIR, "Not a directory");
        ERRSTR(EISDIR, "Is a directory");
        ERRSTR(EINVAL, "Invalid argument");
        ERRSTR(ENFILE, "Too many open files in system");
        ERRSTR(EMFILE, "Too many open files");
        ERRSTR(ENOTTY, "Inappropriate ioctl for device");
        ERRSTR(ETXTBSY, "Text file busy");
        ERRSTR(EFBIG, "File too large");
        ERRSTR(ENOSPC, "No space left on device");
        ERRSTR(ESPIPE, "Illegal seek");
        ERRSTR(EROFS, "Read-only file system");
        ERRSTR(EMLINK, "Too many links");
        ERRSTR(EPIPE, "Broken pipe");
        ERRSTR(EDOM, "Numerical argument out of domain");
        ERRSTR(ERANGE, "Result too large");
        ERRSTR(EAGAIN, "Resource temporarily unavailable");
        ERRSTR(EWOULDBLOCK, "Resource temporarily unavailable");
        ERRSTR(EINPROGRESS, "Operation now in progress");
        ERRSTR(EALREADY, "Operation already in progress");
        ERRSTR(ENOTSOCK, "Socket operation on non-socket");
        ERRSTR(EDESTADDRREQ, "Destination address required");
        ERRSTR(EMSGSIZE, "Message too long");
        ERRSTR(EPROTOTYPE, "Protocol wrong type for socket");
        ERRSTR(ENOPROTOOPT, "Protocol not available");
        ERRSTR(EPROTONOSUPPORT, "Protocol not supported");
        ERRSTR(ESOCKTNOSUPPORT, "Socket type not supported");
        ERRSTR(EOPNOTSUPP, "Operation not supported");
        ERRSTR(EPFNOSUPPORT, "Protocol family not supported");
        ERRSTR(EAFNOSUPPORT, "Address family not supported by protocol family");
        ERRSTR(EADDRINUSE, "Address already in use");
        ERRSTR(EADDRNOTAVAIL, "Can't assign requested address");
        ERRSTR(ENETDOWN, "Network is down");
        ERRSTR(ENETUNREACH, "Network is unreachable");
        ERRSTR(ENETRESET, "Network dropped connection on reset");
        ERRSTR(ECONNABORTED, "Software caused connection abort");
        ERRSTR(ECONNRESET, "Connection reset by peer");
        ERRSTR(ENOBUFS, "No buffer space available");
        ERRSTR(EISCONN, "Socket is already connected");
        ERRSTR(ENOTCONN, "Socket is not connected");
        ERRSTR(ESHUTDOWN, "Can't send after socket shutdown");
        ERRSTR(ETOOMANYREFS, "Too many references: can't splice");
        ERRSTR(ETIMEDOUT, "Operation timed out");
        ERRSTR(ECONNREFUSED, "Connection refused");
        ERRSTR(ELOOP, "Too many levels of symbolic links");
        ERRSTR(ENAMETOOLONG, "File name too long");
        ERRSTR(EHOSTDOWN, "Host is down");
        ERRSTR(EHOSTUNREACH, "No route to host");
        ERRSTR(ENOTEMPTY, "Directory not empty");
        ERRSTR(EPROCLIM, "Too many processes");
        ERRSTR(EUSERS, "Too many users");
        ERRSTR(EDQUOT, "Disc quota exceeded");
        ERRSTR(ESTALE, "Stale NFS file handle");
        ERRSTR(EREMOTE, "Too many levels of remote in path");
        ERRSTR(EBADRPC, "RPC struct is bad");
        ERRSTR(ERPCMISMATCH, "RPC version wrong");
        ERRSTR(EPROGUNAVAIL, "RPC prog. not avail");
        ERRSTR(EPROGMISMATCH, "Program version wrong");
        ERRSTR(EPROCUNAVAIL, "Bad procedure for program");
        ERRSTR(ENOLCK, "No locks available");
        ERRSTR(ENOSYS, "Function not implemented");
        ERRSTR(EFTYPE, "Inappropriate file type or format");
        ERRSTR(EAUTH, "Authentication error");
        ERRSTR(ENEEDAUTH, "Need authenticator");
        ERRSTR(EIDRM, "Identifier removed");
        ERRSTR(ENOMSG, "No message of desired type");
        ERRSTR(EOVERFLOW, "Value too large to be stored in data type");
        ERRSTR(ECANCELED, "Operation canceled");
        ERRSTR(EILSEQ, "Illegal byte sequence");
        ERRSTR(ENOATTR, "Attribute not found");
        ERRSTR(EDOOFUS, "Programming error");
        ERRSTR(EBADMSG, "Bad message");
        ERRSTR(EMULTIHOP, "Multihop attempted");
        ERRSTR(ENOLINK, "Link has been severed");
        ERRSTR(EPROTO, "Protocol error");
        */
    }
    return a;
}