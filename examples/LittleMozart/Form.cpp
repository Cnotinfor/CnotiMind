#include <QDebug>
#include <QSignalMapper>

#include "Form.h"
#include "ui_Form.h"
#include "CnotiAudio.h"
#include "Brain.h"
#include "Perception.h"

Form::Form(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Form)
{
	ui->setupUi(this);


	// connect buttons to slots
	QSignalMapper* signalMapperNotes = new QSignalMapper(this);

	connect(ui->pushButtonDo, SIGNAL(clicked()), signalMapperNotes, SLOT(map()));
	connect(ui->pushButtonRe, SIGNAL(clicked()), signalMapperNotes, SLOT(map()));
	connect(ui->pushButtonMi, SIGNAL(clicked()), signalMapperNotes, SLOT(map()));
	connect(ui->pushButtonFa, SIGNAL(clicked()), signalMapperNotes, SLOT(map()));
	connect(ui->pushButtonSol, SIGNAL(clicked()), signalMapperNotes, SLOT(map()));
	connect(ui->pushButtonLa, SIGNAL(clicked()), signalMapperNotes, SLOT(map()));
	connect(ui->pushButtonSi, SIGNAL(clicked()), signalMapperNotes, SLOT(map()));
	connect(ui->pushButtonDoAgudo, SIGNAL(clicked()), signalMapperNotes, SLOT(map()));
	connect(ui->pushButtonPause, SIGNAL(clicked()), signalMapperNotes, SLOT(map()));
	signalMapperNotes->setMapping(ui->pushButtonDo, "Do");
	signalMapperNotes->setMapping(ui->pushButtonRe, "Re");
	signalMapperNotes->setMapping(ui->pushButtonMi, "Mi");
	signalMapperNotes->setMapping(ui->pushButtonFa, "Fa");
	signalMapperNotes->setMapping(ui->pushButtonSol, "Sol");
	signalMapperNotes->setMapping(ui->pushButtonLa, "La");
	signalMapperNotes->setMapping(ui->pushButtonSi, "Si");
	signalMapperNotes->setMapping(ui->pushButtonDoAgudo, "Do Agudo");
	signalMapperNotes->setMapping(ui->pushButtonPause, "Pause");

	connect(signalMapperNotes, SIGNAL(mapped(const QString&)), this, SLOT(noteClicked(const QString&)));

	QSignalMapper* signalMapperDurations = new QSignalMapper(this);

	connect(ui->pushButtonDuration1, SIGNAL(clicked()), signalMapperDurations, SLOT(map()));
	connect(ui->pushButtonDuration2, SIGNAL(clicked()), signalMapperDurations, SLOT(map()));
	connect(ui->pushButtonDuration3, SIGNAL(clicked()), signalMapperDurations, SLOT(map()));
	connect(ui->pushButtonDuration4, SIGNAL(clicked()), signalMapperDurations, SLOT(map()));
	signalMapperDurations->setMapping(ui->pushButtonDuration1, "1");
	signalMapperDurations->setMapping(ui->pushButtonDuration2, "2");
	signalMapperDurations->setMapping(ui->pushButtonDuration3, "3");
	signalMapperDurations->setMapping(ui->pushButtonDuration4, "4");

	connect(signalMapperDurations, SIGNAL(mapped(const QString&)), this, SLOT(durationClicked(const QString&)));

	// Brain init
	_brain = new CnotiMind::Brain( "../../xml/mozart_mind.xml", this);

	connect( _brain, SIGNAL(sendAction(const QString&,const QString&)), this, SLOT(actionReceived(const QString&,const QString&)));
	connect( _brain, SIGNAL(sendEmotionalState(const QString&,qreal)), this, SLOT(emotionReceived( const QString&, qreal )));

	if(!_brain->loadXmlRules( "../../xml/mozart_rules.xml" ) )
	{
		qWarning() << "[Form::Form] Error loading Xml rules.";
	}

	_brain->printRules();

	_brain->start();
}

Form::~Form()
{
	_brain->stop();
	delete ui;
}

void Form::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}


void Form::noteClicked( const QString& note )
{
	qDebug() << "Note:" << note;
	ui->groupBoxDurations->setEnabled( true );

	CnotiMind::Perception p( "Add Note", note );

	_brain->receivePerception( p );
}


void Form::durationClicked( const QString& duration )
{
	ui->groupBoxDurations->setEnabled( false );

	CnotiMind::Perception p( "Add Duration", duration );

	_brain->receivePerception( p );
}

void Form::on_pushButtonPrint_clicked()
{
	_brain->printMemory(CnotiMind::WorkingMemory);
}

void Form::actionReceived(const QString& action,const QString& value)
{
	ui->plainTextEditActions->insertPlainText( action + ": " + value + "\n");
}

void Form::emotionReceived( const QString& emotion, qreal value)
{
	ui->plainTextEditEmotions->insertPlainText( emotion + ": " + QString::number( value, 'g', 2 ) + "\n" );
}
