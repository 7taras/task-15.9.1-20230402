#pragma once

#include <string.h>
#define NAMELENGTH 20  // Зафикcируем длину имени
#define SHA1LENGTH 40 

typedef char LoginData[NAMELENGTH];
typedef char SHA1Data[SHA1LENGTH]; 

class UsersData
{
public:
    UsersData();
    ~UsersData();
    void add(LoginData fr_login, SHA1Data fr_sha1);
    void remove(LoginData fr_login);
    SHA1Data* find(LoginData fr_login);

private:       

    enum enPairStatus {
        free,
        engaged,
        deleted
    };

    struct Pair // пара ключ-значение
    { 
        Pair() :
            user_name(""),
            user_sha1(""),
            status(enPairStatus::free)
        {}
        Pair(LoginData fr_login, SHA1Data fr_sha1) :
            status(enPairStatus::engaged) {
            memcpy(user_name, fr_login, NAMELENGTH);
            memcpy(user_sha1, fr_sha1, SHA1LENGTH);
        }
        Pair& operator = (const Pair& other) {
            memcpy(user_name, other.user_name, NAMELENGTH);
            memcpy(user_sha1, other.user_sha1, SHA1LENGTH);
            status = other.status;
            return *this;
        }

        bool operator == (const Pair& other) {
            return  status == other.status &&
                (status != enPairStatus::engaged || (!strcmp(user_name, other.user_name) && !strcmp(user_sha1, other.user_sha1)));
        }

        LoginData user_name;
        SHA1Data user_sha1;
        enPairStatus status;
    };

    void resize();
    int hash_func(LoginData user_name, int offset);

    Pair* array;
    int mem_size;
    int count;
};