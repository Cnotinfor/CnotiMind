#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtCore/QMutableListIterator>
#include <QtCore/QListIterator>
#include <QDateTime>
#include <QList>
#include <QTextCodec>

#include "Brain.h"
#include "CnotiMind.h"
#include "SettingsXmlHandler.h"
#include "rules/RuleNode.h"
#include "rules/RulesXmlHandler.h"
#include "gui/BrainGUI.h"
#include "MemoryXmlHandler.h"
#include "ActionModifier.h"
#include "ActionModifiersXmlHandler.h"

namespace CnotiMind
{

	Brain::Brain( const QString& path, QObject* parent ):
		QThread( parent ),
		_rules( NULL ),
		_quit( false ),
		_gui( NULL )
	{
		loadXmlSettings( path );

		// To generate a new random seed
		qsrand( QDateTime::currentDateTime().toTime_t() );
	}

	Brain::Brain( QObject* parent ):
		QThread( parent ),
		_rules( NULL ),
		_quit( false ),
		_gui( NULL )
	{

	}

	Brain::~Brain()
	{
//		_quit = true;
//		_semaphoreBrain.release();
//		wait();

		if( _gui != NULL )
		{
			delete _gui;
		}
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
		defined on the rules
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

		RulesXmlHandler handler( this, _rules );
		QXmlInputSource source( &f );
		if( source.data() == "" )
		{
			qWarning() << "[Brain::loadXmlRules] File not found" << filename;
			return false;
		}

		QXmlSimpleReader reader;
		reader.setContentHandler( &handler );

		// Retrives data from file
		if( reader.parse( source ) )
		{
			_rules = handler.rootNode();
			return true;
		}

		qDebug() << "[Brain::loadXmlRules] Error in XML, line" << handler.line();

		return false;
	}


	bool Brain::saveMemory(const QString& filename)
	{
		saveEmotionalStateToMemory();
		saveLastSceneToMemory();

		// Save to xml
		QFile f(filename);
		QTextStream out(&f);
		out.setCodec(QTextCodec::codecForName("UTF-8"));

		if( f.open( QIODevice::WriteOnly | QIODevice::Text ) )
		{
			f.write( "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" );
			f.write( "<Memory>\n" );
			f.write( "\t<LongTermMemory>\n" );
			QListIterator<MemoryEvent> it(_longTermMemory);
			while(it.hasNext())
			{
				f.write( "\t\t");
				f.write( it.next().toXml().toUtf8() + "\n" );
			}
			f.write( "\t</LongTermMemory>\n" );
//			f.write( "\t<WorkingMemory>\n" );
//			QListIterator<MemoryEvent> it2(_workingMemory);
//			while(it2.hasNext())
//			{
//				f.write( "\t\t");
//				f.write( it2.next().toXml().toUtf8() + "\n" );
//			}
//			f.write( "\t</WorkingMemory>\n" );
			f.write( "</Memory>\n" );

			f.close();
			return true;
		}

		return false;
	}

	bool Brain::loadMemory(const QString& filename)
	{
		_longTermMemory.clear();

		QFile f(filename);

		QXmlInputSource source( &f );
		MemoryXmlHandler handler(this);

		if( source.data() == "" )
		{
			qWarning() << "[Brain::loadMemory] File not found" << filename;
			return false;
		}

		QXmlSimpleReader reader;
		reader.setContentHandler( &handler );

		// Retrives data from file
		if( reader.parse( source ) )
		{
			loadEmotionalStateFromMemory();
			loadLastSceneFromMemory();
			return true;
		}

		return false;
	}

	/**
	  Saves the emotions states to the long term memory
	*/
	bool Brain::saveEmotionalStateToMemory()
	{
		qint64 emotionTime = MemoryEvent::eventTime(); // It's given to all the emotions the same time

		// Marks in long term memory that the emotions are going to be saved
		MemoryEvent m("EmotionDump", emotionTime);
		this->storeToMemory( m, LongTermMemory);

		// Saves all emotion to long term memory
		QListIterator<Emotion> memIt(_emotions);
		while(memIt.hasNext())
		{
			Emotion e = memIt.next();
			MemoryEvent m( "Emotion " + e.key(), e.value(), emotionTime );

			this->storeToMemory( m, LongTermMemory);
		}
		return true;
	}

	/**
	  Loads the emotions states from the long term memory
	*/
	bool Brain::loadEmotionalStateFromMemory()
	{
		// Gets the last savd emotions values in long term memory and updates them.
		QListIterator<MemoryEvent> it(_longTermMemory);
		it.toBack();
		while (it.hasPrevious())
		{
			MemoryEvent m = it.previous();
			if (!m.event().contains("Emotion "))
			{
				continue;
			}

			// Find emotion and change it
			QString emotionName = m.event().split(' ').last();
			this->setEmotionalValue(emotionName, m.value().toReal());

			break;
		}
		return true;
	}

