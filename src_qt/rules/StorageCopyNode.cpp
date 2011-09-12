#include "StorageCopyNode.h"

namespace CnotiMind
{

	StorageCopyNode::StorageCopyNode(MemoryType memory, Brain* brain, QObject* parent):
		RuleNode( brain, parent ),
		_memory( memory ),
	{

	}


	StorageCopyNode::StorageCopyNode(MemoryType memory, QDateTime before, QDateTime after,
									 Brain* brain, QObject* parent):
		RuleNode( brain, parent ),
		_memory( memory ),
		_before( before ),
		_after( after )
	{

	}



	void StorageCopyNode::exec()
	{

	}


	void StorageCopyNode::exec( QHash<QString, QString>& variables )
	{

	}

	/*!
		Information about the StorageCopyNode
	*/
	QString StorageCopyNode::info( int depth ) const
	{
		QString info;

		info += space(depth) + "StorageCopy (" + _memory + ")";

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
