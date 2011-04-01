#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtCore/QMutableListIterator>

#include "Brain.h"
#include "SettingsXmlHandler.h"
#include "rules/RuleNode.h"
#include "rules/RulesXmlHandler.h"


namespace CnotiMind
{

	Brain::Brain( const QString& path, QObject* parent ):
		QThread( parent ),
		_rules( NULL )
	{
		loadXmlSettings( path );

	}

	Brain::Brain( QObject* parent ):
		QThread( parent ),
		_rules( NULL )
	{

	}

	/**
		Load a XML file with settings.

		This method can me called several times, append new settings to the Brain.

		XML file can have Perceptions, Actions and Emotions
	*/
	bool Brain::loadXmlSettings( const QString& filename )
	{
		QFile f( filename );

		SettingsXmlHandler *handler = new SettingsXmlHandler( this );
		QXmlInputSource source( &f );
		if( source.data() == "" )
		{
			qWarning() << "[Brain::loadXmlSettings] File not found" << filename;
			return false;
		}

		QXmlSimpleReader reader;
		reader.setContentHandler( handler );

		// Retrives data from file
		return reader.parse( source );
	}

	/**
		Add a perception to the brain.

		Only perceptions
	*/
	void Brain::addValidPerception( const QString& perception )
	{
		_validPerceptions.append( perception );
	}

	/**
		Add an action to the brain.

		If no actions are added to the brain, it will not be possible for the brain
		to send actions to be executed. Only action added to the brain are sent.
	*/
	void Brain::addValidAction( const QString& action )
	{
		_validActions.append( action );
	}

	/**
		Emotions the brain reacts to.

		If no emotions are added to the brain, it will not react to emotion changes
		defined on the rules.
	*/
	void Brain::addEmotion( const Emotion& emotion )
	{
		_emotions.append( emotion );
	}

	/**

	*/
	bool Brain::loadXmlRules( const QString& filename )
	{
		QFile f( filename );

		RulesXmlHandler *handler = new RulesXmlHandler( this );
		QXmlInputSource source( &f );
		if( source.data() == "" )
		{
			qWarning() << "[Brain::loadXmlRules] File not found" << filename;
			return false;
		}

		QXmlSimpleReader reader;
		reader.setContentHandler( handler );

		// Retrives data from file
		if( reader.parse( source ) )
		{
			_rules = handler->rootNode();
			return true;
		}

		return false;
	}

	/**

	*/
	bool Brain::validateXML(int xml)
	{
		return true;
	}

	bool Brain::saveMemory(const QString& filename)
	{
		return true;
	}

	bool Brain::loadMemory(const QString& filename)
	{
		return true;
	}

	bool Brain::saveEmotionalState(const QString& filename)
	{
		return true;
	}

	bool Brain::loadEmotionalState(const QString& filename)
	{
		return true;
	}

	/**
		Main loop for the thread.

		Everytime a perceptions arrives, the _semaphoreBrian is made available, so it unlocks
		and start
	*/
	void Brain::run()
	{
		while( true )
		{
			// wait for some thing that triggers the brain to react
			// like
			// - emotion changes
			// - perceptions received
			// - changes in the memory
			_semaphoreBrain.acquire();

			int n_emotions = _emotionsChanged.size();

			// Execute the rules
			_rules->exec();

			// remove the emotions changed since the last rules exection
			// if new emotions were added during the rules execution, they are not removed,
			// so that in the next iteration they can be handled
			for(int i = 0; i < n_emotions; i++)
			{
				QString emotionName = _emotionsChanged.dequeue();

				Emotion e = _emotions.value( _emotions.indexOf( Emotion( emotionName, 0 ) ) );
			}

			// Remove first perception added.
			if(! _receivedPerceptions.isEmpty() )
			{
				Perception p = _receivedPerceptions.dequeue();
			}

		}
	}

	void Brain::clearWorkingMemory()
	{
		_workingMemory.clear();
	}

	void Brain::clearMemory()
	{
		_longTermMemory.clear();
		_workingMemory.clear();
	}


	void Brain::printSettings()
	{
		QStringList text;

		text << "--- Valid Perceptions ---";
		if( _validPerceptions.isEmpty() )
		{
			text << "No perceptions defined";
		}
		else
		{
			QListIterator<QString> it(_validPerceptions);
			while( it.hasNext() )
			{
				text << it.next();
			}
		}

		text << "--- Valid Actions ---";
		if( _validActions.isEmpty() )
		{
			text << "No actions defined";
		}
		else
		{
			QListIterator<QString> it(_validActions);
			while( it.hasNext() )
			{
				text << it.next();

			}
		}

		text << "--- Emotions ---";
		if( _emotions.isEmpty() )
		{
			text << "No emotions defined";
		}
		else
		{
			QListIterator<Emotion> it(_emotions);
			while( it.hasNext() )
			{
				text << it.next();
			}
		}

		qDebug() << text;
	}

	void Brain::printRules()
	{

	}

	void Brain::printMemory( MemoryType type )
	{

	}


	/*
		Translate a QString to MemoryType
	*/
	Brain::MemoryType Brain::translateMemoryType( const QString& text )
	{
		if( QString::compare( text, "WM", Qt::CaseInsensitive) == 0 )
		{
			return WorkingMemory;
		}
		if( QString::compare( text, "LTM", Qt::CaseInsensitive) == 0 )
		{
			return LongTermMemory;
		}
		return UndefinedMemory;
	}

	void Brain::receivePerception( const Perception& perception )
	{
		_receivedPerceptions.enqueue( perception );

		// changing the semaphore, so that
		_semaphoreBrain.release();
	}

	void Brain::updateEmotionalValue(const QString& emotionName, int variation, int max, int min)
	{
		QMutableListIterator<Emotion> it(_emotions);
		while(it.hasNext())
		{
			Emotion& e = it.next();
			if( QString::compare( e.key(), emotionName, Qt::CaseInsensitive ) == 0 )
			{
				if( e.addValue( variation, max, min) )
				{
					emit sendEmotionalState( emotionName, e.value() );

					_emotionsChanged.enqueue( emotionName );
					if(_semaphoreBrain.available() == 0)
					{
						_semaphoreBrain.release();
					}
					break;
				}
			}
		}
	}

	void Brain::updateEmotionalValue(const QString& emotionName, int variation)
	{
		updateEmotionalValue( emotionName, variation, INT_MAX, INT_MIN);
	}

	/*
		Store an event in the memory
	*/
	void Brain::storeToMemory( const MemoryEvent& event, MemoryType memory )
	{
		switch(memory)
		{
		case LongTermMemory:
			_longTermMemory.append( event );
			break;
		case WorkingMemory:
			_workingMemory.append( event );
			break;
		}
	}

	/*
		Sends an action
	*/
	void Brain::executeAction( const QString& key, const QString& value )
	{
		emit sendAction( key, value );
	}

}
