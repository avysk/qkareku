#include <QGridLayout>
#include <QTimer>
#include "musicBox.h"

MusicBox::MusicBox()
{
        QWidget *window = new QWidget;
        window->resize(800, 400);

        QGridLayout *layout = new QGridLayout();
        layout->setHorizontalSpacing(0);
        layout->setVerticalSpacing(0);

        timer = new QTimer(window);

        double semi = pow(2.0, 1.0/12.0);
        double freq = 440.0;
        for (int r = 0; r < 8; r++) {
                for (int c = 0; c < 16; c++) {
                        bljams[r][c] = new Bljam(freq, window);
                        layout->addWidget(bljams[r][c], r, c);
                        QObject::connect(timer, SIGNAL(timeout()), bljams[r][c], SLOT(play()));
                }
                freq *= semi;
        }

        window->setLayout(layout);
        setCentralWidget(window);
        window->show();

        Blip::get().duration = 0.2;
        timer->start(1500);
}

MusicBox::~MusicBox()
{
        timer->stop();
        delete timer;
        for (int r = 0; r < 8; r++)
                for (int c = 0; c < 8; c++)
                        delete bljams[r][c];
}
