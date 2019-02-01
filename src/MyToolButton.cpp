#include "MyToolButton.h"

#include "MainWindow.h"

#include <QPainter>

MyToolButton::MyToolButton(QWidget *parent)
	: QToolButton(parent)
{
}

void MyToolButton::setIndicatorMode(Indicator i)
{
	indicator = i;
	update();
}

void MyToolButton::setDot(bool f)
{
	indicator = Dot;
	number = f;
	update();
}

void MyToolButton::setNumber(int n)
{
	indicator = Number;
	number = n;
	update();
}

void MyToolButton::paintEvent(QPaintEvent *event)
{
	QToolButton::paintEvent(event);

	auto *mw = qobject_cast<MainWindow *>(window());
    if(!mw) return;
    //Q_ASSERT(mw); //TMP to move the toolbar


	if (indicator == Dot && number > 0) {
		QPainter pr(this);
		pr.setRenderHint(QPainter::Antialiasing);
		int z = 10;
		QRect r(width() - z, 0, z, z);
		pr.setPen(Qt::NoPen);
		pr.setBrush(QColor(255, 0, 0));
		pr.drawEllipse(r);
	} else if (indicator == Number && number >= 0) {
		int w = mw->digitWidth();
		int h = mw->digitHeight();
		QPixmap pm;
		{
			char tmp[100];
			int n = sprintf(tmp, "%u", number);

			pm = QPixmap((w + 1) * n + 3, h + 4);
			pm.fill(Qt::red);

			QPainter pr(&pm);
			for (int i = 0; i < n; i++) {
				mw->drawDigit(&pr, 2 + i * (w + 1), 2, tmp[i] - '0');
			}
		}
		QPainter pr(this);
		pr.drawPixmap(width() - pm.width(), 0, pm);
	}
}
