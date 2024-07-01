#include "fifteens.h"
#include <QPainter>
#include <QMessageBox>
#include <math.h>

void Fifteens::paintEvent(QPaintEvent *ev)
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
		p.drawImage(QPointF(j*BRICK_SIZE,i*BRICK_SIZE),img.copy(
		    BRICK_SIZE*((mas[i*MAX_NUM+j]-1)%MAX_NUM),
		    BRICK_SIZE*((mas[i*MAX_NUM+j]-1)/MAX_NUM),
		    ceil(BRICK_SIZE),ceil(BRICK_SIZE)));
		if (digits_show) {
			p.drawText(j*BRICK_SIZE,i*BRICK_SIZE,
			    BRICK_SIZE,BRICK_SIZE,Qt::AlignCenter,
			    QString("%1").arg(mas[i*MAX_NUM+j]));
		}
		if (hint_show) {
			if (misplace==mas[i*MAX_NUM+j]) {
				p.drawRect(j*BRICK_SIZE+2,i*BRICK_SIZE+2,BRICK_SIZE-4,BRICK_SIZE-4);
				p.drawRect(j*BRICK_SIZE+4,i*BRICK_SIZE+4,BRICK_SIZE-8,BRICK_SIZE-8);
	    	}
	    	if (misplace==i*MAX_NUM+j+1) {
	    		p.save();
	    		p.setPen(Qt::red);
	    		p.drawRect(j*BRICK_SIZE+2,i*BRICK_SIZE+2,BRICK_SIZE-4,BRICK_SIZE-4);
				p.drawRect(j*BRICK_SIZE+4,i*BRICK_SIZE+4,BRICK_SIZE-8,BRICK_SIZE-8);
	    		p.restore();
	    	}
		}
	} else {
	    p.save();
	    p.setBrush(Qt::white);
	    p.drawRect(j*BRICK_SIZE+2,i*BRICK_SIZE+2,BRICK_SIZE-4,BRICK_SIZE-4);
	    p.restore();
	    if (hint_show) {
	    	if (misplace==i*MAX_NUM+j+1) {
	    		p.save();
	    		p.setPen(Qt::red);
	    		p.drawRect(j*BRICK_SIZE+2,i*BRICK_SIZE+2,BRICK_SIZE-4,BRICK_SIZE-4);
				p.drawRect(j*BRICK_SIZE+4,i*BRICK_SIZE+4,BRICK_SIZE-8,BRICK_SIZE-8);
	    		p.restore();
	    	}
		}
	}
	}
	
    }
    flash++;flash%=2;
    return;
}

void Fifteens::mousePressEvent(QMouseEvent *ev)
{
	if (checkEnd()) {new_game();return;}
    moveLine(ev->y()/BRICK_SIZE,ev->x()/BRICK_SIZE);
    if (checkEnd()) QMessageBox::information(this,"Congratulation", "You win");
    return;
}

void Fifteens::keyPressEvent(QKeyEvent *ev)
{
	int num;
	if (checkEnd()) {
		new_game();
		return;
	}
	if (ev->modifiers()&Qt::ShiftModifier) {
		num = MAX_NUM-1;
	} else {
		num = 1;
	}
    switch(ev->key()) {
	case Qt::Key_Left:
		if (num>1) num -= hc;
		if (hc+1<MAX_NUM)
			moveLine(hr,hc+num);
	    break;
	case Qt::Key_Right:
		if (num>1) num = hc;
		if (hc-1>=0)
			moveLine(hr,hc-num);
	    break;
	case Qt::Key_Up:
		if (num>1) num -= hr;
		if (hr+1<MAX_NUM)
			moveLine(hr+num,hc);
	    break;
	case Qt::Key_Down:
		if (num>1) num = hr;
		if (hr-1>=0)
			moveLine(hr-num,hc);
	    break;
	case Qt::Key_D:
		digits_show = !digits_show;
		repaint();
		break;
	case Qt::Key_H:
		hint_show = !hint_show;
		repaint();
		break;
	case Qt::Key_R:
		new_game();
		return;
    }

    if (checkEnd()) QMessageBox::information(this,"Congratulation", "You win");
    return;
}
