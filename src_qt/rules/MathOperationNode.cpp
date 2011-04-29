#include "MathOperationNode.h"
#include <QtCore/qmath.h>

namespace CnotiMind
{

	MathOperationNode::MathOperationNode( MathOperation op, const QString& variable, const QString& value,
										  const QString& resultVariable, Brain* brain, QObject* parent ):
		RuleNode( "", value, brain, parent),
		_operation( op ),
		_numericValue( value.toDouble( &_isNumericValue ) ),
		_resultVariable( resultVariable ),
		_variable( variable )
	{
	}

	/*
		It does not do nothing, since it requires variables to be executed
	*/
	void MathOperationNode::exec()
	{
		return;
	}

	void MathOperationNode::exec( QHash<QString, QString>& variables )
	{
		// Must be numeric value to be executed
		if(!_isNumericValue)
		{
			return;
		}

		// Test if the variable exists
		if( variables.contains( _variable ) )
		{
			// Get the value from the Variable
			QString variableValue =  variableToValue( _variable, variables );

			// Test if it is a numeric value
			bool ok;
			qreal variableNumericValue = variableValue.toDouble(&ok);
			if( ok )
			{
				// Apply the operator
				qreal result = applyOperation( variableNumericValue );

				// Save the output
				if( _resultVariable.isEmpty() ) // If it is empty, save on the same variable
				{
					variables.insert( _variable, QString::number( result ) );
				}
				else
				{
					variables.insert( _resultVariable, QString::number( result ) );
				}

				// Execute the children nodes with the new variable values
				execChildren( variables );
			}
		}
	}


	QString MathOperationNode::info( int depth ) const
	{
		QString info;

		info += space(depth) + "MathOperation ";

		return info + RuleNode::info(depth);
	}

	qreal MathOperationNode::applyOperation( qreal variableValue )
	{
		switch( _operation )
		{
			case MathOperationSum:
				return _numericValue + variableValue;
			case MathOperationMultiplication:
				return _numericValue * variableValue;
			case MathOperationDivision:
				return _numericValue / variableValue;
			case MathOperationRemainder:
				return (int) _numericValue % (int) variableValue;
			case MathOperationSubtraction:
				return _numericValue - variableValue;
			case MathOperationSquareRoot:
				return qSqrt( variableValue );
		}

		// If undefined return the same value from the variable
		return variableValue;
	}

}
