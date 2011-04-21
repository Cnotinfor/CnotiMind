#include <QtCore/QString>

#include "EmotionNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	EmotionNode::EmotionNode( const QString& key, const QString& value, Brain* brain, QObject* parent ):
		RuleNode( key, value, brain, parent ),
		_min(INT_MIN),
		_max(INT_MAX),
		_valueNumeric( value.toDouble( &_valueNumericOk) )
	{

	}

	EmotionNode::EmotionNode( const QString& key, const QString& value, qreal max, qreal min, Brain* brain, QObject* parent ):
		RuleNode( key, value, brain, parent ),
		_min( min ),
		_max( max ),
		_valueNumeric( value.toDouble() )
	{

	}

	QString EmotionNode::info( int depth ) const
	{
		QString info;

		info += space(depth) + "Emotion (" + _key + ") increment=" + _value;

		if(_min != INT_MIN)
		{
			info += " min=" + QString::number( _min );
		}
		if(_max != INT_MAX)
		{
			info += " max=" + QString::number( _max );
		}

		return info + RuleNode::info(depth);
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

		_brain->updateEmotionalValue( _key, _valueNumeric, _max, _min );
	}

	void EmotionNode::exec( QHash<QString, QString> &variables )
	{
		if(!_valueNumericOk) // it is not a number, it could be a variable
		{
			const QString& value = variableToValue( _value, variables);
			bool ok;

			qreal newValueInt = value.toDouble(&ok);
			if( ok )
			{
				_valueNumeric = newValueInt;
			}
		}

		_brain->updateEmotionalValue( _key, _valueNumeric, _max, _min );
	}
}