	bool Brain::saveLastSceneToMemory()
	{
		// Saves current scene to long term memory
		QHashIterator<QString, QString> propIt(_properties);
		while(propIt.hasNext())
		{
			propIt.next();
			QString prop = propIt.key();
			if (prop.compare("SCENE", Qt::CaseInsensitive) == 0)
			{
				MemoryEvent m( "Last Scene", propIt.value(), MemoryEvent::eventTime() );
				this->storeToMemory( m, LongTermMemory);
				return true;
			}
		}
		// Default scene
		MemoryEvent m( "Last Scene", "Entry", MemoryEvent::eventTime() );
		this->storeToMemory( m, LongTermMemory);
		return true;
	}

	bool Brain::loadLastSceneFromMemory()
	{
		// Gets the last saved scene in long term memory and updates them.
		QListIterator<MemoryEvent> it(_longTermMemory);
		it.toBack();
		while (it.hasPrevious())
		{
			MemoryEvent m = it.previous();
			if (m.event().contains("Last Scene"))
			{
				// Find emotion and change it
				QString name = m.event().split(' ').last();
				QString value = m.value().toString();
				this->updatePropertyValue(name, value);

				emit sendAction(name, value);
				break;
			}
		}
		return true;
	}

	/**
		Main loop for the thread.

		Everytime a perceptions arrives, the _semaphoreBrain is made available, so it unlocks
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

			// Check if it should stop
			if(_quit)
			{
				return;
			}

			int n_emotions = _emotionsChanged.size();

			// Execute the rules
			if( _rules != NULL )
			{
				_talkModifierEnabled = true;
				_rules->exec();
			}

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

		if( _gui != NULL )
		{
			_gui->updateWorkingMemory();
		}
	}

	void Brain::clearMemory()
	{
		_longTermMemory.clear();
		_workingMemory.clear();

		if( _gui != NULL )
		{
			_gui->updateLongTermMemory();
			_gui->updateWorkingMemory();
		}
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
		if( _rules != NULL )
		{
			qDebug() << _rules->info();
		}
	}

	void Brain::printMemory( MemoryType type )
	{
		QListIterator<MemoryEvent> it(type == WorkingMemory ? _workingMemory : _longTermMemory );

		qDebug() << "[Brain::printMemory]";
		while(it.hasNext())
		{
			MemoryEvent me = it.next();

			qDebug() << me.event() << me.value().toString();
		}
	}

	void Brain::printProperties()
	{
		QHashIterator<QString, QString> it(_properties);

		qDebug() << "[Brain::printProperties]";
		while(it.hasNext())
		{
			it.next();
			qDebug() << it.key() << it.value();
		}
	}


	void Brain::receivePerception( const Perception& perception )
	{
		_receivedPerceptions.enqueue( perception );

		// changing the semaphore, to start executing the rules
		_semaphoreBrain.release();

		if( _gui != NULL )
		{
			_gui->updatePerceptions( perception );
		}
	}

	/*
		Stops the brain
	*/
	void Brain::stop()
	{
		_quit = true;
		_semaphoreBrain.release();
		wait();
	}

	/**
	 * Show the a GUI with the Brain information
	 */
	void Brain::showGUI()
	{
		if( _gui == NULL )
		{
			_gui = new BrainGUI( this );
			_gui->show();
		}
		else
		{
			_gui->show();
		}
	}

	/*!
		Updated the graphical representation of the memory events
	*/
	void Brain::updateGUI()
	{
		if( _gui != NULL )
		{
			_gui->updateLongTermMemory();
			_gui->updateWorkingMemory();
		}
	}

	void Brain::updateEmotionalValue(const QString& emotionName, qreal variation, qreal max, qreal min)
	{
		if (_disabledTasks.contains(EmotionNodes))
		{
			qDebug() << "[Brain::updateEmotionalValue] Emotional tasks are disabled.";
			return;
		}

		Emotion* e = findEmotion(emotionName);
		if( e->addValue( variation, max, min) )
		{
			emotionChanged(e);
		}
	}

	void Brain::updateEmotionalValue(const QString& emotionName, qreal variation)
	{
		updateEmotionalValue( emotionName, variation, INT_MAX, INT_MIN);
	}

	/**
	  Changes the value of an emotion
	*/
	void Brain::setEmotionalValue(const QString& emotionName, qreal value)
	{
		if (_disabledTasks.contains(EmotionNodes))
		{
			qDebug() << "[Brain::setEmotionalValue] Emotional tasks are disabled.";
			return;
		}

		Emotion* e = findEmotion(emotionName);
		if (e->setValue(value))
		{
			emotionChanged(e);
		}
	}

