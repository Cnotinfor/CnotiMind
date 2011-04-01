#ifndef FORM_H
#define FORM_H

#include <QWidget>

#include <Action>
#include <Emotion>

namespace CnotiMind
{
	class Brain;
}

namespace Ui {
	class Form;
}

class Form : public QWidget
{
	Q_OBJECT

public:
	explicit Form(QWidget *parent = 0);
	~Form();

private slots:
	// GUI slots
	void on_pushButtonShow_clicked();
	void on_pushButtonExit_clicked();

	// Brain slots - connect brain to the GUI
	void actionReceived( const QString& key, const QString& value );
	void emotionReceived( const QString& emotion, int value );


protected:
	void changeEvent(QEvent *e);

private:
	Ui::Form *_ui;
	CnotiMind::Brain* _brain;

};

#endif // FORM_H
