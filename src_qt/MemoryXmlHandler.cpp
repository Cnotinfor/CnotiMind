#include "MemoryXmlHandler.h"
#include "Brain.h"


namespace CnotiMind
{

	MemoryXmlHandler::MemoryXmlHandler( Brain* brain):
		QXmlDefaultHandler(),
		_brain( brain ),
		_type( UndefinedMemory )
	{
	}


	bool MemoryXmlHandler::startElement ( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts )
	{
		Q_UNUSED( namespaceURI );
		Q_UNUSED( localName );

		if( qName.compare( "Memory", Qt::CaseInsensitive ) == 0 )
		{
			_type = UndefinedMemory;
			return true;
		}
		if( qName.compare( "LongTermMemory", Qt::CaseInsensitive ) == 0 )
		{
			_type = LongTermMemory;
			return true;
		}
		if( qName.compare( "WorkingMemory", Qt::CaseInsensitive ) == 0 )
		{
			_type = WorkingMemory;
			return true;
		}
		else if( qName.compare( "MemoryEvent", Qt::CaseInsensitive ) == 0 )
		{
			if( _type == UndefinedMemory ) // Memory event not inside Working or Long Term Memory
			{
				return false;
			}

			QString name = atts.value( "name" );
			QString value = atts.value( "value" );
			qint64 time = atts.value( "time" ).toInt();


			MemoryEvent me( name, value, time );

			_brain->storeToMemory(me, _type);
			return true;
		}
		return false;
	}

	bool MemoryXmlHandler::endElement( const QString & namespaceURI, const QString & localName, const QString & qName )
	{
		Q_UNUSED( namespaceURI );
		Q_UNUSED( localName );
		Q_UNUSED( qName );

		if( qName.compare( "LongTermMemory", Qt::CaseInsensitive ) == 0 && _type == LongTermMemory )
		{
			_type = UndefinedMemory;
			return true;
		}
		if( qName.compare( "WorkingMemory", Qt::CaseInsensitive ) == 0 && _type == WorkingMemory )
		{
			_type = UndefinedMemory;
			return true;
		}
		if( qName.compare("MemoryEvent", Qt::CaseInsensitive) == 0 || qName.compare("Memory", Qt::CaseInsensitive) == 0 )
		{
			return true;
		}

		// If it reach here there are invalid tags in XML
		return true;
	}

}
