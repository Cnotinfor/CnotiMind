#include <QtCore/QString>
#include <QtCore/QListIterator>

#include "RuleNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	RuleNode::RuleNode( const QString& key, const QString& value, Brain* brain, QObject* parent ):
		Node( key, value ),
		QObject( parent ),
		_brain( brain )
	{
	}


	bool RuleNode::isRoot() const
	{
		return false;
	}

	/**
		Executes all children nodes exec
	*/
	void RuleNode::execChildren()
	{
		QListIterator<QObject*> it( children() );

		// calls exec for each children;
		while(it.hasNext())
		{
			QObject* obj = it.next();

			RuleNode* node = qobject_cast<RuleNode*>( obj );

			node->exec();
		}
	}

	/**
		Executes all children nodes exec.
		It uses the variables
	*/
	void RuleNode::execChildren( QHash<QString, QString>& variables )
	{
		QListIterator<QObject*> it( children() );

		// calls exec for each children;
		while(it.hasNext())
		{
			QObject* obj = it.next();

			RuleNode* node = qobject_cast<RuleNode*>( obj );

			node->exec( variables );
		}
	}
}
