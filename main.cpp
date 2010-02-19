#include <QApplication>
#include <QtGui>
#include <QPushButton>
#include <bljam.h>

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);
        QWidget window;
        window.resize(300,300);
        window.show();

        QGridLayout *layout = new QGridLayout(&window);

        Bljam *b = new Bljam(&window);
        QPushButton *btn = new QPushButton(&window);

        layout->setColumnStretch(1,1);
        layout->addWidget(b,0,0);
        layout->addWidget(btn,0,1);

        QObject::connect(btn, SIGNAL(clicked()), b, SLOT(play()));
        return app.exec();
}
