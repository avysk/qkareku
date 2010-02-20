#include <QAudioOutput>
#include <QAudioDeviceInfo>
#include "beeper.h"
#include "blip.h"

Beeper::Beeper(double f, QObject *parent)
        : QIODevice(parent), frequency(f)
{
        // FIXME: reallocate if duration changes
        buffer = new char[(unsigned int)(Blip::get().duration * SYSTEM_FREQ) * 2];
        t = buffer;
        len = fillData(t, Blip::get().duration);
        pos = 0;
        total = len;
}

Beeper::~Beeper()
{
        delete[] buffer;
}

void Beeper::start()
{
        open(QIODevice::ReadOnly);
}

void Beeper::stop()
{
        close();
}

void Beeper::putShort(char *t, short v)
{
        *(unsigned char *)(t++) = (unsigned char)(v & 0xFF);
        *(unsigned char *)(t) = (unsigned char)((v >> 8) & 0xFF);
}

int Beeper::fillData(char *start, double duration)
{
        int i, len = 0;
        int v;
        double p;
        double adsr;
        for (i = 0; i < duration * SYSTEM_FREQ; i++) {
                adsr = Blip::get().ADSR(i / (duration * SYSTEM_FREQ));
                //v = 2.0 * M_PI * i * frequency / SYSTEM_FREQ;
                //v = 0.8 * sin(v) + 0.2 * sin(2 * v);
                //v = (int)(adsr * 32767.0 * v);
                p = 2.0*M_PI*((double)(i))*frequency/SYSTEM_FREQ;
                p = sin(p);
                v = (short)(adsr*32767.0*p);
                // v = (int)(adsr*32767.0*sin(2.0*M_PI*((double)(i))*frequency/SYSTEM_FREQ));
                putShort(start, v);
                start += 2;
                len += 2;
        }
        return len;
}

qint64 Beeper::readData(char *data, qint64 maxlen)
{
        int len = maxlen;
        if (len > 16384)
                len = 16384;

        if (len < (Blip::get().duration * SYSTEM_FREQ * 2) - pos) {
                memcpy(data, t+pos, len);
                pos += len;
                return len;
        } else {
               //qint64 left = (DURATION*SYSTEM_FREQ/1000*2) - pos;
               //memcpy(data, t+pos, left);
               //pos = 0;
               //return left;
               return 0;
        }
}

qint64 Beeper::writeData(const char *data, qint64 len)
{
        Q_UNUSED(data);
        Q_UNUSED(len);

        return 0;
}
