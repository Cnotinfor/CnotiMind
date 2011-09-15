#include "StorageCopyNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	StorageCopyNode::StorageCopyNode(MemoryType memory, Brain* brain, QObject* parent):
		RuleNode( brain, parent ),
		_memoryFrom( memory ),
		_memoryTo( ( memory == LongTermMemory ) ? WorkingMemory : LongTermMemory ),
		_beforePosition( PositionNone ),
		_afterPosition( PositionNone )
	{

	}


	StorageCopyNode::StorageCopyNode(MemoryType memory, const QString &afterDate, const QString &beforeDate, Brain* brain, QObject* parent):
		RuleNode( brain, parent ),
		_memoryFrom( memory ),
		_memoryTo( ( memory == LongTermMemory ) ? WorkingMemory : LongTermMemory ),
		_beforePosition( PositionNone ),
		_afterPosition( PositionNone ),
		_beforeDateString( beforeDate ),
		_afterDateString( afterDate )
	{

	}


	StorageCopyNode::StorageCopyNode(MemoryType memory, const QString &afterEvent, EventPosition afterEventPosition,
					const QString &beforeEvent, EventPosition beforeEventPosition, Brain* brain, QObject* parent):
		RuleNode( brain, parent ),
		_memoryFrom( memory ),
		_memoryTo( ( memory == LongTermMemory ) ? WorkingMemory : LongTermMemory ),
		_beforePosition( beforeEventPosition ),
		_afterPosition( afterEventPosition ),
		_beforeEventName( beforeEvent ),
		_afterEventName( afterEvent )
	{

	}



	void StorageCopyNode::exec()
	{

	}


	void StorageCopyNode::exec( QHash<QString, QString>& variables )
	{
		QString beforeEventName = _beforeEventName;
		QString afterEventName = _afterEventName;
		QString beforeDateString = _beforeDateString;
		QString afterDateString = _afterDateString;
		bool valid;

		tagsToValue(beforeEventName, variables);
		tagsToValue(afterEventName, variables);
		tagsToValue(beforeDateString, variables);
		tagsToValue(afterDateString, variables);

		// Test if the before Event exists
		QVariant result = _brain->dataMining(DMO_Exists, beforeEventName, 0, _memoryFrom, &valid);
		if( valid && result.toInt() == 1 )
		{

		}

		//
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
			MemoryType memory = translateMemoryType( atts.value( "Memory" ) );

			return new StorageCopyNode( memory, brain, parent );
		}
		return NULL;
	}



}
