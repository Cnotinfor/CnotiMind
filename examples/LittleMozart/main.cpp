#include <QtGui/QApplication>

#include "Form.h"

int main( int argc, char ** argv )
{
	QApplication a(argc, argv);
	Form f;

	f.show();

	return a.exec();
}
