#include <QGridLayout>
#include <QTimer>
#include "musicBox.h"
#include "blip.h"

MusicBox::MusicBox()
{
        QWidget *window = new QWidget;
        window->resize(800, 400);

        QGridLayout *layout = new QGridLayout();
        layout->setHorizontalSpacing(0);
        layout->setVerticalSpacing(0);

        timer = new QTimer(window);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(play()));

        for (int r = 0; r < 8; r++) {
                for (int c = 0; c < Blip::get().steps; c++) {
                        bljams[r][c] = new Bljam(Blip::get().freq[r], c, window);
                        QObject::connect(this, SIGNAL(playColumn(int)), bljams[r][c], SLOT(play(int)));
                        layout->addWidget(bljams[r][c], r, c);
                }
        }

        window->setLayout(layout);
        setCentralWidget(window);
        window->show();

        Blip::get().duration = 0.3;
        playingColumn = 0;
        timer->start(Blip::get().delay);
}

MusicBox::~MusicBox()
{
        timer->stop();
        delete timer;
        for (int r = 0; r < 8; r++)
                for (int c = 0; c < 8; c++)
                        delete bljams[r][c];
}

void MusicBox::play()
{
        emit playColumn(playingColumn++);
        if (playingColumn > 15)
                playingColumn = 0;
}
