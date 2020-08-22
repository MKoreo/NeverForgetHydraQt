#include "stcore.h"
#include "xmlparser.h"


StCore& StCore::instance()
{
    static StCore singleton;
    return singleton;
}

StCore::~StCore(){

}

QVector<QVector<QString>> StCore::loadSettings(){
    QVector<QVector<QString>> output;
    XmlParser::instance().READSETTINGS(output);
    return output;
}

void StCore::writeSettings(QVector<QVector<QString>> input){
    XmlParser::instance().WRITESETTINGS(input);
}
