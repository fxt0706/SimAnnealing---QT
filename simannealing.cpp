#include "simannealing.h"

SimAnnealing::SimAnnealing(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.button_start, SIGNAL(clicked()), this, SLOT(StartRun(void)));
	//ui.view_anneal->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	//ui.view_greedy->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

SimAnnealing::~SimAnnealing()
{
	
}

void SimAnnealing::StartRun(void)
{
	//QMatrix
	qDebug() << "Start";
	QString num_string = ui.input_num->toPlainText();
	int num_iput = num_string.toInt();
	value = new int[num_iput];

	QGraphicsScene *scene_anneal = new QGraphicsScene(this);
	QGraphicsScene *scene_greedy = new QGraphicsScene(this);
	scene_anneal->setSceneRect(0, 0, 295, 195);
	scene_greedy->setSceneRect(0, 0, 295, 195);;
	ui.view_anneal->setScene(scene_anneal);
	ui.view_greedy->setScene(scene_greedy);

	float interval = 295.000 / num_iput;
	
	for (int i = 0; i < num_iput; i++)
	{
		int num_rand = (rand() % (195 - 0 + 1));      //Y轴
		value[i] = 195 - num_rand;                 
		float coordinate_x = interval*i;
		scene_anneal->addRect(coordinate_x, num_rand, interval, value[i]);
		scene_greedy->addRect(coordinate_x, num_rand, interval, value[i]);
	}
	

	QGraphicsEllipseItem *ellip_greedy = new QGraphicsEllipseItem();
	QGraphicsEllipseItem *ellip_anneal = new QGraphicsEllipseItem();
	
	ellip_anneal->setBrush(Qt::red);
	ellip_greedy->setBrush(Qt::red);

	
    // 贪心算法
	
	int num_rand = (rand() % (num_iput - 0 + 1));
	int num_now = num_rand;							 //所在的序号
	float coordinate_x = interval * num_now + interval/2 - 5;
	
	ellip_greedy->setRect(coordinate_x , 195 - value[num_now] - 5, 10, 10);
	scene_greedy->addItem(ellip_greedy);

	int times_greedy = 0;
	bool state = false;

	while (state == false)
	{
		if (value[num_now] > value[num_now - 1] && value[num_now] > value[num_now + 1])
			state = true;
		else
		{
			if (value[num_now-1] < value[num_now + 1])
				num_now++;
			else if (value[num_now - 1] > value[num_now + 1])
				num_now--;
		}
		coordinate_x = interval * num_now + interval / 2 - 5;
		ellip_greedy->setRect(coordinate_x, 195 - value[num_now] - 5, 10, 10);
		qDebug() << "break 1 !";
		times_greedy++;
		ui.view_greedy->viewport()->repaint();
	}

	int value_greedy = value[num_now];

	qDebug() << "quit";
	
	
	num_now = num_rand;
	coordinate_x = interval * num_now + interval / 2 - 5;
	ellip_anneal->setRect(coordinate_x, 195 - value[num_now] - 5, 10, 10);
	scene_anneal->addItem(ellip_anneal);
	
	state = false;
	float heat = 100.000;
	float cool = 0.919;
	int times_anneal = 0;

	while (heat > 0.01)
	{
		num_rand = rand();
		int dice_direction = num_rand % (num_iput+1);
		int dice_ifmove = num_rand % 101;
		if (num_now >= dice_direction)
		{
			qreal dice_dice = 10 * qExp((value[num_now - 1] - value[num_now]) / heat);
			if (value[num_now] <= value[num_now - 1])
				num_now--;
			else if (dice_dice >= dice_ifmove)
				num_now--;
		}if (num_now < dice_direction)
		{
			qreal dice_dice = 100 * qExp((value[num_now + 1] - value[num_now]) / heat);
			if (value[num_now] <= value[num_now + 1])
				num_now++;
			else if (dice_dice >= dice_ifmove)
				num_now++;
		}

		heat = heat * cool;
		QString heat_string;
		heat_string.setNum(heat);
		ui.label_heatvalue->setText(heat_string);
		coordinate_x = interval * num_now + interval / 2 - 5;
		ellip_anneal->setRect(coordinate_x, 195 - value[num_now] - 5, 10, 10);
		times_anneal++;

		ui.view_anneal->viewport()->repaint();
	}

	int value_anneal = value[num_now];

	qDebug() << "anneal run " << times_anneal << "times";
	qDebug() << "greedy run " << times_greedy << "times";
	qDebug() << "anneal value is " << value_anneal;
	qDebug() << "greedy value is " << value_greedy;
	delete[] value;
}

void SimAnnealing::closeEvent(QCloseEvent *event)
{
	event->accept();
}
