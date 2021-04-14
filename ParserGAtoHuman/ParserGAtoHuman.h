#ifndef TABLEOFLIFE_PARSERGATOHUMAN_H
#define TABLEOFLIFE_PARSERGATOHUMAN_H


class Result;
class Solution;

class ParserGAtoHuman {
public:
    ParserGAtoHuman();
    ~ParserGAtoHuman();

    Solution* GetReadable();
private:
    Result *unreadable;
};


#endif //TABLEOFLIFE_PARSERGATOHUMAN_H
