#include "MainWindow.h"

#include <QtCore>
#include <iostream>

using std::cout;
using std::endl;

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
	cout << "reps: " << repsSB->value() << endl;
}

void MainWindow::onResetButtonPressed()
{
	recentPoints.clear();
	display->reset();

	// set completed to true to force piThread to stop
}

void MainWindow::refreshDisplay()
{
	mux.lock();
	display->addPoints(recentPoints);
	recentPoints.clear();
	mux.unlock();

	if (completed)
	{
		//piThread.join()
		//qt popup that displays the estimate of pi
	}
}

uint64_t MainWindow::piLoop(uint64_t reps)
{
    // loop making points and incrementing count, and adding to recentPoints
    // check completed if we are being reset
}
