#include <QApplication>
#include "musicBox.h"

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);
        app.setApplicationName("QKareku");

        MusicBox mb;
        mb.show();

        return app.exec();
}
