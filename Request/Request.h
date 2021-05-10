#include <iostream>
#include <vector>

#ifndef TABLEOFLIFE_REQUEST_H
#define TABLEOFLIFE_REQUEST_H

struct Group {
    int id_group;
    std::string name; // название группы
    int count_pupil; // колличество учеников
};

struct Classes {
    int id_classes;
    std::string name; // название занятия
    std::string teacher; // имя преподавателя
    int id_groups; // хранит id группы (Group)
};

class Request {
public:
    Request() = default;
    ~Request() = default;
    Request(const Request&) = delete;

    int id; // Генерируем на сервере uuid и отдаем пользователю
    std::vector<Classes> classes; // все занятия, а вних id группы
    std::vector<std::vector<int>> pupil_params; // все ученики и их параметры
    size_t countActive; // колличество занятий
    time_t timeIterations; //если ограничение по времени
    size_t numIterations; //если ограничение по числу
    //это нужно для билдера ГА
    std::tuple<std::string, std::string, std::string, std::string> params; // приходит в заявке, настройка ГА
};

#endif //TABLEOFLIFE_REQUEST_H
