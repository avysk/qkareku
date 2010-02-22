#ifndef __MIXER_H_
#define __MIXER_H_
#include <math.h>
#include <QObject>
#include <QIODevice>

const int SYSTEM_FREQ = 44100;

class Mixer : public QIODevice
{
        Q_OBJECT
        public:
                Mixer(QObject *parent);
                ~Mixer();

                void start();
                void stop();

                qint64 readData(char *data, qint64 maxlen);
                qint64 writeData(const char *data, qint64 len);

        public slots:
                void mixIn(int step, char *data, int len);
        private:
                void putShort(char *t, short value);
                unsigned int buflen;
                char *buffer;
                int pos;
};
#endif
