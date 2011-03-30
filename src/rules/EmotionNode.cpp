#include <QtCore/QString>

#include "EmotionNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	EmotionNode::EmotionNode( const QString& key, const QString& value, Brain* brain, QObject* parent ):
		RuleNode( key, value, brain, parent ),
		_min(INT_MIN),
		_max(INT_MAX)
	{

	}

	EmotionNode::EmotionNode( const QString& key, const QString& value, int max, int min, Brain* brain, QObject* parent ):
		RuleNode( key, value, brain, parent ),
		_min( min ),
		_max( max )
	{

	}

	void EmotionNode::exec()
	{

	}

	RuleNode::RuleNodeTypes EmotionNode::type() const
	{
		return Emotion;
	}

}
