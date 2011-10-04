#include "StorageCopyNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	StorageCopyNode::StorageCopyNode(MemoryType fromMemory, MemoryType toMemory, Brain* brain, QObject* parent):
		RuleNode( brain, parent ),
		_memoryFrom( fromMemory ),
		_memoryTo( toMemory ),
		_beforePosition( PositionNone ),
		_afterPosition( PositionNone )
	{

	}


	StorageCopyNode::StorageCopyNode(MemoryType fromMemory, MemoryType toMemory, const QString &afterDate, const QString &beforeDate, Brain* brain, QObject* parent):
		RuleNode( brain, parent ),
		_memoryFrom( fromMemory ),
		_memoryTo( toMemory ),
		_beforePosition( PositionNone ),
		_afterPosition( PositionNone ),
		_beforeDateString( beforeDate ),
		_afterDateString( afterDate )
	{

	}


	StorageCopyNode::StorageCopyNode(MemoryType fromMemory, MemoryType toMemory, const QString &afterEvent, EventPosition afterEventPosition,
					const QString &beforeEvent, EventPosition beforeEventPosition, Brain* brain, QObject* parent):
		RuleNode( brain, parent ),
		_memoryFrom( fromMemory ),
		_memoryTo( toMemory ),
		_beforePosition( beforeEventPosition ),
		_afterPosition( afterEventPosition ),
		_beforeEventName( beforeEvent ),
		_afterEventName( afterEvent )
	{


	}



	void StorageCopyNode::exec()
	{
		_brain->copyEvents(_memoryFrom, _memoryTo, _afterEventName, _afterPosition, _beforeEventName, _beforePosition);
	}


	void StorageCopyNode::exec( QHash<QString, QString>& variables )
	{
		QString beforeEventName = _beforeEventName;
		QString afterEventName = _afterEventName;
		QString beforeDateString = _beforeDateString;
		QString afterDateString = _afterDateString;

		tagsToValue(beforeEventName, variables);
		tagsToValue(afterEventName, variables);
		tagsToValue(beforeDateString, variables);
		tagsToValue(afterDateString, variables);

		// Copy the events as necessary
		if( afterEventName.isEmpty() || beforeEventName.isEmpty() || _afterPosition == PositionNone || _beforePosition == PositionNone )
		{
			_brain->copyEvents(_memoryFrom, _memoryTo);
		}
		else
		{
			_brain->copyEvents(_memoryFrom, _memoryTo, afterEventName, _afterPosition, beforeEventName, _beforePosition);
		}


	}

	/*!
		Information about the StorageCopyNode
	*/
	QString StorageCopyNode::info( int depth ) const
	{
		QString info;

		info += space(depth) + "StorageCopy (from: " + _memoryFrom + ")";

		if(_before.isValid())
		{
			info += " Before: " + _before.toString("yyyy-MM-dd");
		}
		if(_after.isValid())
		{
			info += " After: " + _after.toString("yyyy-MM-dd");
		}

		return info;
	}



	StorageCopyNode *StorageCopyNode::fromXML( const QString &qName, const QXmlAttributes &atts,
											   Brain* brain, QObject* parent )
	{
		if( qName.compare( "StorageCopy", Qt::CaseInsensitive ) == 0 )
		{
			MemoryType fromMemory = translateMemoryType( atts.value( "from" ) );
			MemoryType toMemory = translateMemoryType( atts.value( "fro" ) );

			return new StorageCopyNode( fromMemory, toMemory, brain, parent );
		}
		return NULL;
	}



}
