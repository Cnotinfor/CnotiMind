#include "DataMiningNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	DataMiningNode::DataMiningNode( const QString& key, const QString& value, DataMiningOperation dataMiningOperation,
								   MemoryType memory, const QString& variable, Brain* brain, QObject* parent ) :
		RuleNode( key, value, brain, parent ),
		_operation( dataMiningOperation ),
		_memory( memory ),
		_variable( variable )
	{
		_valueNumeric = value.toDouble( &_isValueNumeric );
	}

	void DataMiningNode::exec()
	{
		if( isTrue() )
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
		if( isTrue() )
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

	bool DataMiningNode::isTrue()
	{
		bool valid;

		// If the values are numbers it should use the
		if( _isValueNumeric )
		{
			_result = _brain->dataMining( _operation, _key, _valueNumeric, _memory, &valid );

			return valid;
		}
		else // If the value is QString
		{
			_result = _brain->dataMining( _operation, _key, _value, _memory, &valid );

			return valid;
		}
	}

}
