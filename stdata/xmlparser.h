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
  static void READXML(const QString& path, QVector<QVector<QString>> &xml_output);
  static void WRITEXML(const QString &path, const QVector<QVector<QString>> &xml_input);
  static void READSETTINGS(QVector<QVector<QString>> &xml_output);
  static void WRITESETTINGS(const QVector<QVector<QString>> &xml_input);
};

#endif // XMLPARSER_H
