#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QListIterator>

#include "ConditionPerceptionNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	ConditionPerceptionNode::ConditionPerceptionNode( const QString& key, const QString& value, ConditionNode::ConditionOperator op, Brain* brain, QObject* parent):
		ConditionNode( key, value, op, brain, parent )
	{

	}

	bool ConditionPerceptionNode::isTrue() const
	{
		// Check if there are perceptions to be processed in the brain
		if( !_brain->_receivedPerceptions.isEmpty() )
		{
			// Just test the first perception
			Perception p = _brain->_receivedPerceptions.head();
			// Check if it is the percetion for this Node
			if( p.key() == _key )
			{
				// Perception is equal to this Node
				return true;
			}
		}

		return false;
	}

}
