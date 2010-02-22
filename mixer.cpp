#include <QAudioOutput>
#include <QAudioDeviceInfo>
#include "beeper.h"
#include "blip.h"

Mixer::Mixer(double f, QObject *parent)
        : QIODevice(parent), frequency(f)
{
        buflen = (unsigned int)(Blip::get().duration * SYSTEM_FREQ) * 2 * Blip::get().steps;
        buffer = new char[buflen];
        pos = 0;
}

Mixer::~Mixer()
{
        delete[] buffer;
}

void Mixer::start()
{
        open(QIODevice::ReadOnly);
}

void Mixer::stop()
{
        close();
}

void Mixer::putShort(char *t, short v)
{
        *(unsigned char *)(t++) = (unsigned char)(v & 0xFF);
        *(unsigned char *)(t) = (unsigned char)((v >> 8) & 0xFF);
}

short Mixer::getShort(char *t)
{
       return (short)((unsigned char *)t + (short)((unsigned char *)(t+1) << 8));
}


qint64 Mixer::readData(char *data, qint64 maxlen)
{
        int len = maxlen;

        qint64 tail = buflen - pos;

        if (len > 16384)
                len = 16384;

        if (len < tail) {
                memcpy(data, buffer + pos, len);
                pos += len;
                return len;
        } else {
                memcpy(data, buffer + pos, tail);
                pos = 0;
                return tail;
        }

}

qint64 Mixer::writeData(const char *data, qint64 len)
{
        Q_UNUSED(data);
        Q_UNUSED(len);

        return 0;
}

void Mixer::mixIn(step, char *data, int len) {
         mine;
        int their;
        int result;
        int cur = 0;
        int pos = (unsigned int)(Blip::get().duration * SYSTEM_FREQ) * 2 * step;
        while (len > 0) {
                mine = 32768 + getShort(buffer + pos);
                their = 32768 + getShort(data + cur);
                if (mine < 32768 and their < 32768)
                        result = mine * their / 32768
                else
                        result = 2 * (mine + their) - mine * their / 32768 - 65536;
                result = result - 32768;
                putShort(buffer + pos, (short)result);
                len -= 2;
                cur += 2;
                pos += 2;
                if pos = buflen
                        pos = 0;
        }
}
