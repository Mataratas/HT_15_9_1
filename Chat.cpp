#include "Chat.h"
//==================================================================================
void Chat::reg(char _login[NAMELENGTH], char _pass[], int pass_length) {
    data.add(_login, _pass);
}
//----------------------------------------------------------------------------------
bool Chat::login(char _login[NAMELENGTH], char _pass[], int pass_length) {
    int i = 0;
    uint* found_hash{ nullptr };
    for (; i < data.get_count(); i++) {
        found_hash = data.find(_login);
        if (found_hash) {
            break;
        }
    }
    if (i >= data.get_count()) return false;

    uint* digest = sha1(_pass, pass_length);

    bool cmpHashes = !memcmp(
        found_hash,
        digest,
        SHA1HASHLENGTHBYTES);
    delete[] digest;

    return cmpHashes;
}
//----------------------------------------------------------------------------------
void Chat::remove_account(char _login[NAMELENGTH]) {
    data.del(_login);
}
//----------------------------------------------------------------------------------
void Chat::squize() {
    data.resize(true);
}
//----------------------------------------------------------------------------------
void Chat::show() const {
    data.show();
}
//----------------------------------------------------------------------------------