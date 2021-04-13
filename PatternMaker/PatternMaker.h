#ifndef TABLEOFLIFE_PATTERNMAKER_H
#define TABLEOFLIFE_PATTERNMAKER_H

class json;
class htmlFile;

class PatternMaker {
public:
    htmlFile *GeneratePage();
private:
    json *ReadableData;
};


#endif //TABLEOFLIFE_PATTERNMAKER_H
