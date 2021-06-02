#ifndef TABLEOFLIFE_TIMETABLESIMULATOR_H
#define TABLEOFLIFE_TIMETABLESIMULATOR_H

#include "ISimulator.h"

template <std::size_t N>
class TableSimulator final: public ISimulator<N> {
public:
    explicit TableSimulator(std::vector<std::vector<int> students,
            std::vector<int> fullness, int lessons)
        :lesson(lessons), goal(0.95), students(students), fullness(fullness){};
    ~TableSimulator() = default;
    bool Exit(Genome<N> *) override;
    void Simulate(Genome<N> *) override;


private:
    //сколько занятий
    int lesson;
    float goal;
    //масив учеников на какие занятия хотят
    std::vector<std::vector<int>> students;
    //сколько может быть в каждом занятии людей
    std::vector<int> fullness;
};

template <std::size_t N>
bool TableSimulator<N>::Exit(Genome<N> *g) {
    if (g == nullptr) {
        return false;
    }
    if (ExitF == nullptr) {
        return true;
    }
    return g->GetFitness() >= goal;
}

template <std::size_t N>
void TableSimulator<N>::Simulate(Genome<N> *g) {

    if (g == nullptr) {
        return;
    }

    std::vector<int> tmp(lesson);
    auto bits = g->GetGenes();
    //для каждого студента
    int st = bits.size();

    //по студентам
    for (int i = 0; i < st; ++i) {
        std::bitset<N> lessons = bits[i];
        for (int j = lesson; j > 0; --j) {
            //если мы не записывались на занятие, но нас записали
            if (students[i][lesson-j] != 1 and lessons.test(j)) {
                g->SetFitness(0);
                return;
            }

            if (students[i][lesson-j] == 1 and lessons.test(j)) {
                tmp[j]++;
            }
        }
    }

    float result = 1;
    for (int i = 0; i < fullness.size(); ++i) {
        tmp[i] = -tmp[i] + fullness[i];
        if (tmp[i] < 0) {
            result -= (-tmp[i])/fullness[i]
        }
    }

    g->SetFitness(result);
}

#endif//TABLEOFLIFE_TIMETABLESIMULATOR_H
