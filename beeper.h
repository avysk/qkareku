#ifndef __BEEPER_H_
#define __BEEPER_H_
#include <math.h>
#include <QObject>
#include <QIODevice>

// const int BUFFER_SIZE = 32768;
const int SYSTEM_FREQ = 44100;

class Beeper : public QIODevice
{
        Q_OBJECT
        public:
                Beeper(double freq, QObject *parent);
                ~Beeper();

                void start();
                void stop();
                void restart();

                qint64 readData(char *data, qint64 maxlen);
                qint64 writeData(const char *data, qint64 len);

        private:
                void putShort(char *t, short value);
                void fillData(char *start, double duration);
                double frequency;
                unsigned int buflen;
                char *buffer;
                int pos;
};
#endif
