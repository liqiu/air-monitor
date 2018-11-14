#include "serial.h"
#include <stdio.h>
#include <unistd.h>

#include <QObject>
#include <QTimer>
#include <QVariant>

class MyClass : public QObject
{
    Q_OBJECT
public:
    MyClass(QObject* parent = 0) : QObject(parent)
    {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateData()));
        timer->start(900);

        rootObject = this->parent();
        txtPM1p0 = rootObject->findChild<QObject *>("txtPM1p0");
        txtPM2p5 = rootObject->findChild<QObject *>("txtPM2p5");
        txtPM10 = rootObject->findChild<QObject *>("txtPM10");

        fd = open_port();
    }

    virtual ~MyClass()
    {
        close(fd);
        delete timer;
    }

public slots:

    void updateData()
    {
        int pm1p0, pm2p5, pm10;
        char message[64];
        read_port(fd);
        if (!parse_data(&pm1p0, &pm2p5, &pm10)) {
            sprintf(message, "PM1.0: %i PM2.5: %i PM10: %i", pm1p0, pm2p5, pm10);
            txtPM1p0->setProperty("text", pm1p0);
            txtPM2p5->setProperty("text", pm2p5);
            txtPM10->setProperty("text", pm10);
        }
    }

private:
    QObject* rootObject;
    QObject* txtPM1p0;
    QObject* txtPM2p5;
    QObject* txtPM10;
    QTimer* timer;
    int fd;
};


