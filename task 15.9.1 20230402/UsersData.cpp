#include "UsersData.h"

UsersData::UsersData() {
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}

UsersData::~UsersData() {
    delete[] array;
}

void UsersData::add(LoginData fr_login, SHA1Data fr_sha1) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(fr_login, i);
        if (array[index].status == enPairStatus::free) {
            // найдена пустая ячейка, занимаем ее
            break;
        }
    }
    if (i >= mem_size) {
        resize();
        add(fr_login, fr_sha1);
    }
    else {
        array[index] = Pair(fr_login, fr_sha1);
        count++;
    }

    // кладем в свободную ячейку пару
    array[index] = Pair(fr_login, fr_sha1);
    count++;
}

void UsersData::resize() {

    Pair* save = array;
    int save_ms = mem_size;

    mem_size *= 2;
    array = new Pair[mem_size];
    count = 0;

    for (int i = 0; i < save_ms; i++) {
        Pair& old_pair = save[i];
        if (old_pair.status == enPairStatus::engaged) {
            add(old_pair.user_name, old_pair.user_sha1);
        }
    }

    delete[] save;
}

void UsersData::remove(LoginData fr_login) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(fr_login, i);
        if (array[index].status == enPairStatus::engaged &&
            !strcmp(array[index].user_name, fr_login)) {
            array[index].status = enPairStatus::deleted;
            count--;
            return;
        }
        else if (array[index].status == enPairStatus::free) {
            return;
        }
    }
}

SHA1Data* UsersData::find(LoginData fr_login) {

    for (int i = 0; i < mem_size; i++) {
        int index = hash_func(fr_login, i);
        if (array[index].status == enPairStatus::engaged &&
            !strcmp(array[index].user_name, fr_login)) {
            return &array[index].user_sha1;
        }
        else if (array[index].status == enPairStatus::free) {
            return nullptr;
        }
    }
    return nullptr;
}

int UsersData::hash_func(LoginData user_name, int offset) {
    // вычисляем индекс
    int sum = 0, i = 0;
    for (; i < strlen(user_name); i++)
    {
        sum += user_name[i];
    }
    // квадратичные пробы
    return (sum % mem_size + offset * offset) % mem_size;
}