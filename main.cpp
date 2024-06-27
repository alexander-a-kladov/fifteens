#include <qapplication.h>
#include "fifthteens.h"

int main(int argc, char **argv)
{
    int num=4;
    QApplication app(argc,argv);
    if (argc>1) num=atoi(argv[1]);
    if (num<3) num=16;
    FifthTeens w(NULL,num);
    w.show();
    return app.exec();
}
