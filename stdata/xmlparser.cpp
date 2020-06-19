#include "xmlparser.h"

XmlParser& XmlParser::instance()
{
  qDebug() << "XmlParser Instance accessed";
  static XmlParser singleton;
  return singleton;
}

XmlParser::~XmlParser(){
  qDebug() << "XmlParser Instance destroyed";
}

QVector<QVector<QString*>*>* XmlParser::READXML(const QString& path){
  qDebug() << "Attempting to read XML file @" << path;
  // We change the path to file
  QFile file(path);

  // Check if file is there and can be opened
  if(!file.open(QFile::ReadOnly | QFile::Text)){
      qDebug() << "Failed to read file due to error: " << file.errorString();
      exit(0);
    }

  // Create reader to parse XML
  QXmlStreamReader reader(&file);

  // Allocate return value on heap
  QVector<QVector<QString*>*>* records = new QVector<QVector<QString*>*>();

  // Parse the document
  if (reader.readNextStartElement()) {

      // First element has to be Diary
      if (reader.name() == "diary"){


          while(reader.readNextStartElement()){

              // For all records
              if(reader.name() == "record"){
                  // Reading can be any order, but writing and storing internal:
                  // addDate, recordDate, costCenter, project, subject, minutes;
                  QVector<QString*> rec;
                  QXmlStreamAttribute att;
                  foreach (att, reader.attributes()) {
                      if(att.name() == "addDate"){
                          rec.append(new QString(att.value().toString()));
                        }

                      if(att.name() == "recordDate"){
                          rec.append(new QString(att.value().toString()));
                        }

                      if(att.name() == "costCenter"){
                          rec.append(new QString(att.value().toString()));
                        }

                      if(att.name() == "project"){
                          rec.append(new QString(att.value().toString()));
                        }

                      if(att.name() == "subject"){
                          rec.append(new QString(att.value().toString()));
                        }

                      if(att.name() == "minutes"){
                          rec.append(new QString(att.value().toString()));
                        }
                    }

                  QVector<QString*>* record = new QVector<QString*>();


                  foreach(QString* str, rec){
                      record->append(str);
                      //qDebug(qPrintable(*str));
                    }
                  records->append(record);
                  qDebug() << "Record read: " << *record->at(0) << *record->at(1) << *record->at(2) << *record->at(3) << *record->at(4) << *record->at(5);
                  //qDebug(qPrintable(addDate + recordDate + costCenter + project + subject + minutes));

                  reader.readNextStartElement(); // Going up a level
                }
              else {
                  reader.skipCurrentElement();
                }
            }
        }
      else {
          reader.raiseError(QObject::tr("Incorrect file"));
        }
    }
  return records;
}

void XmlParser::WRITEXML(const QString& path, QVector<QVector<QString*>*>* records) {
  QFile file(path);
  if(!file.open(QFile::WriteOnly| QFile::Text)){
      qDebug() << "Cannot write file" << file.errorString();
      exit(0);
    }

  QXmlStreamWriter writer(&file);
  writer.setAutoFormatting(true);
  writer.writeStartDocument();
  writer.writeStartElement("diary");

  QVector<QString*>* rec;
  foreach(rec, *records) {
      writer.writeStartElement("record");
      int i = 0;
      writer.writeAttribute("addDate", *rec->at(i++));
      writer.writeAttribute("recordDate", *rec->at(i++));
      writer.writeAttribute("costCenter", *rec->at(i++));
      writer.writeAttribute("project", *rec->at(i++));
      writer.writeAttribute("subject", *rec->at(i++));
      writer.writeAttribute("minutes", *rec->at(i++));

      writer.writeEndElement(); // record
    }

  writer.writeEndElement(); // diary
  writer.writeEndDocument();
}
