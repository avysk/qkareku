#include <QtGui>
#include <QtCore>
#include <QPropertyAnimation>

#include "bljam.h"

Bljam::Bljam(double freq, QWidget *parent)
        : QWidget(parent), frequency(freq)
{
        setBackgroundRole(QPalette::Shadow);
        setAutoFillBackground(true);
        state = false;
        setHue(120);
        setSaturation(255);
        setValue(160);
        setAlpha(0);

        settings.setFrequency(SYSTEM_FREQ);
        settings.setChannels(1);
        settings.setSampleSize(16);
        settings.setCodec("audio/pcm");
        settings.setByteOrder(QAudioFormat::LittleEndian);
        settings.setSampleType(QAudioFormat::SignedInt);

        QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
        if (!info.isFormatSupported(settings)) {
                qWarning()<<"default format not supported try to use nearest";
                settings = info.nearestFormat(settings);
        }

        audioOutput = new QAudioOutput(settings, this);
        beep = 0;

}

Bljam::~Bljam()
{
        audioOutput->stop();
        if (beep) {
                delete beep;
        }
        delete audioOutput;
}

QSize Bljam::minimumSizeHint() const
{
        return QSize(50, 50);
}

QSize Bljam::sizeHint() const
{
        return QSize(50, 50);
}

void Bljam::play()
{
        QPropertyAnimation *animation = new QPropertyAnimation(this, "value");
        animation->setDuration(200);
        animation->setStartValue(255);
        animation->setKeyValueAt(0.8, 100);
        animation->setEndValue(160);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
        //if (state)
        //        audioOutput->start(beep);
}

void Bljam::paintEvent(QPaintEvent *)
{
        QPainter painter(this);
        painter.setPen(Qt::NoPen);
        QColor col = QColor::fromHsv(s_hue, s_saturation, s_value, s_alpha);
        QBrush brush(col);
        painter.setBrush(brush);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.drawEllipse(5,5,40,40);
}

void Bljam::mouseReleaseEvent(QMouseEvent *)
{
        int start;
        int end;
        if (state) {
                start = 255;
                end = 0;
                if (beep) {
                        audioOutput->stop();
                        beep->stop();
                        delete beep;
                        beep = 0;
                }
        } else {
                start = 0;
                end = 255;
                beep = new Beeper(frequency, this);
                beep->start();
                audioOutput->start(beep);
        }
        state = not state;
        QPropertyAnimation *animation = new QPropertyAnimation(this, "alpha");
        animation->setDuration(200);
        animation->setStartValue(start);
        animation->setEndValue(end);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
}

int Bljam::getHue() const { return s_hue; }
void Bljam::setHue(int h) { s_hue = h; update(); }
int Bljam::getSaturation() const { return s_saturation; }
void Bljam::setSaturation(int s) { s_saturation = s; update(); }
int Bljam::getValue() const { return s_value; }
void Bljam::setValue(int v) { s_value = v; update(); }
int Bljam::getAlpha() const { return s_alpha; }
void Bljam::setAlpha(int a) { s_alpha = a; update(); }
