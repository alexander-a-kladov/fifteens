#include <qapplication.h>
#include "fifteens.h"

int main(int argc, char **argv)
{
    int num=4;
    QApplication app(argc,argv);
    if (argc>1) num=atoi(argv[1]);
    if (num<3) num=16;
    Fifteens w(NULL,num);
    w.show();
    return app.exec();
}
