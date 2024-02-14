#include <QApplication>
#include "Windows.h"
#include "app.h"

int main(int argc, char* argv[]) {

	//	ShowWindow(::GetConsoleWindow(), SW_HIDE);
	ShowWindow(::GetConsoleWindow(), SW_SHOW);

	QCoreApplication::addLibraryPath(".");

	QApplication AudioExperiment(argc, argv);

	app  main;
	main.show();

	return AudioExperiment.exec();
}