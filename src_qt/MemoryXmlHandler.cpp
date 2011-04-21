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

		if( QString::compare( qName, "Memory", Qt::CaseInsensitive ) == 0 )
		{
			_type = UndefinedMemory;
			return true;
		}
		if( QString::compare( qName, "LongTermMemory", Qt::CaseInsensitive ) == 0 )
		{
			_type = LongTermMemory;
			return true;
		}
		if( QString::compare( qName, "WorkingMemory", Qt::CaseInsensitive ) == 0 )
		{
			_type = LongTermMemory;
			return true;
		}
		else if( QString::compare( qName, "MemoryEvent", Qt::CaseInsensitive ) == 0 )
		{
			if( _type == UndefinedMemory ) // Memory event not inside Working or Long Term Memory
			{
				return false;
			}

			QString name = atts.value( "name" );
			QString value = atts.value( "value" );

			MemoryEvent me( name, value );

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

		return true;
	}

}
