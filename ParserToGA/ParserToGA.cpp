#include "../ParserToGA/ParserToGA.h"
#include "../Request/Request.h"
#include "../Queue/Queue.h"
#include <string>


template <typename T> bool ParserToGA<T>::validateClasses() {
    return (!req->classes.empty()) || (status_validation = false);
}

template <typename T> bool ParserToGA<T>::validateStudents() {
    int size = req->classes.size();
    for (int i = 0; i < req->students.size() - 1; i++) {
        if (req->students[i].size() == size)
            continue;
        else {
            status_validation = false;
            return false;
        }
    }
    return true;
}

template <typename T> Request * ParserToGA<T>::WorkCycle(std::string *dataJson) {
    requestStr = *dataJson;
    std::lock_guard<std::mutex> guard(status_work);
    ParserToGA<T>::ParserValidate();
    if (status_validation)
        return req;
    return nullptr;
}

template<typename T>
void ParserToGA<T>::ParserToRequest() {
    status_validation = true;
    pt::ptree tree; // создание пустого дерева
    std::stringstream ss;
    ss << requestStr;
    try {
        pt::read_json(ss, tree);
        auto parse_classes = [](pt::ptree &tree) -> Classes {
            Classes classes;

            classes.name = tree.get<std::string>("name");
            classes.teacher = tree.get<std::string>("teacher");
            classes.id_groups = tree.get<int>("id_groups");

            return classes;
        };

        auto classes = tree.get_child("classes");
        int classesNumber = 0;
        for (auto &t : classes) {
            req->classes.push_back(parse_classes(t.second));
            classesNumber++;
        }
        req->ClassesNumber = classesNumber;

        for (pt::ptree::value_type &row : tree.get_child("students")) {
            std::vector<int> child;

            for (pt::ptree::value_type &cell : row.second)
                child.push_back(cell.second.get_value<int>());

            req->students.push_back(child);
        }

        req->Iterations = tree.get<int>("iterations", 0); // поумолчанию 0
        Params param;
        param.crossover = tree.get<std::string>("params.crossover", "None");
        param.mutation = tree.get<std::string>("params.mutation", "None");
        param.selector = tree.get<std::string>("params.selector", "None");
        param.creator = tree.get<std::string>("params.creator", "None");
        req->params = param;
    } catch (boost::property_tree::ptree_error &e) {
        status_validation = false;
        return; // временно
    }

}

template<typename T> // для тестов
bool ParserToGA<T>::SetStatus() {
    if (!status_validation)
        return false;
    return true;
}

template<typename T>
void ParserToGA<T>::ParserValidate() {
    ParserToGA::ParserToRequest();
    if (!status_validation)
        return;

    if (status_validation && !ParserToGA::validateClasses())
        return;

    if (!ParserToGA::validateStudents())
        return;
}
