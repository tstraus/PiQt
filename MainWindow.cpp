#include "MainWindow.h"

#include <QtCore>
#include <QMessageBox>
#include <chrono>
#include <random>
#include <iostream>

using std::cout;
using std::endl;
using std::make_pair;
using std::async;
using std::launch;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(), Ui::MainWindow()
{
	setupUi(this);

	refreshTimer = new QTimer();

	connect(refreshTimer, SIGNAL(timeout()), this, SLOT(refreshDisplay()));
	connect(startButton, SIGNAL(pressed()), this, SLOT(onStartButtonPressed()));

	refreshTimer->start(17); // about 60 FPS
}

void MainWindow::onStartButtonPressed()
{
    reps = repsSB->value();
	cout << "reps: " << reps << endl;
    
    piFuture = async(launch::async, &MainWindow::piLoop, this, repsSB->value());
}

void MainWindow::onResetButtonPressed()
{
	recentPoints.clear();
	display->reset();

	// set completed to true to force piThread to stop
	completed = true;
}

void MainWindow::refreshDisplay()
{
	mux.lock();
	display->addPoints(recentPoints);
	recentPoints.clear();
	mux.unlock();

	if (completed)
	{
        uint64_t count = piFuture.get();
		refreshTimer->stop();
        
		//qt popup that displays the estimate of pi
        QMessageBox msgBox;
        msgBox.setText(QString("Pi: ") + QString::number((double)count / (double)reps * 4.0));
	}
}

uint64_t MainWindow::piLoop(uint64_t reps)
{
    uint64_t count = 0;

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
			return 0;
	}

	completed = true;

	return count;
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
