#include "MainWindow.h"

#include <QtCore>
#include <QMessageBox>
#include <chrono>
#include <random>
#include <iostream>

using std::cout;
using std::endl;
using std::make_pair;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(), Ui::MainWindow()
{
	setupUi(this);
	completed = false;
	count = 0;
	refreshTimer = new QTimer();
	display->initializeGL();

	connect(refreshTimer, SIGNAL(timeout()), this, SLOT(refreshDisplay()));
	connect(startButton, SIGNAL(pressed()), this, SLOT(onStartButtonPressed()));
	connect(resetButton, SIGNAL(pressed()), this, SLOT(onResetButtonPressed()));
}

void MainWindow::onStartButtonPressed()
{
    reps = repsSB->value();
	cout << "reps: " << reps << endl;
    
	piThread = new std::thread(&MainWindow::piLoop, this, repsSB->value());

	refreshTimer->start(17); // about 60 FPS
}

void MainWindow::onResetButtonPressed()
{
	recentPoints.clear();
	display->reset();
	count = 0;

	// set completed to true to force piThread to stop
	completed = true;
}

void MainWindow::refreshDisplay()
{
	mux.lock();
	vector<pair<Vec2f, Color>> tempPoints;
	for (auto point : recentPoints)
		tempPoints.push_back(point);
	//display->addPoints(recentPoints);
	recentPoints.clear();
	mux.unlock();

	display->addPoints(tempPoints);

	if (completed)
	{
		refreshTimer->stop();
		piThread->join();
        
		//qt popup that displays the estimate of pi
        QMessageBox msgBox;
        msgBox.setText(QString("Pi: ") + QString::number((double)count / (double)reps * 4.0));
	}
}

void MainWindow::piLoop(uint64_t reps)
{
	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine engine(seed);
	std::uniform_real_distribution<float> rand(0, 1);

	Vec2f point;

	for (uint64_t i = 0; i < reps; i++)
	{
		point.x = rand(engine);
		point.y = rand(engine);

		if (checkCircle(point))
			count++;

		// stop loop if reset was pressed
		if (completed)
			break;
	}

	completed = true;
}

bool MainWindow::checkCircle(Vec2f point)
{
	if (point.x * point.x + point.y * point.y < 1.0f)
	{
		recentPoints.push_back(make_pair(point, GREEN));
		return true;
	}

	else
	{
		recentPoints.push_back(make_pair(point, RED));
		return false;
	}
}
