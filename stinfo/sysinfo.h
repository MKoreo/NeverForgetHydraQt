#ifndef SYSINFO_H
#define SYSINFO_H


class SysInfo
{
public:
  static SysInfo& instance();
  virtual ~SysInfo();       // Destructor is virtual, so that derrived classes can also destroy this

  virtual void init() = 0; // The = 0 makes this class pure abstract
  virtual double cpuLoadAverage() = 0;
  virtual double memoryUsed() = 0;


protected:
  explicit SysInfo(); // Singleton: So only this class and derived can create

private:
  // Sinlgleton: private copy and assignment operator, so it's not possible
    SysInfo(const SysInfo& rhs) = delete;
    SysInfo& operator = (const SysInfo& rhs) = delete;
};

#endif // SYSINFO_H
