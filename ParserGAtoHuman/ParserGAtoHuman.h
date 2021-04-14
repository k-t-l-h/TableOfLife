#ifndef TABLEOFLIFE_PARSERGATOHUMAN_H
#define TABLEOFLIFE_PARSERGATOHUMAN_H


class Result;
class json;                                     //wrapper
class Solution;

class ParserGAtoHuman {
public:
    ParserGAtoHuman();
    ~ParserGAtoHuman();

private:
    Solution* GetReadable();
};


#endif //TABLEOFLIFE_PARSERGATOHUMAN_H
