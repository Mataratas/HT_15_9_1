#pragma once
#pragma warning(disable : 4996)
#include "CHashTable.h"

#define SIZE 10
//===============================================================================
class Chat {
public:
    Chat()=default;
    void reg(char _login[NAMELENGTH], char _pass[], int pass_length);
    bool login(char _login[NAMELENGTH], char _pass[], int pass_length);
    void remove_account(char _login[NAMELENGTH]);
    void squize();
    void show() const;

private:
    CHashTable data;
};


