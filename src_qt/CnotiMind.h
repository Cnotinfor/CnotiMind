#ifndef CNOTIMIND_H
#define CNOTIMIND_H

class QString;

namespace CnotiMind
{

	enum MemoryType
	{
		LongTermMemory,
		WorkingMemory,
		UndefinedMemory
	};

	enum ConditionOperator
	{
		ConditionOperatorEqual,
		ConditionOperatorDifferent,
		ConditionOperatorSmaller,
		ConditionOperatorBigger,
		ConditionOperatorBiggerOrEqual,
		ConditionOperatorSmallerOrEqual,
		ConditionOperatorUndefined
	};

	enum DataMiningOperation
	{
		DMO_Max,
		DMO_Min,
		DMO_Sum,
		DMO_Count,
		DMO_Mean,
		DMO_Exists,
		DMO_Last,
		DMO_First,
		DMO_Duration,
		DMO_Time,
		DMO_Item,
		DMO_Undefined
	};

	enum MathOperation
	{
		MathOperationSum,
		MathOperationMultiplication,
		MathOperationDivision,
		MathOperationRemainder,
		MathOperationSubtraction,
		MathOperationSquareRoot,
		MathOperationUndefined
	};

	enum DeletePosition
	{
		DeleteLast,
		DeleteFirst,
		DeleteItem, // Not implemente yeat
		DeleteAll
	};

	MemoryType translateMemoryType( const QString& text );
	ConditionOperator translateConditionOperator( const QString &text );
	DataMiningOperation translateDataMiningOperator( const QString &text );
	MathOperation translateMathOperation( const QString &text );
	DeletePosition translateDeletePosition( const QString &text );
}

#endif // CNOTIMIND_H
