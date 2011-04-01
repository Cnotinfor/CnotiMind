#include <QtCore/QString>

#include "EmotionNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	EmotionNode::EmotionNode( const QString& key, const QString& value, Brain* brain, QObject* parent ):
		RuleNode( key, value, brain, parent ),
		_min(INT_MIN),
		_max(INT_MAX),
		_valueInt( value.toInt() )
	{

	}

	EmotionNode::EmotionNode( const QString& key, const QString& value, int max, int min, Brain* brain, QObject* parent ):
		RuleNode( key, value, brain, parent ),
		_min( min ),
		_max( max ),
		_valueInt( value.toInt() )
	{

	}

	void EmotionNode::exec()
	{
		// Test if the value is valid
		bool ok;
		_value.toInt(&ok);
		if(!ok) // it is not a number, it could be a variable, but there are no variables
		{
			return; // it doesn't do nothing
		}

		_brain->updateEmotionalValue( _key, _valueInt, _max, _min );
	}

	void EmotionNode::exec( QHash<QString, QString> &variables )
	{
		// Test if the value is valid
		bool ok;
		_value.toInt(&ok);
		if(!ok) // it is not a number, it could be a variable
		{
			if( variables.contains( _value ) ) // Test if the variable is set
			{
				_valueInt = variables.value( _value ).toInt(&ok); // get the value from the variable

				if(!ok) // if there has an error convertinf the value to int
				{
					return;
				}
			}
			else
			{
				return; // It doesn't contain the variable, does nothing
			}
		}

		_brain->updateEmotionalValue( _key, _valueInt, _max, _min );
	}
}
