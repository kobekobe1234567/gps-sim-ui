#ifndef RADIO_THREAD_H
#define RADIO_THREAD_H

#include <QThread>

class RadioThread : public QThread
{
    Q_OBJECT

    void run();

    bool stop;

signals:
    void error(int errorcode);

public:

enum{
    RADIO_NOERROR,
    RADIO_UNDERFLOW
};

    void set_stop(bool v);
};

#endif // RADIO_THREAD

