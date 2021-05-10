#ifndef TABLEOFLIFE_PARSERGATOHUMAN_H
#define TABLEOFLIFE_PARSERGATOHUMAN_H

class json;

class ParserToHuman {
public:
    ParserToHuman() = default;
    ~ParserToHuman() = default;

    std::string& GetReadable(const std::vector<int>&);
private:

    ParserToHuman(const ParserToHuman &a) = delete;
    ParserToHuman& operator=(const ParserToHuman &a) = delete;

};


#endif //TABLEOFLIFE_PARSERGATOHUMAN_H
