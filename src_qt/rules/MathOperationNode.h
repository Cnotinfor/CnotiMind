#ifndef OPERATIONNODE_H
#define OPERATIONNODE_H

#include "../CnotiMind.h"
#include "RuleNode.h"

namespace CnotiMind
{
	/*
		/class OperationNode

		op = math operation
		variable = variable which will be applied the operation
		value = value to be applied to the variable, using the math operator
				The value must be numeric. If it is not, no operation will be executed
		result variable = if defined where the output will be stored.
						  if not defined will be stored in the same variable

	*/
	class MathOperationNode : public RuleNode
	{
		Q_OBJECT

	public:
		MathOperationNode( MathOperation op, const QString& variable, const QString& value,
					  const QString& resultVariable, Brain* brain, QObject* parent );

		void exec();
		void exec( QHash<QString, QString>& variables );

		QString info( int depth = 0 ) const;

	protected:
		qreal applyOperation( qreal variableValue );

		MathOperation _operation;
		QString _variable;
		qreal _numericValue;
		bool _isNumericValue;
		QString _resultVariable;


	};

}
#endif // OPERATIONNODE_H
