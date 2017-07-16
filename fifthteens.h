#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QDir>
#include <QTimer>
#include <time.h>
#include <iostream>

#ifndef __FIFTHTEENS_H__
#define __FIFTHTEENS_H__

using namespace std;

class FifthTeens : public QWidget
{
    Q_OBJECT
    public:
	FifthTeens(QWidget *parent=0, int num=2) : QWidget(parent) {
	    setWindowTitle("Fifthteens");
	    srand(time(NULL));
        cout << "before loadImg" << endl;
        loadImg();
        cout << "after loadImg" << endl;
	    MAX_NUM = num;
	    max_value = MAX_NUM*MAX_NUM;
	    misplace = -1;
	    BRICK_SIZE = img.width()/MAX_NUM;
	    setFixedSize(img.width(),img.height());
	    mas = new int [max_value];
	    setFixedSize(img.width(),img.height());
        cout << "before newgame" << endl;
	    new_game();
	}

	void new_game() {
	    for (int i=0;i<MAX_NUM;i++)
	    for (int j=0;j<MAX_NUM;j++)
		mas[i*MAX_NUM+j]=i*MAX_NUM+j+1;
	    hr = hc = MAX_NUM-1;
	    shuffle();
	    checkEnd();
	}
	
	void loadImg() {
        //const char *img_path="/usr/share/wallpapers/1024x768/";
        QString img_path=QDir::currentPath();
        cout << "img_path = " << img_path.toAscii().data() << endl;
        QDir dir(img_path.toAscii().constData(), "*.jpg");
        img = QImage(img_path+"/"+
            dir.entryList()[rand()%dir.entryList().count()])
			.copy(0,0,768,768);
        cout << "img.width=" << img.width() << "  img.height=" << img.height() << endl;
	    return;
	}
	
	void shuffle()
	{
	    for (int i=0;i<1000;i++) {
		if (rand()%2) moveLine(hr,rand()%MAX_NUM);
		moveLine(rand()%MAX_NUM,hc);
	    }
	    return;
	}
	
	void moveLine(int r, int c)
	{
	    int i,j,sign;
	    
	    if (mas[r*MAX_NUM+c]==max_value) return;
	    for (i=0;i<MAX_NUM;i++)
		if (mas[i*MAX_NUM+c]==max_value) break;
	    if (hc==c) {
		i = hr;
		if (i>r) sign=-1; else sign=1;
		j=i;
		while(j!=r) {
		    mas[j*MAX_NUM+c]=mas[(j+sign)*MAX_NUM+c];
		    j+=sign;
		}
		    mas[j*MAX_NUM+c]=max_value;
		    hr = j;
		    repaint();
		    return;
	    }
	    if (hr==r) {
		i = hc;
		if (i>c) sign=-1; else sign=1;
		j=i;
		while(j!=c) {
		    mas[r*MAX_NUM+j]=mas[r*MAX_NUM+j+sign];
		    j+=sign;
		}
		    mas[r*MAX_NUM+j]=max_value;
		    hc = j;
		    repaint();
		    return;
	    }
	    return;
	}
	
	
	bool checkEnd()
	{
	    int j;
	    bool result;
	    for (j=0;j<max_value;j++)
		if (mas[j]!=j+1) break;
	    if (j==max_value) return true;
	    misplace = j+1;
	    return false;
	}
    protected:
	int MAX_NUM;
	int BRICK_SIZE;
	QImage img;
	QTimer *tmr;
	int hr,hc;
	int misplace;
	int max_value;
	void paintEvent(QPaintEvent *ev);
	void mousePressEvent(QMouseEvent *ev);
	void keyPressEvent(QKeyEvent *ev);
	int *mas;
};

#endif
