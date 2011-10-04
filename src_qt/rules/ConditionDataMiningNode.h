#if !defined(_CONDITIONDATAMININGNODE_H)
#define _CONDITIONDATAMININGNODE_H

#include <QtCore/QString>

#include "ConditionNode.h"
#include "../CnotiMind.h"

namespace CnotiMind
{


	class ConditionDataMiningNode : public ConditionNode //, DataMining
	{
		Q_OBJECT

	public:

		ConditionDataMiningNode(const QString& event, const QString& value, ConditionOperator op,
								DataMiningOperation dataMiningOperation, MemoryType memory,
								const QString& variable, const QString& compareValue,
								Brain* brain, QObject* parent);

		void exec();
		void exec( QHash<QString, QString>& variables );

		QString info( int depth = 0 ) const;

		static ConditionDataMiningNode *fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject* parent );

	protected:
		const DataMiningOperation _dataMiningOperation;
		const QString _variable;
		const QString _compareValue;
		qreal _compareValueNumeric;
		const MemoryType _memory;
		bool _isCompareValueNumeric;
		QString _result;
		QString _event;
		QString _value;
		qreal _valueNumeric;
		bool _isValueNumeric;

		bool isTrue();
	};

}

#endif  //_CONDITIONDATAMININGNODE_H
