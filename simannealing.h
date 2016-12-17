#ifndef SIMANNEALING_H
#define SIMANNEALING_H

#include <QtWidgets/QMainWindow>
#include "ui_simannealing.h"
#include <qgraphicsitem.h>
#include <QDebug>
#include <QCloseEvent>
#include <QPainter>
#include <qmath.h>

#include <iostream>
#include <windows.h>


class SimAnnealing : public QMainWindow
{
	Q_OBJECT

public:
	SimAnnealing(QWidget *parent = 0);
	~SimAnnealing();
	
private:
	Ui::SimAnnealingClass ui;

	int *value;
	
private slots:
	void StartRun(void);

protected:
	void closeEvent(QCloseEvent *event);
};

#endif // SIMANNEALING_H
