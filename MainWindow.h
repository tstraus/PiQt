#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <QMainWindow>
#include <atomic>
#include <mutex>
#include <thread>
#include <stdint.h>

#include "ui_MainWindow.h"

using std::atomic;
using std::mutex;
using std::pair;

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
    void piLoop(uint64_t reps);

	bool checkCircle(Vec2f point);
    
    std::thread* piThread;
    
    uint64_t reps;

	uint64_t count;

	vector<pair<Vec2f, Color>> recentPoints;

	atomic<bool> completed;

	QTimer* refreshTimer;

	mutex mux;
};

#endif // __MAIN_WINDOW_H__
