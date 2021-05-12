#include <iostream>
#include <vector>

#ifndef TABLEOFLIFE_REQUEST_H
#define TABLEOFLIFE_REQUEST_H

// нужно подумать, возможно вообще убрать
//struct Group {
//    unsigned int id_group;
//    std::string name; // название группы
//    unsigned int count_students; // колличество учеников
//};

struct Params {
    std::string crossover;
    std::string mutation;
    std::string selector;
    std::string creator;
};

struct Classes {
    std::string name;// название занятия
    std::string teacher; // имя преподавателя
    int id_groups = 0; // хранит id группы (Group)
};

class Request {
public:
    Request(): ClassesNumber(0), id(0), Iterations(0), students(0), classes(0) { } ;
    ~Request() = default;

    int id; // Генерируем на сервере uuid и отдаем пользователю
    std::vector<Classes> classes; // все занятия, а вних id группы
    std::vector<std::vector<int>> students; // все ученики и их параметры
    size_t ClassesNumber; // количество занятий
    size_t Iterations; //если ограничение по числу максимальных итераций, нужен именно size_t
    Params params; // приходит в заявке, настройка ГА, это нужно для билдера ГА
};

#endif //TABLEOFLIFE_REQUEST_H