	/**
	  Searches an emotion in the emotion list, by it's name.
	*/
	Emotion* Brain::findEmotion(const QString& emotionName)
	{
		QMutableListIterator<Emotion> it(_emotions);
		while (it.hasNext())
		{
			Emotion& e = it.next();
			if (QString::compare( e.key(), emotionName, Qt::CaseInsensitive ) == 0)
			{
				return &e;
			}
		}
		return NULL;
	}

	/**
	  Tasks to execute after a emotion values has changed
	*/
	void Brain::emotionChanged(const Emotion* emotion)
	{
		emit sendEmotionalState( emotion->key(), emotion->value() );

		_emotionsChanged.enqueue( emotion->key() );
		if(_semaphoreBrain.available() == 0)
		{
			_semaphoreBrain.release();
		}

		// Update the GUI
		if( _gui != NULL )
		{
			_gui->updateEmotions();
		}
	}

	void Brain::updatePropertyValue( const QString& name, const QString& value )
	{
		_properties.insert( name, value );
		if( _gui != NULL )
		{
			_gui->updateProperties();
		}
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
			if( _gui != NULL )
			{
				_gui->updateLongTermMemory();
			}
			break;
		case WorkingMemory:
			_workingMemory.append( event );
			if( _gui != NULL )
			{
				_gui->updateWorkingMemory();
			}
			break;
		}
	}

	/*
		Sends an action
	*/
	void Brain::executeAction( const QString& key, const QString& value )
	{
		if (_disabledTasks.contains(ActionNodes))
		{
			qDebug() << "[Brain::executeAction] Action tasks are disabled.";
			return;
		}

		// Hold action info
		typedef struct {
			QString key;
			QString value;
		} action;

		action a = {key, value};
		QList<action> actions;
		actions << a;

		// Verify modifiers
		if (_talkModifierEnabled)
		{
			// Get modifiers for this action
			QList<ActionModifier*> modifiers = actionModifiers(key);
			if (!modifiers.empty())
			{
				_talkModifierEnabled = false;
				// Select one of the modifiers
				int pos = qrand() % modifiers.size();
				ActionModifier* r = modifiers.at(pos);
				action mAction = {key, r->identification()};

				int order = r->order();
				if (order == ActionModifier::ExecuteBeforeOrAfter)
				{
					if ((qrand() % 2) == 1)
					{
						order = ActionModifier::ExecuteBefore;
					}
					else
					{
						order = ActionModifier::ExecuteAfter;
					}
				}

				// Add to action list
				switch (order)
				{
				case ActionModifier::ExecuteBefore:
					// Start of the list
					actions.insert(0, mAction);
					break;
				case ActionModifier::ExecuteAfter:
					// End of the list
					actions << mAction;
					break;
				}
			}
		}

		// Execute actions
		QListIterator<action> it(actions);
		while (it.hasNext())
		{
			action itAction = it.next();
			if( _gui != NULL )
			{
				_gui->updateActions( itAction.key, itAction.value );
			}

			emit sendAction( itAction.key, itAction.value );
		}

	}

	/*
		Delete an event from the memory
	*/
	void Brain::deleteEvent( const QString& name, EventPosition position, MemoryType memory )
	{
		QList<MemoryEvent>* mem = ( memory == LongTermMemory ? &_longTermMemory : &_workingMemory );

		QMutableListIterator<MemoryEvent> it(*mem);

		switch(position)
		{
			case PositionLast:
				it.toBack();
				while(it.hasPrevious())
				{
					if( it.previous() == name )
					{
						it.remove();
						break;
					}
				}
				break;
			case PositionFirst:
				while(it.hasNext())
				{
					if( it.next() == name )
					{
						it.remove();
						break;
					}
				}
				break;
			case PositionAll:
				while(it.hasNext())
				{
					if( it.next() == name )
					{
						it.remove();
					}
				}
				break;
		}

		updateGUI();
	}

	void Brain::deleteEvent( const QString& name, const QString& value, EventPosition position, MemoryType memory )
	{
		QList<MemoryEvent>* mem = ( memory == LongTermMemory ? &_longTermMemory : &_workingMemory );
		MemoryEvent tmpEvent(name, value);

		QMutableListIterator<MemoryEvent> it(*mem);

		switch(position)
		{
			case PositionLast:
				it.toBack();
				while(it.hasPrevious())
				{
					if( it.previous() == tmpEvent )
					{
						it.remove();
						break;
					}
				}
				break;
			case PositionFirst:
				while(it.hasNext())
				{
					if( it.next() == tmpEvent )
					{
						it.remove();
						break;
					}
				}
				break;
			case PositionAll:
				while(it.hasNext())
				{
					if( it.next() == tmpEvent )
					{
						it.remove();
					}
				}
				break;
		}

		updateGUI();
	}


	/*!
		Copies all events from one memory to another memory.
	*/
	void Brain::copyEvents(MemoryType fromMemory, MemoryType toMemory)
	{
		QList<MemoryEvent> &listFrom = (fromMemory == LongTermMemory ? _longTermMemory : _workingMemory);
		QList<MemoryEvent> &listTo = (toMemory == LongTermMemory ? _longTermMemory : _workingMemory);

		// size must be read here, in case it is the same memory, if not is an endless loop
		int size = listFrom.size();
		for(int i = 0; i < size; i++)
		{
			listTo.append(listFrom.at(i));
		}
	}

	/*!
		Copies the Events from a memory to another. The
	*/
	void Brain::copyEvents( MemoryType fromMemory, MemoryType toMemory, const QString afterEvent,
							EventPosition afterPosition, const QString &beforeEvent,
							EventPosition beforePosition)
	{
		QList<MemoryEvent> tmp;
		QList<MemoryEvent> &listFrom = (fromMemory == LongTermMemory ? _longTermMemory : _workingMemory);
		QList<MemoryEvent> &listTo = (toMemory == LongTermMemory ? _longTermMemory : _workingMemory);

		int iAfter = findMemoryEvent( afterPosition, afterEvent, listFrom );
		int iBefore = findMemoryEvent( beforePosition, beforeEvent, listFrom );

		if(iBefore == -1 || iAfter == -1)
		{
			// It doesn't make the copy of between memories
			return;
		}
		if(iAfter > iBefore )
		{
			// If the events don't provide a valid rage of elements to be copied
			return;
		}

		// Copy the elements to the other memory storage

		for(int i = iAfter; i <= iBefore; i++)
		{
			listTo.append( listFrom.at(i) );
		}
	}


	/*!
		Search for a memory Event named eventName in the memory
	*/
	int Brain::findMemoryEvent( EventPosition position, const QString& eventName, const QList<MemoryEvent>& memory )
	{
		if( position == PositionLast )
		{
			for(int pos = memory.size() - 1; pos >= 0; pos--)
			{
				if(memory.at(pos) == eventName)
				{
					// Found MemoryEvent
					return pos;
				}
			}
		}
		else if( position == PositionFirst )
		{
			for(int pos = 0; pos < memory.size(); pos++)
			{
				if(memory.at(pos) == eventName)
				{
					// Found MemoryEvent
					return pos;
				}
			}
		}
		// not found
		return -1;
	}

	int Brain::findMemoryEvent( int itemPosition, const QString& eventName, const QList<MemoryEvent>& memory )
	{
		int n = 0; // Count the number of events found

		if( itemPosition > 0 )
		{
			// start from the oldest event in the memory
			for(int pos = 0; pos < memory.size(); pos++)
			{
				if(memory.at(pos) == eventName)
				{
					// Found MemoryEvent
					n++;
					// Test if it is itemPosition evenName found
					if(n == itemPosition)
					{
						return pos;
					}
				}
			}
		}
		else if( itemPosition < 0 )
		{
			// If the itemPosition is negative, start from the most recent event
			for(int pos = memory.size() - 1; pos <= 0 ; pos--)
			{
				if(memory.at(pos) == eventName)
				{
					// Found MemoryEvent
					n--;
					// Test if it is itemPosition evenName found
					if(n == itemPosition)
					{
						return pos;
					}
				}
			}
		}
		// not found
		return -1;
	}

	/*
		Return a QVariant with the datamining result operation. In case there are no events, or
		the data doesn't allow the operation it return an non valid QVariant.

		All numeric operations are converted to QString.
	*/
	QVariant Brain::dataMining( DataMiningOperation operation, const QString& event, int position, MemoryType memoryType, bool* valid )
	{
		// test if parameters are valid for datamining
		if( event.isEmpty() )
		{
			setValid( valid, false );
			return "";
		}

		// get the memory to performe data mining
		QList<MemoryEvent>& memory = ( memoryType == WorkingMemory ? _workingMemory : _longTermMemory );
		setValid( valid, true );

		switch( operation )
		{
		case DMO_Max:
			return QString::number( dataMiningMax( event, memory, valid ) );
		case DMO_Min:
			return QString::number( dataMiningMin( event, memory, valid ) );
		case DMO_Sum:
			return QString::number( dataMiningSum( event, memory, valid ) );
		case DMO_Count:
			return QString::number( dataMiningCount( event, memory, valid ) );
		case DMO_Mean:
			return QString::number( dataMiningMean( event, memory, valid ) );
		case DMO_Exists:
			return dataMiningExists( event, memory, valid ) ? "1" : "0";
		case DMO_Last:
			return dataMiningLast( event, memory, valid );
		case DMO_First:
			return dataMiningFirst( event, memory, valid );
		case DMO_Time:
			return dataMiningTime( event, memory, valid );
		case DMO_Item:
			return dataMiningItem( event, position, memory, valid );
		}

		setValid( valid, false );
		return "";
	}

	/*
		Return a QVariant with the datamining result operation. In case there are no events, or
		the data doesn't allow the operation it return an non valid QVariant.

		All numeric operations are converted to QString.
	*/
	QVariant Brain::dataMining( DataMiningOperation operation, const QString& event, const QString& value, int position, MemoryType memoryType, bool* valid )
	{
		// test if parameters are valid for datamining
		if( event.isEmpty() )
		{
			setValid( valid, false );
			return "";
		}

		// if value is empty, do datamining without the value
		if( value.isEmpty() )
		{
			return dataMining( operation, event, position, memoryType, valid );
		}


		// get the memory to performe data mining
		QList<MemoryEvent>& memory = ( memoryType == WorkingMemory ? _workingMemory : _longTermMemory );
		setValid( valid, true );

		switch( operation )
		{
		case DMO_Count:
			return QString::number( dataMiningCount( event, value, memory, valid ) );
		case DMO_Exists:
			return dataMiningExists( event, value, memory, valid ) ? "1" : "0";
		}

		setValid( valid, false );
		return "";
	}

	/*
		Return a QVariant with the datamining result operation. In case there are no events, or
		the data doesn't allow the operation it return an non valid QVariant.

		All numeric operations are converted to QString.
	*/
	QVariant Brain::dataMining( DataMiningOperation operation, const QString& event, qreal value, int position, MemoryType memoryType, bool* valid )
	{
		// test if parameters are valid for datamining
		if( event.isEmpty() )
		{
			setValid( valid, false );
			return 0;
		}

		// get the memory to performe data mining
		QList<MemoryEvent>& memory = ( memoryType == WorkingMemory ? _workingMemory : _longTermMemory );
		setValid( valid, true );

		switch( operation )
		{
		case DMO_Sum:
			return dataMiningSum( event, value, memory, valid );
		}

		setValid( valid, false );
		return 0;
	}


	/*
		Datamining Max only works if the values of the events are numbers.

		If any value of the event is not a number, it will set valid to false.
		If the memory is empty it will set valid to false.
		If no event is found it also set valid to false.

		Valid becomes true, if it founds one element.
	*/
	qreal Brain::dataMiningMax( const QString& event, const QList<MemoryEvent>& memory, bool* valid )
	{
		// by defaulf the data mining is not valid
		setValid( valid, false );

		if( memory.isEmpty() )
		{
			return 0;
		}

		bool ok;
		qreal max = INT_MIN;
		qreal aux;
		QListIterator<MemoryEvent> it(memory);
		while(it.hasNext()) // Iterate all memory
		{
			const MemoryEvent& me = it.next();

			if( QString::compare(me.event(), event, Qt::CaseInsensitive) == 0 ) // Event found
			{
				aux = me.value().toReal(&ok); // convert value to qreal
				if( !ok ) // if the event value is not numeric
				{
					setValid( valid, false ); // mark has invalid datamining
					return 0;
				}

				if( aux > max )
				{
					max = aux;
					setValid( valid, true );// Max found, mark data mining has valid
				}
			}
		}

		return max;
	}

	/*
		Datamining Min only works if the values of the events are numbers.

		If any value of the event is not a number, it will set valid to false.
		If the memory is empty it will set valid to false.
		If no event is found it also set valid to false.

		Valid becomes true, if it founds one element.
	*/
	qreal Brain::dataMiningMin( const QString& event, const QList<MemoryEvent>& memory, bool* valid )
	{
		// by defaulf the data mining is not valid
		setValid( valid, false );

		if( memory.isEmpty() )
		{
			return 0;
		}

		bool ok;
		qreal min = INT_MAX;
		qreal aux;
		QListIterator<MemoryEvent> it(memory);
		while(it.hasNext()) // Iterate all memory
		{
			const MemoryEvent& me = it.next();

			if( QString::compare(me.event(), event, Qt::CaseInsensitive) == 0 ) // Event found
			{
				aux = me.value().toReal(&ok); // convert value to qreal
				if( !ok ) // if the event value is not numeric
				{
					setValid( valid, false );
					return 0;
				}

				if( aux < min )
				{
					min = aux;
					setValid( valid, true ); // min found, mark has valid datamining
				}
			}
		}

		return min;
	}

	/*
		Datamining Sum only works if the values are numbers.

		If any value of the event is not a number, it will set valid to false.

		If the memory is empty or no event is found it will set valid to true, and return 0.
	*/
	qreal Brain::dataMiningSum( const QString& event, const QList<MemoryEvent>& memory, bool* valid)
	{
		// by defaulf the data mining is valid
		setValid( valid, true );

		if( memory.isEmpty() )
		{
			return 0;
		}

		bool ok;
		qreal sum = 0;
		qreal aux;
		QListIterator<MemoryEvent> it(memory);
		while(it.hasNext()) // Iterate all memory
		{
			const MemoryEvent& me = it.next();

			if( QString::compare(me.event(), event, Qt::CaseInsensitive) == 0 ) // Event found
			{
				aux = me.value().toReal(&ok); // convert value to qreal
				if( !ok ) // if the event value is not numeric
				{
					setValid( valid, false ); // mark has invalid datamining
					return 0;
				}
				sum += aux; // increment
			}
		}

		return sum;
	}

	/*
		Datamining Sum only works if the values are numbers.
		It only sums events with the value specified.

		If any value of the event is not a number, it will set valid to false.

		If the memory is empty or no event with the value is found it will set valid to true, and return 0.
	*/
	qreal Brain::dataMiningSum( const QString& event, qreal value, const QList<MemoryEvent>& memory, bool* valid )
	{
		// by defaulf the data mining is valid
		setValid( valid, true );

		if( memory.isEmpty() )
		{
			return 0;
		}

		bool ok;
		qreal sum = 0;
		qreal aux;
		QListIterator<MemoryEvent> it(memory);
		while(it.hasNext()) // Iterate all memory
		{
			const MemoryEvent& me = it.next();

			if( QString::compare(me.event(), event, Qt::CaseInsensitive) == 0 ) // Event found
			{
				aux = me.value().toReal(&ok); // convert value to qreal
				if( !ok ) // if the event value is not numeric
				{
					setValid( valid, false );
					return 0;
				}
				if( value == aux )
				{
					sum += aux; // increment
				}
			}
		}

		return sum;
	}

	/*
		Datamining Count counts all events with name event in memory

		It is always valid datamining.
	*/
	qreal Brain::dataMiningCount( const QString& event, const QList<MemoryEvent>& memory, bool* valid )
	{
		// by defaulf the data mining is valid
		setValid( valid, true );

		if( memory.isEmpty() )
		{
			return 0;
		}

		int n = 0;

		QListIterator<MemoryEvent> it(memory);
		while( it.hasNext() ) // Iterate all memory
		{
			const MemoryEvent& me = it.next();

			if( QString::compare(me.event(), event, Qt::CaseInsensitive ) == 0 ) // Event found
			{
				n++;
			}
		}

		return n;
	}

	/*
		Datamining Count counts all events with name event and value in memory

		It is always valid datamining.
	*/
	qreal Brain::dataMiningCount( const QString& event, const QString& value, const QList<MemoryEvent>& memory, bool* valid )
	{
		// by default the data mining is valid
		setValid( valid, true );

		if( memory.isEmpty() )
		{
			return 0;
		}

		int n = 0;

		QListIterator<MemoryEvent> it(memory);
		while( it.hasNext() ) // Iterate all memory
		{
			const MemoryEvent& me = it.next();

			if( QString::compare(me.event(), event, Qt::CaseInsensitive ) == 0 &&
				QString::compare(me.value().toString(), value, Qt::CaseInsensitive ) == 0 ) // Event with value found
			{
				n++;
			}
		}

		return n;
	}

	/*
		Datamining Mean only works if the values are numbers.

		If any value of the event is not a number, it will set valid to false.

		If the memory is empty or no event is found it will set valid to true, and return 0.
	*/
	qreal Brain::dataMiningMean( const QString& event, const QList<MemoryEvent>& memory, bool* valid)
	{
		// by defaulf the data mining is valid
		setValid( valid, false );

		if( memory.isEmpty() )
		{
			return 0;
		}

		bool ok;
		qreal sum = 0;
		int n = 0;
		qreal aux;
		QListIterator<MemoryEvent> it(memory);
		while(it.hasNext()) // Iterate all memory
		{
			const MemoryEvent& me = it.next();

			if( QString::compare(me.event(), event, Qt::CaseInsensitive) == 0 ) // Event found
			{
				aux = me.value().toReal(&ok); // convert value to qreal
				if( !ok ) // if the event value is not numeric
				{
					setValid( valid, false );
					return 0;
				}
				sum += aux; // increment
				n++;
			}
		}

		// Return 0, if no events were found
		return (n > 0 ? sum / n : 0); // return mean = sum / n
	}

	/*
		Datamining Exists is always valid
	*/
	bool Brain::dataMiningExists( const QString& event, const QList<MemoryEvent>& memory, bool* valid)
	{
		// set data mining to valid
		setValid( valid, true );

		if( memory.isEmpty() )
		{
			return false;
		}

		QListIterator<MemoryEvent> it(memory);
		while(it.hasNext()) // Iterate all memory
		{
			const MemoryEvent& me = it.next();

			if( QString::compare(me.event(), event, Qt::CaseInsensitive) == 0 ) // Event found
			{
				return true;
			}
		}

		return false;
	}

	/*
		Datamining Exists is always valid
	*/
	bool Brain::dataMiningExists( const QString& event, const QString& value, const QList<MemoryEvent>& memory, bool *valid )
	{
		// set data mining to valid
		setValid( valid, true );

		if( memory.isEmpty() )
		{
			return false;
		}

		QListIterator<MemoryEvent> it(memory);
		while(it.hasNext()) // Iterate all memory
		{
			const MemoryEvent& me = it.next();

			if( QString::compare(me.event(), event, Qt::CaseInsensitive ) == 0 &&
				QString::compare(me.value().toString(), value, Qt::CaseInsensitive ) == 0 ) // Event with value found
			{
				return true;
			}
		}

		return false;
	}


	/*
		Dataminign Last. Return the value of the last event found

		If the memory is empty or the event is not found, set valid to false. Return an emtpy QString.
	*/
	QString Brain::dataMiningLast( const QString& event, const QList<MemoryEvent>& memory, bool* valid)
	{
		// by defaulf the data mining is not valid
		setValid( valid, false );

		if( memory.isEmpty() )
		{
			return "";
		}

		QListIterator<MemoryEvent> it(memory);
		it.toBack(); // start search from back
		while( it.hasPrevious() ) // Iterate all memory
		{
			const MemoryEvent& me = it.previous();

			if( QString::compare(me.event(), event, Qt::CaseInsensitive ) == 0 ) // Event found
			{
				setValid( valid, true );
				return me.value().toString();
			}
		}

		return "";
	}

	/*
		Dataminign First. Return the value of the first event found

		If the memory is empty or the event is not found, set valid to false. Return an emtpy QString.
	*/
	QString Brain::dataMiningFirst( const QString& event, const QList<MemoryEvent>& memory, bool* valid )
	{
		// by defaulf the data mining is not valid
		setValid( valid, false );

		if( memory.isEmpty() )
		{
			return "";
		}

		QListIterator<MemoryEvent> it(memory);
		while( it.hasNext() ) // Iterate all memory
		{
			const MemoryEvent& me = it.next();

			if( QString::compare(me.event(), event, Qt::CaseInsensitive ) == 0 ) // Event found
			{
				setValid( valid, true );
				return me.value().toString();
			}
		}

		return "";
	}

	QString Brain::dataMiningItem( const QString& event, int position, const QList<MemoryEvent>& memory, bool *valid )
	{
		// by defaulf the data mining is not valid
		setValid( valid, false );

		if( memory.isEmpty() )
		{
			return "";
		}

		// Search for elements starting from start
		if( position > 0 )
		{
			QListIterator<MemoryEvent> it(memory);
			while( it.hasNext() ) // Iterate all memory
			{
				const MemoryEvent& me = it.next();

				if( QString::compare(me.event(), event, Qt::CaseInsensitive ) == 0 ) // Event found
				{
					// test if it the correct item
					if( position == 1 )
					{
						setValid( valid, true );
						return me.value().toString();
					}
					position--; // found one, decrease the position
				}
			}
			return "";
		}
		else if ( position < 0 )
		{
			QListIterator<MemoryEvent> it(memory);
			it.toBack(); // start search from back
			while( it.hasPrevious() ) // Iterate all memory
			{
				const MemoryEvent& me = it.previous();

				if( QString::compare(me.event(), event, Qt::CaseInsensitive ) == 0 ) // Event found
				{
					// test if it is the correct event
					if( position == -1 )
					{
						setValid( valid, true );
						return me.value().toString();
					}
					position++; // Increase position until it reachs -1
				}
			}

			return "";
		}

		// position can't be 0
		return "";
	}

	/*
		Datamining Time. Get the time from the last event in memory

		If the memory is empty or the event is not found, set valid to false. Return 0.
	*/
	qreal Brain::dataMiningTime( const QString& event, const QList<MemoryEvent>& memory, bool *valid )
	{
		// by defaulf the data mining is not valid
		setValid( valid, false );

		if( memory.isEmpty() )
		{
			return 0;
		}

		QListIterator<MemoryEvent> it(memory);
		it.toBack();
		while( it.hasPrevious() ) // Iterate all memory
		{
			const MemoryEvent& me = it.previous();

			if( QString::compare(me.event(), event, Qt::CaseInsensitive ) == 0 ) // Event found
			{
				setValid( valid, true );
				qDebug() << me.time();
				return me.time();
			}
		}

		return 0;
	}

	/*
		Datamining Time. Get the time from the last event in memory with a specific value

		If the memory is empty or the event is not found, set valid to false. Return 0.
	*/
	qreal Brain::dataMiningTime( const QString& event, const QString& value, const QList<MemoryEvent>& memory, bool *valid )
	{
		// by defaulf the data mining is not valid
		setValid( valid, false );

		if( memory.isEmpty() )
		{
			return 0;
		}

		QListIterator<MemoryEvent> it(memory);
		it.toBack();
		while( it.hasPrevious() ) // Iterate all memory
		{
			const MemoryEvent& me = it.previous();

			if( QString::compare(me.event(), event, Qt::CaseInsensitive ) == 0 &&
				QString::compare(me.value().toString(), value, Qt::CaseInsensitive ) == 0    ) // Event found
			{
				setValid( valid, true );
				return me.time();
			}
		}

		return 0;
	}


	/*
		Private method, to change the value of the pointer valid.
		It only changes, if the pointer is valid.
	*/
	void Brain::setValid( bool* valid, bool value )
	{
		if( valid != NULL)
		{
			*valid = value;
		}
	}

	/*
		Private method, to disable tasks perfomed by the brain.
	*/
	void Brain::deactivateTask(const QString& task)
	{
		_disabledTasks << translateBrainTasks(task);
	}

	/*
		Private method, to enable tasks perfomed by the brain.
	*/
	void Brain::activateTask(const QString& task)
	{
		_disabledTasks.removeAll(translateBrainTasks(task));
	}

	Brain::BrainNodes Brain::translateBrainTasks(const QString &text)
	{
		if (QString::compare( text, "Emotions", Qt::CaseInsensitive) == 0)
		{
			return EmotionNodes;
		}
		if (QString::compare( text, "Actions", Qt::CaseInsensitive) == 0)
		{
			return ActionNodes;
		}
		return UndefinedNodes;
	}

	/**
	  Load the reinforce statements from the xml file
	*/
	bool Brain::loadXmlActionModifiers(const QString &filename)
	{
		QFile f( filename );

		ActionModifiersXmlHandler* handler = new ActionModifiersXmlHandler();
		QXmlInputSource source( &f );
		if( source.data() == "" )
		{
			qWarning() << "[Brain::loadXmlReinforceStatements] File not found" << filename;
			return false;
		}

		QXmlSimpleReader reader;
		reader.setContentHandler( handler );

		// Retrives data from file
		if( reader.parse( source ) )
		{
			_actionModifiers = handler->reinforceStatements();
			return true;
		}

		return false;
	}

	/**
	  Find all modifiers that can afect the current action.
	*/
	QList<ActionModifier *> Brain::actionModifiers(const QString &action)
	{
		QList<ActionModifier *> result;

		QListIterator<ActionModifier *> it(_actionModifiers);
		ActionModifier *r;
		while (it.hasNext())
		{
			r = it.next();
			// Check action
			if (QString::compare(r->action(), action, Qt::CaseInsensitive) != 0)
			{
				continue;
			}
			// Check emotion
			bool emotionNotFound = false;
			Emotion* mEmotion = r->emotion();
			QListIterator<Emotion> it2(_emotions);
			while (it2.hasNext())
			{
				Emotion e = it2.next();
				// Check if emotion from modifier is equal to emotion from iterator
				if (QString::compare(e.key(), mEmotion->key(), Qt::CaseInsensitive) == 0)
				{
					// Check if emotion value is between the max and min value
					// for the current modifier
					if (e.value() > mEmotion->max() || e.value() < mEmotion->min())
					{
						emotionNotFound = true;
						break;
					}
				}
			}

			if (emotionNotFound)
			{
				continue;
			}

			// Check properties
			bool passedProperties = true;
			QHashIterator<QString, QString> it3(r->properties());
			while (it3.hasNext())
			{
				it3.next();
				// Check if property existes in the brain
				QHash<QString, QString>::const_iterator itP = _properties.find(it3.key());
				if (itP == _properties.end())
				{
					passedProperties = false;
					break;
				}
				// Check if the value is the same.
				if (QString::compare(it3.value(), itP.value(), Qt::CaseInsensitive) != 0)
				{
					passedProperties = false;
					break;
				}
			}

			if (!passedProperties)
			{
				continue;
			}

			result << r;
		}

		return result;
	}

}
