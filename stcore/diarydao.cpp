#include "diarydao.h"


DiaryDao& DiaryDao::instance()
{
  static DiaryDao singleton;
  return singleton;
}

DiaryDao::~DiaryDao(){

}

QVector<Record*>* DiaryDao::read(const QString& path) {
  QVector<Record*>* readRecords = new QVector<Record*>();

  QVector<QVector<QString*>*>* xml_output = XmlParser::instance().READXML(path);

  QVector<QString*>* vec;
  foreach(vec, *xml_output){
      readRecords->append(new Record(*vec->at(0),*vec->at(1),*vec->at(2),*vec->at(3),*vec->at(4),*vec->at(5)));
      foreach(QString* str, *vec){
          delete(str);
        }
      delete(vec);
  }
  delete(xml_output);

  return readRecords;
}
