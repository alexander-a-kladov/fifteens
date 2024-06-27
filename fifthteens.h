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

const int IMG_SIZE=768;

class FifthTeens : public QWidget
{
    Q_OBJECT
    public:
	FifthTeens(QWidget *parent=0, int num=2) : QWidget(parent) {
	    setWindowTitle("Fifteens (DHR)");
	    srand(time(NULL));
	    MAX_NUM = num;
	    max_value = MAX_NUM*MAX_NUM;
	    BRICK_SIZE = IMG_SIZE/MAX_NUM;
	    setFixedSize(IMG_SIZE,IMG_SIZE);
	    mas = new int [max_value];
        digits_show = false;
        hint_show = false;
	    new_game();
	}

	void new_game() {
		misplace = -1;
		loadImg();
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
        QDir dir(img_path.toLocal8Bit().constData(), "*.jpeg");
        img = QImage(img_path+"/"+
            dir.entryList()[rand()%dir.entryList().count()])
			.copy(0,0,IMG_SIZE,IMG_SIZE);
	    return;
	}
	
	void shuffle()
	{
	    for (int i=0;i<100;i++) {
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
	    checkState();
	    return false;
	}

	bool checkState() {
		int offset = 0;
		for (int offset=0;offset<MAX_NUM-2;++offset) {
		for (int j=offset;j<MAX_NUM;++j) {
			int index = offset*MAX_NUM + j;
			if (mas[index]!=index+1) {misplace = index + 1;return false;}
		}
		if (offset==MAX_NUM-3) {misplace = -1; return false;}
		for (int i=offset+1;i<MAX_NUM;++i) {
			int index = i*MAX_NUM + offset;
			if (mas[index]!=index+1) {misplace = index + 1;return false;}
		}
		}
		return true;
	}
    protected:
	int MAX_NUM;
	int BRICK_SIZE;
	QImage img;
	QTimer *tmr;
	int hr,hc;
	int misplace;
	int max_value;
	bool digits_show;
	bool hint_show;
	void paintEvent(QPaintEvent *ev);
	void mousePressEvent(QMouseEvent *ev);
	void keyPressEvent(QKeyEvent *ev);
	int *mas;
};

#endif
