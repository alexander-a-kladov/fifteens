#include "fifthteens.h"
#include <QPainter>
#include <QMessageBox>

void FifthTeens::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    static int flash=0;
    p.setFont(QFont("Arial",(24*BRICK_SIZE)/100));
    p.setPen(Qt::white);
    if (checkEnd()) p.drawImage(0,0,img);
    else {
    for (int i=0;i<MAX_NUM;i++)
    for (int j=0;j<MAX_NUM;j++) {
	if (mas[i*MAX_NUM+j]!=max_value) {
	p.drawImage(j*BRICK_SIZE,i*BRICK_SIZE,img,
		    BRICK_SIZE*((mas[i*MAX_NUM+j]-1)%MAX_NUM),
		    BRICK_SIZE*((mas[i*MAX_NUM+j]-1)/MAX_NUM),
		    BRICK_SIZE,BRICK_SIZE);
	/*p.drawText(j*BRICK_SIZE,i*BRICK_SIZE,
			    BRICK_SIZE,BRICK_SIZE,Qt::AlignCenter,
			    QString("%1").arg(mas[i*MAX_NUM+j]));*/
	//cout << "misplace = " << misplace << endl;
	if (misplace==mas[i*MAX_NUM+j]) {
		p.drawRect(j*BRICK_SIZE+2,i*BRICK_SIZE+2,BRICK_SIZE-4,BRICK_SIZE-4);
		p.drawRect(j*BRICK_SIZE+4,i*BRICK_SIZE+4,BRICK_SIZE-8,BRICK_SIZE-8);
	    }
	}
	else {
	    p.save();
	    p.setBrush(Qt::white);
	    p.drawRect(j*BRICK_SIZE+2,i*BRICK_SIZE+2,BRICK_SIZE-4,BRICK_SIZE-4);
	    p.restore();
	}
	}
	
    }
    flash++;flash%=2;
    return;
}

void FifthTeens::mousePressEvent(QMouseEvent *ev)
{
    moveLine(ev->y()/BRICK_SIZE,ev->x()/BRICK_SIZE);
    if (checkEnd()) QMessageBox::information(this,"Congratulation", "You win");
    return;
}

void FifthTeens::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key()) {
	case Qt::Key_Left: {
		if (hc+1<MAX_NUM)
		moveLine(hr,hc+1);
		}
	    break;
	case Qt::Key_Right:
		if (hc-1>=0)
		moveLine(hr,hc-1);
	    break;
	case Qt::Key_Up:
		if (hr+1<MAX_NUM)
		moveLine(hr+1,hc);
	    break;
	case Qt::Key_Down:
		if (hr-1>=0)
		moveLine(hr-1,hc);
	    break;
    }
    if (checkEnd()) QMessageBox::information(this,"Congratulation", "You win");
    return;
}
