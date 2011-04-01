#include <QtCore/QString>
#include <QtCore/QListIterator>

#include "ConditionEmotionNode.h"
#include "../Brain.h"
#include "../Emotion.h"

namespace CnotiMind
{

	ConditionEmotionNode::ConditionEmotionNode(const QString& emotion, const QString& value, ConditionNode::ConditionOperator op, Brain* brain, QObject* parent):
		ConditionNode( emotion, value, op, brain, parent ),
		_valueInt( value.toInt() )
	{

	}

	bool ConditionEmotionNode::isTrue() const
	{
		// If the brain doesn't have emotions
		if( _brain->_emotions.isEmpty() )
		{
			return false;
		}

		// search the emotion
		QListIterator<Emotion> it(_brain->_emotions);
		while( it.hasNext() )
		{
			Emotion e = it.next();

			if( e.key() == _key) // Emotion found
			{
				return testEmotion(e);
			}
		}

		return true;
	}

	/*
		Test the emotional value using the node operator
	*/
	bool ConditionEmotionNode::testEmotion( const Emotion& e ) const
	{
		switch( _operator )
		{
			case ConditionOperatorBigger: return e.value() == _valueInt;
			case ConditionOperatorBiggerOrEqual: return e.value() >= _valueInt;
			case ConditionOperatorSmaller: return e.value() < _valueInt;
			case ConditionOperatorSmallerOrEqual: return e.value() <= _valueInt;
			case ConditionOperatorEqual: return e.value() == _valueInt;
			case ConditionOperatorDifferent: return e.value() != _valueInt;
		}

		// if the operator is invalid
		return false;
	}

}
