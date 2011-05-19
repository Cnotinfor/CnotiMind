#include "BrainGUI.h"
#include "ui_BrainGUI.h"
#include "../Brain.h"
#include "PropertiesModel.h"
#include "EmotionsModel.h"
#include "PerceptionsModel.h"
#include "MemoryModel.h"


namespace CnotiMind
{

	BrainGUI::BrainGUI( const Brain* brain, QWidget *parent ):
		QWidget( parent ),
		_ui( new Ui::BrainGUI() )
	{
		_ui->setupUi( this );


		_propertiesModel = new PropertiesModel( brain, this );
		_emotionsModel = new EmotionsModel( brain, this );
		_perceptionsModel = new PerceptionsModel( this );
		_longTermMemoryModel = new MemoryModel( CnotiMind::LongTermMemory, brain, this );
		_workingMemoryModel = new MemoryModel( CnotiMind::WorkingMemory, brain, this );


		_ui->tableProperties->setModel( _propertiesModel );
		_ui->tableEmotions->setModel( _emotionsModel );
		_ui->tablePerceptions->setModel( _perceptionsModel );
	}

	BrainGUI::~BrainGUI()
	{
		delete _ui;
	}

	void BrainGUI::updateProperties()
	{
		_propertiesModel->update();
	}

	void BrainGUI::updateEmotions()
	{
		_emotionsModel->update();
	}

	void BrainGUI::updatePerceptions( const Perception& p )
	{
		_perceptionsModel->update( p );
	}

	void BrainGUI::updateLongTermMemory()
	{
		//_longTermMemoryModel->update();
	}

	void BrainGUI::updateWorkingMemory()
	{
		//_workingMemoryModel->update();

	}

	void BrainGUI::changeEvent( QEvent *e )
	{
		QWidget::changeEvent( e );
		switch ( e->type() )
		{
			case QEvent::LanguageChange:
				_ui->retranslateUi(this);
				break;
			default:
				break;
		}
	}

}
