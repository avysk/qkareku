#ifndef BLJAM_H
#define BLJAM_H

#include <QBrush>
#include <QPen>
#include <QWidget>

class Bljam : public QWidget
{
        Q_OBJECT
        Q_PROPERTY(int hue READ getHue WRITE setHue)
        Q_PROPERTY(int saturation READ getSaturation WRITE setSaturation)
        Q_PROPERTY(int value READ getValue WRITE setValue)
        Q_PROPERTY(int alpha READ getAlpha WRITE setAlpha)

        public:

                Bljam(QWidget *parent = 0);

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
                void play(void);

        protected:
                void paintEvent(QPaintEvent *event);
                void mouseReleaseEvent(QMouseEvent *event);

        private:
                bool state;
                int s_hue, s_saturation, s_value, s_alpha;

};

#endif
