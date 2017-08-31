#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <QMainWindow>
#include <atomic>
#include <mutex>
#include <future>
#include <stdint.h>

#include "ui_MainWindow.h"

using std::atomic;
using std::mutex;

class MainWindow : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = 0);

	~MainWindow() {};

public slots:
	void onStartButtonPressed();

	void onResetButtonPressed();

	void refreshDisplay();

private:
    uint64_t piLoop(uint64_t reps);

	vector<Vec2f> recentPoints;

	atomic<bool> completed;

	QTimer* refreshTimer;

	mutex mux;
};

#endif // __MAIN_WINDOW_H__
