#include <QAudioOutput>
#include <QAudioDeviceInfo>
#include "beeper.h"
#include "blip.h"

Beeper::Beeper(double f, QObject *parent)
        : QIODevice(parent), frequency(f)
{
        // FIXME: reallocate if duration changes
        buflen = (unsigned int)(Blip::get().duration * SYSTEM_FREQ) * 2 * 4;
        buffer = new char[buflen];

        fillData(buffer, Blip::get().duration);
        pos = buflen;
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

void Beeper::fillData(char *start, double duration)
{
        int i, len = 0;
        int v;
        double p;
        double adsr;
        double phase = qrand()/RAND_MAX * 2 * M_PI;
        for (i = 0; i < duration * SYSTEM_FREQ; i++) {
                adsr = Blip::get().ADSR(i / (duration * SYSTEM_FREQ));
                p = 2.0*M_PI*((double)(i))*frequency/SYSTEM_FREQ;
                p = p + phase;
                p = sin(p);
                v = (short)(adsr*32767.0*p);
                putShort(start, v);
                v /= Blip::get().echoDecay;
                putShort(start + buflen/4, v);
                v /= Blip::get().echoDecay;
                putShort(start + 2*buflen/4, v);
                v /= Blip::get().echoDecay;
                putShort(start + 3*buflen/4, v);
                start += 2;
                len += 2;
        }
}

qint64 Beeper::readData(char *data, qint64 maxlen)
{
        int len = maxlen;

        qint64 tail = buflen - pos;
        if (tail <= 0) return 0;

        if (len > 16384)
                len = 16384;

        if (len < tail) {
                memcpy(data, buffer + pos, len);
                pos += len;
                return len;
        } else {
                memcpy(data, buffer + pos, tail);
                pos += tail;
                return tail;
        }

        //if (len < (Blip::get().duration * SYSTEM_FREQ * 2) - pos) {
        //        memcpy(data, buffer + pos, len);
        //        pos += len;
        //        return len;
        //} else {
        //       qint64 left = (Blip::get().duration * SYSTEM_FREQ * 2) - pos;
        //       memcpy(data, buffer + pos, left);
               //pos = 0;
        //       return left;
               //return 0;
        //}
}

void Beeper::restart()
{
        pos = 0;
}

qint64 Beeper::writeData(const char *data, qint64 len)
{
        Q_UNUSED(data);
        Q_UNUSED(len);

        return 0;
}
