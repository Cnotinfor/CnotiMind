#ifndef FORM_H
#define FORM_H

#include <QWidget>


namespace Ui {
	class Form;
}

namespace CnotiMind {
	class Brain;
}

class Form : public QWidget
{
	Q_OBJECT

public:
	explicit Form(QWidget *parent = 0);
	~Form();

protected:
	void changeEvent(QEvent *e);

private slots:
	void noteClicked( const QString& note );
	void durationClicked( const QString& duration );

	void on_pushButtonPrint_clicked();
	void on_pushButtonSave_clicked();
	void on_pushButtonLoad_clicked();

	void on_pushButtonCancelDuration_clicked();
	void on_pushButtonDeleteNote_clicked();
	void on_pushButtonStartMelody_clicked();
	void on_pushButtonFinishMelody_clicked();

	void actionReceived(const QString& action,const QString& value);
	void emotionReceived( const QString& emotion, qreal value);

private:
	Ui::Form *ui;
	CnotiMind::Brain *_brain;
};

#endif // FORM_H
