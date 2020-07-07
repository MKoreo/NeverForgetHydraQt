#include <iostream>
#include <diary.h>

using namespace std;
#include <chrono>


// new Record(QDate(2020, 06, 19), QDate(2020, 06, 19), QString("R&D"), QString("NGS-D440"), QString("HDMI check"), 50)

int main()
{
  cout << "This is a testrun..." << std::endl;
  cout << "Let's first attempt to read XML..." << std::endl;
  //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  Diary::instance().loadDiary("/home/thomas/Bureaublad/qt_records_write.xml");
  //QVector<Record*> test = Diary::instance().getRecordsByDates(QDate(2020, 05, 14), QDate(2020, 05, 15));
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  Diary::instance().sort();
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  Diary::instance().saveDiary("/home/thomas/Bureaublad/qt_records_writee.xml");


  //std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
 std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
  return 0;
}
