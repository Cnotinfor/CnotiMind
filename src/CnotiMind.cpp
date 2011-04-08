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
		if( text.compare(">") == 0)
		{
			return ConditionOperatorBigger;
		}
		if( text.compare(">=") == 0)
		{
			return ConditionOperatorBiggerOrEqual;
		}
		if( text.compare("<") == 0)
		{
			return ConditionOperatorSmaller;
		}
		if( text.compare("<=") == 0)
		{
			return ConditionOperatorSmallerOrEqual;
		}
		if( text.compare("==") == 0)
		{
			return ConditionOperatorEqual;
		}
		if( text.compare("!=") == 0)
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
		if( QString::compare( text, "max" ) == 0 )
		{
			return DMO_Max;
		}
		if( QString::compare( text, "min" ) == 0 )
		{
			return DMO_Min;
		}
		if( QString::compare( text, "sum" ) == 0 )
		{
			return DMO_Sum;
		}
		if( QString::compare( text, "count" ) == 0 )
		{
			return DMO_Count;
		}
		if( QString::compare( text, "mean" ) == 0 )
		{
			return DMO_Mean;
		}
		if( QString::compare( text, "exists" ) == 0 )
		{
			return DMO_Exists;
		}
		if( QString::compare( text, "last" ) == 0 )
		{
			return DMO_Last;
		}
		if( QString::compare( text, "first" ) == 0 )
		{
			return DMO_First;
		}
		if( QString::compare( text, "duration" ) == 0 )
		{
			return DMO_Duration;
		}
		if( QString::compare( text, "time" ) == 0 )
		{
			return DMO_Time;
		}
		return DMO_Undefined;
	}
}
