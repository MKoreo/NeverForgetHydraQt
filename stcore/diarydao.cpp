#include "diarydao.h"

DiaryDao& DiaryDao::instance()
{
    static DiaryDao singleton;
    return singleton;
}

DiaryDao::~DiaryDao(){

}

void DiaryDao::read(const QString& path, QVector<Record*> &records) {
    records = QVector<Record*>();

    QVector<QVector<QString>> xml_output;
    XmlParser::instance().READXML(path, xml_output);

    QVector<QString> vec;
    foreach(vec, xml_output){
        records.append(new Record(std::move(vec.at(0)),std::move(vec.at(1)),std::move(vec.at(2)),std::move(vec.at(3)),std::move(vec.at(4)),std::move(vec.at(5))));
    }
}

void DiaryDao::write(const QString &path, const QVector<Record*> &records){
    QVector<QVector<QString>> xml_input = QVector<QVector<QString>>();
    //xml_input.append({"","","","","","",""});
    if(records.empty() == false){
        foreach(Record *rec, records){
            xml_input.append({rec->creationDate().toString("yyyy-MM-dd"), rec->recordDate().toString("yyyy-MM-dd"),rec->costCenter(),rec->project(),rec->subject(), QString::number(rec->minutes())});
        }
            XmlParser::instance().WRITEXML(path, xml_input);
    }



}
