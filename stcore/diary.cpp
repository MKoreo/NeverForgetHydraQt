#include "diary.h"

Diary& Diary::instance()
{
  // Singleton declared in static memory
  // Will be same instance, everytime method is called
  static Diary singleton;
  return singleton;
}

Diary::~Diary(){
  // Perhaps save?
  saveDiary();
}


void Diary::newDiary(const QString path) {
  m_path = path;

  if(m_records != nullptr) {
      delete(m_records);
  }
  if(m_deletedRecords != nullptr) {
      delete(m_deletedRecords);
  }

  m_records = new QVector<Record*>();
  m_deletedRecords = new QVector<Record*>();
}
bool Diary::loadDiary(const QString path){
  newDiary(path);

  return false;
}

bool Diary::saveDiary(){
  return false;
}
