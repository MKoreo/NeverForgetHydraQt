#include <iostream>
#include <diarydao.h>

using namespace std;

int main()
{
  //QVector<QVector<QString*>*>* test = XmlParser::READXML("/home/thomas/Bureaublad/qt_records.xml");
  //XmlParser::WRITEXML("/home/thomas/Bureaublad/qt_records_writer.xml", XmlParser::READXML("/home/thomas/Bureaublad/qt_records.xml"));
  QVector<Record*>* test = DiaryDao::instance().read("/home/thomas/Bureaublad/qt_records.xml");
  QVector<Record*>* test2 = DiaryDao::instance().read("/home/thomas/Bureaublad/qt_records.xml");
  if (test == test2){
        cout << "DONE" << endl;
    }
  delete(test);
  delete(test2);
  return 0;
}
