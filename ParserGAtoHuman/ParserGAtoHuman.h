#ifndef TABLEOFLIFE_PARSERGATOHUMAN_H
#define TABLEOFLIFE_PARSERGATOHUMAN_H

class json;

class ParserGAtoHuman {
public:
    ParserGAtoHuman(int **);
    ~ParserGAtoHuman();

    json* GetReadable();
private:

    ParserGAtoHuman() = delete;
    ParserGAtoHuman(const ParserGAtoHuman &a) = delete;
    ParserGAtoHuman& operator=(const ParserGAtoHuman &a) = delete;

    int **unreadable;
};


#endif //TABLEOFLIFE_PARSERGATOHUMAN_H
