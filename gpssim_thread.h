#ifndef GPSSIM_THREAD_H
#define GPSSIM_THREAD_H

#include <QThread>

class GpsSimThread : public QThread
{
    Q_OBJECT

    void run();

    bool stop;

signals:
    void error(int errorcode);

public:

enum{
    FILE_CANNOT_OPEN,
    FILE_CONTENT_ERROR
};

    bool useCurrentTime;

    bool holdLocation;

    char umfile[255];

    char navfile[255];

    int nmeaGGA;

    void set_stop(bool v);

    GpsSimThread();
};

#endif // GPSSIM_THREAD_H

