#ifndef SYSTEMFUNCT_H
#define SYSTEMFUNCT_H


class SystemFunct
{
// Singleton
protected:
    explicit SystemFunct();
private:
    SystemFunct(const SystemFunct& rhs) = delete;
    SystemFunct& operator = (const SystemFunct& rhs) = delete;

public:
    // Singleton instance
    static SystemFunct& instance();

    // Destructor is virtual, so that derrived classes can also destroy this
    virtual ~SystemFunct();

public:
    virtual bool enableStartup() = 0;
    virtual bool disableStartup() = 0;
    virtual bool checkStartup() = 0;

private:
    bool m_startupStatus = false;

};

#endif // SYSTEMFUNCT_H
