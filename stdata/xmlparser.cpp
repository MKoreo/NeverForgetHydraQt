#include "xmlparser.h"

XmlParser& XmlParser::instance()
{
    qDebug() << "-> SINGLETON USED: XmlParser Instance accessed";
    static XmlParser singleton;
    return singleton;
}

XmlParser::~XmlParser(){
    qDebug() << "-> SINGLETON DESTROYED: XmlParser Instance destroyed";
}

void XmlParser::READXML(const QString& path, QVector<QVector<QString>> &xml_output){
    qDebug() << "----- READING DIARY -----";
    qDebug() << "Path: " << path;

    // We change the path to file
    QFile file(path);

    // Check if file is there and can be opened
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "FAILURE: Could not read diary due to: " << file.errorString();
        exit(0);
    }

    // Create reader to parse XML
    QXmlStreamReader reader(&file);

    // Parse the document
    if (reader.readNextStartElement()) {

        // First element has to be Diary
        if (reader.name() == "diary"){

            while(reader.readNextStartElement()){
                // For all records
                if(reader.name() == "record"){
                    // Reading can be any order, but writing and storing internal:
                    // addDate, recordDate, costCenter, project, subject, minutes;
                    QVector<QString> rec;
                    QXmlStreamAttribute att;
                    foreach (att, reader.attributes()) {
                        if(att.name() == "addDate"){
                            rec.append(QString(att.value().toString()));
                        }

                        if(att.name() == "recordDate"){
                            rec.append(QString(att.value().toString()));
                        }

                        if(att.name() == "costCenter"){
                            rec.append(QString(att.value().toString()));
                        }

                        if(att.name() == "project"){
                            rec.append(QString(att.value().toString()));
                        }

                        if(att.name() == "subject"){
                            rec.append(QString(att.value().toString()));
                        }

                        if(att.name() == "minutes"){
                            rec.append(QString(att.value().toString()));
                        }
                    }

                    QVector<QString> record;
                    foreach(QString str, rec){
                        record.append(str);
                    }
                    xml_output.append(record);

                    qDebug() << "Record read: " << record.at(0) << record.at(1) << record.at(2) << record.at(3) << record.at(4) << record.at(5);

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
    reader.clear();
}

void XmlParser::WRITEXML(const QString& path, const QVector<QVector<QString>> &xml_input) {
    qDebug() << "----- WRITING DIARY -----";
    qDebug() << "Path: " << path;

    QFile file(path);
    if(!file.open(QFile::WriteOnly| QFile::Text)){
        qDebug() << "FAILURE: Could not write diary due to: " << file.errorString();
        exit(0);
    }

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("diary");

    QVector<QString> rec;
    if (!xml_input.empty()) {
        foreach(rec, xml_input) {
            writer.writeStartElement("record");
            int i = 0;
            writer.writeAttribute("addDate", rec.at(i++));
            writer.writeAttribute("recordDate", rec.at(i++));
            writer.writeAttribute("costCenter", rec.at(i++));
            writer.writeAttribute("project", rec.at(i++));
            writer.writeAttribute("subject", rec.at(i++));
            writer.writeAttribute("minutes", rec.at(i++));

            writer.writeEndElement(); // record
        }
    }
    writer.writeEndElement(); // diary
    writer.writeEndDocument();
}

void XmlParser::WRITESETTINGS(const QVector<QVector<QString>> &xml_input) {
    QFile file("./settings.ini");

    qDebug() << "----- WRITING SETTEING -----";
    qDebug() << "Path: " << "./settings.ini";

    if(!file.open(QFile::WriteOnly| QFile::Text)){
        qDebug() << "FAILURE: Could not write settings due to:" << file.errorString();
        exit(0);
    }

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("settings");

    QVector<QString> setting;
    if (!xml_input.empty()) {
        foreach(setting, xml_input) {
            writer.writeAttribute(setting.at(0), setting.at(1));
        }
    }

    writer.writeEndElement(); // diary
    writer.writeEndDocument();
}

void XmlParser::READSETTINGS(QVector<QVector<QString>> &xml_output){
    qDebug() << "----- LOADING SETTINGS -----";
    qDebug() << "Path: " << "./settings.ini";

    // We change the path to file
    QFile file("./settings.ini");

    // Check if file is there and can be opened
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "FAILURE: Could not load settings due to: " << file.errorString();
        exit(0);
    }

    // Create reader to parse XML
    QXmlStreamReader reader(&file);

    // Parse the document
    if (reader.readNextStartElement()) {

        // First element has to be settings
        if (reader.name() == "settings"){


            // For all settings

            QXmlStreamAttribute att;
            foreach (att, reader.attributes()) {
                QVector<QString> setting;
                setting.append(att.name().toString());
                setting.append(att.value().toString());
                qDebug() << "Setting read: " << setting.at(0) << " : " << setting.at(1);
                xml_output.append(setting);
            }

            reader.readNextStartElement(); // Going up a level
        }
    }
    else {
        reader.raiseError(QObject::tr("Incorrect file"));
    }
    reader.clear();
}
