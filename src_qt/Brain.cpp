#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtCore/QMutableListIterator>
#include <QtCore/QListIterator>
#include <QDateTime>

#include "Brain.h"
#include "CnotiMind.h"
#include "SettingsXmlHandler.h"
#include "rules/RuleNode.h"
#include "rules/RulesXmlHandler.h"
#include "gui/BrainGUI.h"

namespace CnotiMind
{

	Brain::Brain( const QString& path, QObject* parent ):
		QThread( parent ),\
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

		qDebug() << "[Brain::loadXmlRules] Error in XML, line" << handler->line();

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
		QFile f(filename);

		if( f.open( QIODevice::WriteOnly | QIODevice::Text ) )
		{
			f.write( "<Memory>\n" );
			f.write( "<LongTermMemory>\n" );
			QListIterator<MemoryEvent> it(_longTermMemory);
			while(it.hasNext())
			{

				f.write( it.next().toXml().toUtf8() + "\n" );
			}
			f.write( "</LongTermMemory>\n" );
			f.write( "<WorkingMemory>\n" );
			QListIterator<MemoryEvent> it2(_workingMemory);
			while(it2.hasNext())
			{
				f.write( it2.next().toXml().toUtf8() + "\n" );
			}
			f.write( "</WorkingMemory>\n" );
			f.write( "</Memory>\n" );

			f.close();
			return true;
		}

		return false;
	}

	bool Brain::loadMemory(const QString& filename)
	{
		QFile f(filename);

		if( f.open( QIODevice::ReadOnly | QIODevice::Text ) )
		{

			f.close();
			return true;
		}

		return false;
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

			// Check if it should stop
			if(_quit)
			{
				return;
			}

			int n_emotions = _emotionsChanged.size();

			// Execute the rules
			if( _rules != NULL )
			{
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

		// changing the semaphore, so that
		_semaphoreBrain.release();
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

	void Brain::updateEmotionalValue(const QString& emotionName, qreal variation, qreal max, qreal min)
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

		// Update the GUI
		if( _gui != NULL )
		{
			_gui->updateEmotions();
		}
	}

	void Brain::updateEmotionalValue(const QString& emotionName, qreal variation)
	{
		updateEmotionalValue( emotionName, variation, INT_MAX, INT_MIN);
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

	/*
		Delete an event from the memory
	*/
	void Brain::deleteEvent( const QString& key, DeletePosition position, MemoryType memory )
	{
		QList<MemoryEvent>* mem = ( memory == LongTermMemory ? &_longTermMemory : &_workingMemory );

		QMutableListIterator<MemoryEvent> it(*mem);

		switch(position)
		{
			case DeleteLast:
				it.toBack();
				while(it.hasPrevious())
				{
					if( it.previous() == key )
					{
						it.remove();
						break;
					}
				}
				break;
			case DeleteFirst:
				while(it.hasNext())
				{
					if( it.next() == key )
					{
						it.remove();
						break;
					}
				}
				break;
			case DeleteAll:
				while(it.hasNext())
				{
					if( it.next() == key )
					{
						it.remove();
					}
				}
				break;
		}
	}

	void Brain::deleteEvent( const QString& key, const QString& value, DeletePosition position, MemoryType memory )
	{

	}


	/*
		Return a QString with the datamining result operation. In case there are no events, or
		the data doesn't allow the operation it return an empty QString.

		All numeric operations are converted to QString
	*/

	;

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
		Datamining Max only works if the values are numbers.

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
}
