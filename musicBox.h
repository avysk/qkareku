#ifndef __MUSICBOX_H_
#define __MUSICBOX_H_

#include <QObject>
#include <QMainWindow>

#include "bljam.h"
#include "blip.h"

class MusicBox : public QMainWindow
{
        Q_OBJECT
        public:
                MusicBox();
                ~MusicBox();
        private:
                QTimer *timer;
                Bljam *bljams[8][16];
};

#endif
