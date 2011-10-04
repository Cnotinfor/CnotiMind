#include "MathOperationNode.h"
#include <QtCore/qmath.h>
#include <QDebug>

namespace CnotiMind
{

	MathOperationNode::MathOperationNode( MathOperation op, const QString& variable, const QString& value,
										  const QString& resultVariable, Brain* brain, QObject* parent ):
		RuleNode( brain, parent),
		_operation( op ),
		_value( value ),
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
		bool valueOk;
		qreal numericValue;

		// Test if the value to use in the operation is a variable
		if(!_isNumericValue)
		{
			QString value = _value;
			tagsToValue( value, variables );

			// Variable not found
			if( value.isEmpty() )
			{
				qDebug() << "[MathOperationNode::exec] value" << value << "has not found in variables";
				return; // does nothing
			}

			// Convert to number
			numericValue = value.toDouble( &valueOk );
			if( !valueOk )
			{
				qDebug() << "[MathOperationNode::exec] value" << value << "is not a number";
				return; // It was not possible to convert to number
			}

			// update the numeric value from the node
			_numericValue = numericValue;
		}

		// Get the value from the Variable
		QString variableValue = _variable;
		tagsToValue( variableValue, variables );

		// Test if the variable exists
		if( !variableValue.isEmpty() )
		{
			// Test if the variable value is a numeric value
			bool variableOk;
			qreal variableNumericValue = variableValue.toDouble( &variableOk );
			if( variableOk )
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
				return variableValue + _numericValue;
			case MathOperationMultiplication:
				return variableValue * _numericValue ;
			case MathOperationDivision:
				if( variableValue == 0 )
				{
					return 0;
				}
				return variableValue / _numericValue;
			case MathOperationRemainder:
				if( variableValue == 0 )
				{
					return 0;
				}
				return (int) variableValue % (int) _numericValue;
			case MathOperationSubtraction:
				return variableValue - _numericValue;
			case MathOperationSquareRoot:
				return qSqrt( variableValue );
		}

		// If undefined return the same value from the variable
		return variableValue;
	}

	MathOperationNode *MathOperationNode::fromXML(const QString &qName, const QXmlAttributes &atts, Brain *brain, QObject *parent)
	{
		if(qName.compare("MathOperation") == 0)
		{
			MathOperation operation = translateMathOperation( atts.value( "name" ) );
			QString value = atts.value( "value" );
			QString variable = atts.value( "variable" );
			QString resultVariable = atts.value( "result" );

			return new MathOperationNode( operation, variable, value, resultVariable, brain, parent );
		}
		return NULL;
	}

}
