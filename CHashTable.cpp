#include "CHashTable.h"
//==============================================================================================
CHashTable::CHashTable() {
    count = 0;
    mem_size = 3; // 8;
    array = new Pair[mem_size];
}
//---------------------------------------------------------------------------
CHashTable::~CHashTable() {
    delete[] array;
}
//---------------------------------------------------------------------------
int CHashTable::hash_func(Login l, int offset) {
    int sum = 0, i = 0;
    const double r = 0.7;//0.55;
    for (; i < strlen(l); i++) {
        sum += l[i];
    }
    return int((mem_size + offset * offset) * (r * sum - int(r * sum)));
}
//---------------------------------------------------------------------------
void CHashTable::add(Login _login, Pwd _pwd) {
    int index = -1, i = 0;
    for (; i < mem_size; i++) {
        index = hash_func(_login, i);
        if (array[index].status != enPairStatus::engaged) {
            break;
        }
    }
    if (i >= mem_size) {// все перебрали, нет места
        resize();
        add(_login, _pwd);
    }
    else {
        uint* digest = sha1(_pwd, strlen(_pwd));
        array[index] = Pair(_login, digest);
        delete[] digest;
    }
    count++;
}
//---------------------------------------------------------------------------
void CHashTable::_add(Login _login, uint* sha_hash) {
    int index = -1, i = 0;
    for (; i < mem_size; i++) {
        index = hash_func(_login, i);
        if (array[index].status != enPairStatus::engaged) {
            break;
        }
    }
    if (index >= mem_size) {// все перебрали, нет места
        resize();
        _add(_login, sha_hash);
    }
    else
        array[index] = Pair(_login, sha_hash);

    count++;
}
//---------------------------------------------------------------------------
uint* CHashTable::find(Login _login) {
    uint* value{ nullptr };
    int i{ 0 };
    for (; i < mem_size; i++) {
        int index = hash_func(_login, i);
        if (!strcmp(array[index].login, _login) && array[index].status == enPairStatus::engaged) {
            value = array[index].pass_sha1_hash; 
            break;
        }
    }
    return value;
}
//---------------------------------------------------------------------------
void CHashTable::del(Login _login) {
    if (!find(_login)) return;
    int index{};
    for (int i = 0; i < mem_size; i++) {
        index = hash_func(_login, i);
        if (!strcmp(array[index].login, _login) && array[index].status == enPairStatus::engaged) {
            array[index].status = enPairStatus::deleted;
            count--;
            break;
        }
    }
}
//---------------------------------------------------------------------------
void CHashTable::resize(bool squize) {
    Pair* save = array;
    int save_ms = mem_size;
    count = 0;

    if (squize) {
        //при cжатии надо сохранить валидность хешей. “о есть те индексы по которым расположены пары со статусом engaged
        //должны быть доступны после сжати€. ѕоэтому берЄм максимальный дл€ определени€ нового размера массива 
        int max_en{};
        for (size_t i = 0; i < save_ms; i++)
            if (save[i].status == enPairStatus::engaged) 
                if (i > max_en) max_en = i;

        if ((save_ms-max_en)>3) {
            mem_size = max_en + 1;
            array = new Pair[mem_size];
            for (size_t i = 0; i < mem_size; i++) {
                if (save[i].status = enPairStatus::engaged)
                    _add(save[i].login, save[i].pass_sha1_hash);
            }
            delete[] save;
        }
    }else{
        mem_size *= 2;
        array = new Pair[mem_size];        
        for (int i = 0; i < save_ms; i++) {
            Pair& old_pair = save[i];
            if (old_pair.status == enPairStatus::engaged) {
                _add(old_pair.login, old_pair.pass_sha1_hash);
            }
        }
        delete[] save;
    }
    
}
//---------------------------------------------------------------------------
void CHashTable::show() const{
    printf("------------------------------------------------------------------------\n");
    printf(" User accounts:\n");
    printf("------------------------------------------------------------------------\n");
    for (int i = 0; i < mem_size; i++) {
        if (array[i].pass_sha1_hash)
            printf("Login:%s sha1:%X %X %X %X %X status:%d\n", array[i].login, array[i].pass_sha1_hash[0],
                array[i].pass_sha1_hash[1],
                array[i].pass_sha1_hash[2],
                array[i].pass_sha1_hash[3],
                array[i].pass_sha1_hash[4],
                array[i].status);
        //else
            //printf("<--Empty-->\n");
            //printf("Login:%s sha1:%X status:%d\n", array[i].login, 0, array[i].status);
    }
    printf("------------------------------------------------------------------------\n");
}
//---------------------------------------------------------------------------