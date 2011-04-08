//Qt
#include <QtCore/QDebug>

#include "Form.h"
#include "ui_Form.h"

// Cnoti Mind
#include <Brain>
#include <Perception>
#include <Action>
#include <Emotion>

#define XML_RULES "../../xml/single_emotion_rules.xml"
#define XML_SETTINGS "../../xml/mind_settings.xml"


Form::Form(QWidget *parent) :
	QWidget(parent),
	_ui(new Ui::Form),
	_brain( new CnotiMind::Brain( XML_SETTINGS , this ) )
{
	_ui->setupUi(this);

	connect( _brain, SIGNAL(sendAction(const QString&,const QString&)), this, SLOT(actionReceived(const QString&,const QString&)));
	connect( _brain, SIGNAL(sendEmotionalState(const QString&,qreal)), this, SLOT(emotionReceived( const QString&, qreal )));

	if(!_brain->loadXmlRules( XML_RULES ) )
	{
		qWarning() << "[Form::Form] Error loading Xml rules.";
	}

	_brain->start();

	_brain->printSettings();
}

Form::~Form()
{
	delete _ui;
}

void Form::on_pushButtonShow_clicked()
{

	CnotiMind::Perception p("User Talk", "Hello");
	_brain->receivePerception( p );
}

void Form::on_pushButtonExit_clicked()
{
	CnotiMind::Perception p("User Talk", "Bye");
	_brain->receivePerception( p );
}

void Form::actionReceived( const QString& key, const QString& value )
{
	_ui->plainTextEdit->appendPlainText( "Action " + key + ": " + value );
}

void Form::emotionReceived( const QString& emotion, qreal value )
{
	_ui->plainTextEdit->appendPlainText( "Emotion " + emotion + ": " + QString::number( value ) );
}


void Form::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		_ui->retranslateUi(this);
		break;
	default:
		break;
	}
}



