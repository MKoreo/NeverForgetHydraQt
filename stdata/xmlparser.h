#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QDebug>
#include <QVector>

class XmlParser
{
public:
  // Only one instance of the XmlParser is required
  // So going for singleton design
  static XmlParser& instance();
  ~XmlParser();

private:
  // Disable constructor and copy operator
  XmlParser(){};
  XmlParser& operator=(const XmlParser& rhs) = delete;

public:
  static QVector<QVector<QString*>*>* READXML(const QString& path);
  static void WRITEXML(const QString& path, QVector<QVector<QString*>*>* records);
};

#endif // XMLPARSER_H
