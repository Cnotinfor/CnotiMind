#include "DataMiningNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	DataMiningNode::DataMiningNode( const QString& event, const QString& value, DataMiningOperation dataMiningOperation,
								   MemoryType memory, const QString& variable, const QString& position, Brain* brain, QObject* parent ) :
		RuleNode( brain, parent ),
		_event( event ),
		_value( value ),
		_operation( dataMiningOperation ),
		_memory( memory ),
		_variable( variable ),
		_valueNumeric( value.toDouble( &_isValueNumeric ) ),
		_position( position ),
		_positionNumeric( position.toInt( &_isPositionNumeric ) )
	{

	}

	void DataMiningNode::exec()
	{
		if( isTrue( QHash<QString, QString>() ) )
		{
			if( _variable.isEmpty() )
			{
				// this should not happen, since the _variable should never be empty
				execChildren();
			}
			else
			{
				QHash<QString,QString> variables;
				variables.insert( _variable, _result.toString() );
				execChildren( variables );
			}
		}
	}

	void DataMiningNode::exec( QHash<QString, QString> &variables )
	{
		if( isTrue( variables ) )
		{
			if( !_variable.isEmpty() )
			{
				variables.insert( _variable, _result.toString() );
			}
			execChildren( variables );
		}
	}

	QString DataMiningNode::info( int depth ) const
	{
		QString info;

		info += space(depth) + "DataMining";

		return info + RuleNode::info(depth);
	}

	bool DataMiningNode::isTrue( const QHash<QString, QString> &variables )
	{
		bool valid;
		int position = 0;

		if( _isPositionNumeric )
		{
			position = _positionNumeric;
		}
		else // it should be a variable tag
		{
			QString positionStr = _position;
			bool ok;
			tagsToValue( positionStr, variables);

			// Test if it was possible to convert to number
			int p = positionStr.toInt( &ok );
			if( ok )
			{
				position = p;
			}
		}

		// If the values are numbers it should use the
		if( _isValueNumeric )
		{
			_result = _brain->dataMining( _operation, _event, _valueNumeric, position, _memory, &valid );

			return valid;
		}
		else // If the value is QString
		{
			_result = _brain->dataMining( _operation, _event, _value, position, _memory, &valid );

			return valid;
		}
	}

}
