#include <QtCore/QString>
#include <QtCore/QListIterator>

#include "ConditionEmotionNode.h"
#include "../Brain.h"
#include "../Emotion.h"

namespace CnotiMind
{

	ConditionEmotionNode::ConditionEmotionNode(const QString& emotion, const QString& value, ConditionOperator op, Brain* brain, QObject* parent):
		ConditionNode( emotion, value, op, brain, parent )
	{

	}

	void ConditionEmotionNode::exec()
	{
		if( isTrue() )
		{
			QHash<QString,QString> variables;
			variables.insert("[Emotion.value]", _value );
			execChildren( variables );
		}
	}

	void ConditionEmotionNode::exec( QHash<QString,QString>& variables )
	{
		if( isTrue() )
		{
			variables.insert( "[Emotion.value]", _value );
			execChildren( variables );
		}
	}

	QString ConditionEmotionNode::info( int depth ) const
	{
		QString info;

		info += space(depth) + "Condition type=Emotion";

		return info + RuleNode::info(depth);
	}

	bool ConditionEmotionNode::isTrue()
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
		if( _isValueNumeric )
		{
			switch( _operator )
			{
				case ConditionOperatorBigger: return e.value() > _valueNumeric;
				case ConditionOperatorBiggerOrEqual: return e.value() >= _valueNumeric;
				case ConditionOperatorSmaller: return e.value() < _valueNumeric;
				case ConditionOperatorSmallerOrEqual: return e.value() <= _valueNumeric;
				case ConditionOperatorEqual: return e.value() == _valueNumeric;
				case ConditionOperatorDifferent: return e.value() != _valueNumeric;
			}
		}
		// if the operator is invalid or the value is not numeric
		return false;
	}

}
