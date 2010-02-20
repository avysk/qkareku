#ifndef __BLJAM_H_
#define __BLJAM_H_

#include <QWidget>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include "beeper.h"

class Bljam : public QWidget
{
        Q_OBJECT
        Q_PROPERTY(int hue READ getHue WRITE setHue)
        Q_PROPERTY(int saturation READ getSaturation WRITE setSaturation)
        Q_PROPERTY(int value READ getValue WRITE setValue)
        Q_PROPERTY(int alpha READ getAlpha WRITE setAlpha)

        public:

                Bljam(double freq, int c, QWidget *parent = 0);
                ~Bljam();

                QSize minimumSizeHint() const;
                QSize sizeHint() const;

                int getHue(void) const;
                void setHue(int);
                int getSaturation(void) const;
                void setSaturation(int);
                int getValue(void) const;
                void setValue(int);
                int getAlpha(void) const;
                void setAlpha(int);
        public slots:
                void play(int);

        protected:
                void paintEvent(QPaintEvent *event);
                void mouseReleaseEvent(QMouseEvent *event);

        private:
                double frequency;
                int column;
                int s_hue, s_saturation, s_value, s_alpha;
                bool state;

                Beeper *beep;
                QAudioOutput *audioOutput;
                QAudioFormat settings;

};

#endif
