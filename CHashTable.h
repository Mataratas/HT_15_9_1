#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <string.h>
#include "sha1.h"
//=========================================================================================
#define NAMELENGTH 10  
#define PWDLENGTH 21  

typedef char Login[NAMELENGTH]; // 
typedef char Pwd[NAMELENGTH];
//-----------------------------------------------------------------------------------------
class CHashTable{
public:

    CHashTable();
    ~CHashTable();
    void add(Login, Pwd);
    
    void del(Login);
    uint* find(Login);
    void resize(bool squize = false);
    void show() const;
    int get_count() const { return count; }

private:
    void _add(Login, uint*);
    enum enPairStatus {
        free, // свободен
        engaged, //занят
        deleted //удален
    };

    struct Pair {
        Pair() :
            login(""),
            pass_sha1_hash(0),status(free) {
        }
        ~Pair() {
            if (pass_sha1_hash != 0)
                delete[] pass_sha1_hash;
        }
        Pair(char _login[NAMELENGTH], uint* sh1) {
            strcpy(login, _login);
            pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
            memcpy(pass_sha1_hash, sh1, SHA1HASHLENGTHBYTES);
            status = engaged;
        }
        Pair& operator = (const Pair& other) {
            strcpy(login, other.login);

            if (pass_sha1_hash != 0)
                delete[] pass_sha1_hash;
            pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];

            memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);

            status = other.status;

            return *this;
        }
        char login[NAMELENGTH];
        uint* pass_sha1_hash;
        enPairStatus status;
    };

    int hash_func(Login l, int offset);//multiplication

    Pair* array;
    int mem_size;
    int count;
};

