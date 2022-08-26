#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <QDebug>
void* my_memcpy(void* s1, const void* s2, size_t n);

void* my_memmove(void* s1, const void* s2, size_t n);

char* my_strcpy(char* s1, const char* s2);

char* my_strncpy(char* s1, const char* s2, size_t n);

char* my_strcat(char* s1, const char* s2);

char* my_strncat(char* s1, const char* s2, size_t n);

int my_memcmp(const void* s1, const void* s2, size_t n);

int my_strcmp(const char* s1, const char* s2);

//strcoll
int my_strcoll(const char* s1, const char* s2);

int my_strncmp(const char* s1, const char* s2, size_t n);

//strxfrm
size_t my_strxfrm(char* s1, const char* s2, size_t n);

char* my_strtok(char* s1, const char* s2);

void* my_memset(void* s, int c, size_t n);

//strerror
char* my_strerror(int errnum);

size_t my_strlen(const char* s);



#endif // FUNCTION_H
