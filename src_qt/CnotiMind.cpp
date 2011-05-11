#include "CnotiMind.h"
#include <QtCore\QString>

namespace CnotiMind
{


	/*
		Translate a QString to MemoryType
	*/
	MemoryType translateMemoryType( const QString& text )
	{
		if( QString::compare( text, "WM", Qt::CaseInsensitive) == 0 )
		{
			return WorkingMemory;
		}
		if( QString::compare( text, "LTM", Qt::CaseInsensitive) == 0 )
		{
			return LongTermMemory;
		}
		return UndefinedMemory;
	}

	/*
		Converts text to the conditional operator
	*/
	ConditionOperator translateConditionOperator( const QString &text )
	{
		if( text.compare(">") == 0 || text.compare("bigger") == 0 )
		{
			return ConditionOperatorBigger;
		}
		if( text.compare(">=") == 0 )
		{
			return ConditionOperatorBiggerOrEqual;
		}
		if( text.compare("<") == 0 || text.compare("smaller") == 0 )
		{
			return ConditionOperatorSmaller;
		}
		if( text.compare("<=") == 0)
		{
			return ConditionOperatorSmallerOrEqual;
		}
		if( text.compare("==") == 0 || text.compare("=") == 0 )
		{
			return ConditionOperatorEqual;
		}
		if( text.compare("!=") == 0 || text.compare("<>") == 0)
		{
			return ConditionOperatorDifferent;
		}

		return ConditionOperatorUndefined;
	}

	/**
		Convert texto to a Data Mining operator
	*/
	DataMiningOperation translateDataMiningOperator( const QString &text )
	{
		if( QString::compare( text, "max", Qt::CaseInsensitive  ) == 0 )
		{
			return DMO_Max;
		}
		if( QString::compare( text, "min", Qt::CaseInsensitive  ) == 0 )
		{
			return DMO_Min;
		}
		if( QString::compare( text, "sum", Qt::CaseInsensitive  ) == 0 )
		{
			return DMO_Sum;
		}
		if( QString::compare( text, "count", Qt::CaseInsensitive  ) == 0 )
		{
			return DMO_Count;
		}
		if( QString::compare( text, "mean", Qt::CaseInsensitive  ) == 0 )
		{
			return DMO_Mean;
		}
		if( QString::compare( text, "exists", Qt::CaseInsensitive ) == 0 )
		{
			return DMO_Exists;
		}
		if( QString::compare( text, "last", Qt::CaseInsensitive  ) == 0 )
		{
			return DMO_Last;
		}
		if( QString::compare( text, "first", Qt::CaseInsensitive  ) == 0 )
		{
			return DMO_First;
		}
		if( QString::compare( text, "duration", Qt::CaseInsensitive  ) == 0 )
		{
			return DMO_Duration;
		}
		if( QString::compare( text, "time", Qt::CaseInsensitive  ) == 0 )
		{
			return DMO_Time;
		}
		return DMO_Undefined;
	}

	/*
		Convert text string to a MathOperation
	*/
	MathOperation translateMathOperation( const QString &text )
	{
		if( QString::compare( text, "sum", Qt::CaseInsensitive  ) == 0 ||
			QString::compare( text, "+" ) == 0 )
		{
			return MathOperationSum;
		}
		if( QString::compare( text, "sub", Qt::CaseInsensitive  ) == 0 ||
			QString::compare( text, "subtraction", Qt::CaseInsensitive  ) == 0 ||
			QString::compare( text, "-" ) == 0 )
		{
			return MathOperationSubtraction;
		}
		if( QString::compare( text, "mul", Qt::CaseInsensitive  ) == 0 ||
			QString::compare( text, "multiplication", Qt::CaseInsensitive  ) == 0 ||
			QString::compare( text, "x", Qt::CaseInsensitive ) == 0 ||
			QString::compare( text, "*" ) == 0 )
		{
			return MathOperationMultiplication;
		}
		if( QString::compare( text, "div", Qt::CaseInsensitive  ) == 0 ||
			QString::compare( text, "division", Qt::CaseInsensitive  ) == 0 ||
			QString::compare( text, "quotient", Qt::CaseInsensitive  ) == 0 ||
			QString::compare( text, "/" ) == 0 )
		{
			return MathOperationDivision;
		}
		if( QString::compare( text, "remainder", Qt::CaseInsensitive  ) == 0 ||
			QString::compare( text, "%" ) == 0 )
		{
			return MathOperationRemainder;
		}
		if( QString::compare( text, "sqrt", Qt::CaseInsensitive  ) == 0 )
		{
			return MathOperationSquareRoot;
		}

		return MathOperationUndefined;
	}

	/*
		Convert text string to a DeleteItem
	*/
	DeletePosition translateDeletePosition( const QString &text )
	{
		if( QString::compare( text, "last", Qt::CaseInsensitive  ) == 0 )
		{
			return DeleteLast;
		}
		if( QString::compare( text, "first", Qt::CaseInsensitive  ) == 0 )
		{
			return DeleteFirst;
		}
		if( QString::compare( text, "item", Qt::CaseInsensitive  ) == 0 )
		{
			return DeleteItem;
		}
		if( QString::compare( text, "all", Qt::CaseInsensitive  ) == 0 )
		{
			return DeleteAll;
		}

	}
}
